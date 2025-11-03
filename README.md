# 🧠 Smart Congestion Control Algorithm using NS3

## 1. Title
**Smart Congestion Control Algorithm using Network Simulator 3 (NS3)**

---

## 2. Introduction
In modern computer networks, congestion occurs when too many packets compete for limited network resources, leading to packet loss, high latency, and reduced throughput.  
Congestion control mechanisms are essential to ensure efficient utilization of network bandwidth and stable network performance.

This project focuses on designing and simulating a **Smart Congestion Control Algorithm** using the **Network Simulator 3 (NS3)**.  
The proposed algorithm dynamically adjusts packet transmission rates based on real-time network conditions like queue length, round-trip time (RTT), and packet loss ratio.

---

## 3. Objective
- To study and analyze traditional congestion control algorithms like TCP Reno, NewReno, and BBR.  
- To design an improved, intelligent algorithm that adapts dynamically to congestion levels.  
- To simulate and evaluate the performance using NS3.  
- To compare throughput, packet loss, and delay with standard TCP variants.

---

## 4. Existing System
Existing TCP congestion control algorithms (e.g., TCP Reno, TCP NewReno, and TCP Tahoe) rely on **packet loss** as the primary indicator of congestion.  
However, this reactive approach causes throughput reduction and increased latency, especially in modern high-speed or wireless networks.

### Limitations:
- Delayed reaction to congestion.  
- Poor performance in dynamic or mobile environments.  
- Packet loss–based feedback may be inaccurate under wireless conditions.

---

## 5. Proposed System
The proposed **Smart Congestion Control Algorithm (SCCA)** uses **real-time feedback** from the network, combining:
- Queue length monitoring  
- Round-trip time (RTT) measurement  
- Packet delivery ratio  

Instead of waiting for packet loss, the algorithm predicts congestion earlier and adjusts the sending rate smoothly.  
It uses a **hybrid AI-inspired adaptive mechanism** (simple threshold-based or weighted approach) to balance throughput and delay.

---

## 6. Algorithm / Methodology
### Algorithm Steps:
1. **Initialization:**  
   Set initial congestion window (cwnd) and threshold values.

2. **Data Transmission:**  
   Begin sending packets and record RTT, queue length, and acknowledgment rate.

3. **Congestion Detection:**  
   If average RTT increases and queue length > threshold → predict congestion.

4. **Rate Adjustment:**  
   - Decrease cwnd moderately (not drastically).  
   - Adjust sending rate proportionally to the congestion level.

5. **Recovery Phase:**  
   When congestion indicators normalize, gradually increase cwnd.

6. **Repeat:**  
   Continue dynamic monitoring and adjustment.

---

## 7. Tools and Software Used

| Tool | Purpose |
|------|----------|
| **NS3 (Network Simulator 3)** | Simulation of network environment |
| **Ubuntu / Linux** | Operating System for NS3 |
| **Python / C++** | For writing custom congestion control logic |
| **Wireshark** | For packet analysis and visualization |

---

## 8. System Architecture
