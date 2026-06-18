# Reliable Transport Protocol Framework using C++

## Overview

This project implements a Reliable Transport Protocol Framework over UDP using C++ socket programming. Since UDP does not provide built-in reliability mechanisms such as acknowledgements, retransmissions, or packet ordering, reliability is implemented at the application layer using the Stop-and-Wait ARQ (Automatic Repeat reQuest) protocol.

The framework consists of sender and receiver modules that communicate using UDP sockets. Reliability is achieved through sequence numbering, acknowledgements (ACK), timeout handling, and retransmission mechanisms. Packet loss is also simulated to evaluate protocol behavior under unreliable network conditions.

---

## Objectives

* Implement reliable data transfer using UDP.
* Understand Stop-and-Wait ARQ protocol.
* Design sender and receiver modules using C++.
* Implement ACK-based communication.
* Simulate packet loss and retransmission.
* Analyze transport layer reliability mechanisms.
* Visualize protocol performance using MATLAB.

---

## Features

* UDP Socket Communication
* Stop-and-Wait ARQ Protocol
* Sequence Numbering
* Acknowledgement Mechanism
* Timeout Detection using `select()`
* Packet Retransmission
* Packet Loss Simulation
* MATLAB-Based Visualization
* Linux/Ubuntu Compatible

---

## Project Structure

```text
Reliable-Transport-Protocol-Framework/
│
├── udp_sender.cpp
├── udp_receiver.cpp
├── matlab_simulation.m
│
├── screenshots/
│   ├── sender_output.png
│   ├── receiver_output.png
│   ├── matlab_result1.png
│   └── matlab_result2.png
│
├── report/
│   └── Reliable_Transport_Protocol_Framework_Report.pdf
│
└── README.md
```

---

## System Architecture

```text
+------------+                          +------------+
|   Sender   | ---- Data Packet ------> |  Receiver  |
+------------+                          +------------+
       ^                                       |
       |                                       |
       +--------- ACK Packet ------------------+
```

### Working Principle

1. Sender creates a packet with a sequence number.
2. Packet is transmitted using UDP.
3. Receiver receives the packet and extracts the sequence number.
4. Receiver sends an acknowledgement (ACK).
5. Sender waits for ACK using a timeout mechanism.
6. If ACK is received, the next packet is transmitted.
7. If timeout occurs, the packet is retransmitted.
8. The process continues until all packets are successfully delivered.

---

## Technologies Used

* C++
* UDP Socket Programming
* Linux / Ubuntu
* GCC / G++
* MATLAB

---

## Compilation

Compile the sender and receiver programs:

```bash
g++ udp_sender.cpp -o sender
g++ udp_receiver.cpp -o receiver
```

---

## Execution

### Terminal 1 (Receiver)

```bash
./receiver
```

### Terminal 2 (Sender)

```bash
./sender
```

---

## Sample Output

### Sender

```text
Sender started...

Sent Packet 0
ACK received: 0

Sent Packet 1
Timeout -> Resending Packet 1

Sent Packet 1
ACK received: 1

Sent Packet 2
ACK received: 2

Sent Packet 3
ACK received: 3
```

### Receiver

```text
Receiver running...

Packet received:
Seq: 0
Data: Hello
ACK 0 sent

Packet received:
Seq: 1
Data: Packet 2

Simulating ACK loss...

Packet received:
Seq: 1
Data: Packet 2
ACK 1 sent
```

---

## Performance Analysis

### Observations

* Sender waits for ACK before transmitting the next packet.
* Timeout occurs when ACK is lost.
* Retransmission ensures reliable packet delivery.
* Packet loss is successfully recovered using Stop-and-Wait ARQ.

### Results

* Reliable communication achieved over UDP.
* Packet loss handled through retransmission.
* No packet loss in final delivery.
* Improved understanding of transport layer reliability.

---




