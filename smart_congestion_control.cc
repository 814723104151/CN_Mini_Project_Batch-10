#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("SmartCongestionControlExample");

// Define a simple Smart Congestion Control based on RTT and Queue size
class SmartCongestionControl {
public:
    double cwnd;       // congestion window
    double ssthresh;   // slow start threshold
    double rttThreshold;
    double queueThreshold;

    SmartCongestionControl() {
        cwnd = 1.0;
        ssthresh = 10.0;
        rttThreshold = 50.0;       // in ms
        queueThreshold = 0.6;      // 60% full
    }

    void AdjustWindow(double currentRtt, double queueUtilization) {
        if (currentRtt > rttThreshold || queueUtilization > queueThreshold) {
            // Congestion predicted → Decrease cwnd
            cwnd = cwnd * 0.8;
            if (cwnd < 1.0) cwnd = 1.0;
        } else {
            // No congestion → Increase cwnd smoothly
            cwnd = cwnd + 0.5;
        }
    }
};

int main(int argc, char *argv[]) {
    LogComponentEnable("SmartCongestionControlExample", LOG_LEVEL_INFO);

    NodeContainer nodes;
    nodes.Create(4); // 0,1 = senders; 2,3 = receivers

    // Create links: 0->2 and 1->3 through a router
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("10ms"));

    NetDeviceContainer dev01 = p2p.Install(nodes.Get(0), nodes.Get(2));
    NetDeviceContainer dev23 = p2p.Install(nodes.Get(1), nodes.Get(3));

    InternetStackHelper stack;
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces1 = address.Assign(dev01);
    address.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces2 = address.Assign(dev23);

    // Install UDP applications
    uint16_t port = 9;
    UdpEchoServerHelper echoServer(port);
    ApplicationContainer serverApps = echoServer.Install(nodes.Get(2));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    UdpEchoClientHelper echoClient(interfaces1.GetAddress(1), port);
    echoClient.SetAttribute("MaxPackets", UintegerValue(1000));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(0.05)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    // Simulation environment
    SmartCongestionControl scc;

    Simulator::Schedule(Seconds(2.0), [&]() {
        for (double t = 2.0; t <= 10.0; t += 1.0) {
            double fakeRtt = 40 + rand() % 30;       // simulate variable RTT
            double fakeQueue = (rand() % 100) / 100.0; // simulate queue usage

            scc.AdjustWindow(fakeRtt, fakeQueue);
            NS_LOG_INFO("Time " << t << "s: cwnd = " << scc.cwnd
                                << "  RTT=" << fakeRtt
                                << "ms  QueueUtil=" << fakeQueue);
        }
    });

    Simulator::Stop(Seconds(10.0));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
