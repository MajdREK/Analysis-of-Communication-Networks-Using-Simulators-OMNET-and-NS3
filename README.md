# Analysis of Communication Networks Using Simulators OMNET++ and NS3

## Introduction

Communication networks are an essential part of modern society, and their efficient and reliable operation is crucial for various applications such as the internet, telecommunication, and transportation systems. One of the key methods to analyze and design communication networks is through simulation, which allows for the testing and evaluation of different network configurations and protocols in a controlled environment.

This Master's Thesis studies the use of OMNET++ and NS3 network simulators for analyzing communication networks. The study compares the performance of the two simulators based on network performance criteria such as packet loss rate, throughput, end-to-end delay, jitter, collisions, number of events, and simulation time. This work is necessary due to a lack of research comparing the two simulators when it comes to simulating legacy telecommunication technologies such as CSMA/CD and PPP protocols and an increasing interest in newer protocols like Wi-Fi.

## Methodology

To conduct the study, two identical projects were created, one for each simulator. The default setup for the simulation included a wired peer-to-peer network with a client and a server running a single TCP application. The cable was configured with a data rate of 100Mbps and a delay of 0.4 microseconds. The client sent a preset number of packets to the server periodically at a configurable data rate. The simulation was run with two different cable types: full-duplex mode with PPP protocol and half-duplex mode with CSMA/CD protocol.

The following is a topology used:

![topology](topology.jpeg?raw=true "Title")

This is the socket diagram that shows what each machine does:

![socket diagram](socket.jpeg?raw=true "Title")

This table shows the default setup configuration:

![setup](setup.png)

## Why Choose these protocols

CSMA/CD and PPP protocols were chosen in this study as they are legacy telecommunication technologies that have been widely used in the past and have a significant impact on the performance of communication networks. Despite their widespread use, there is a lack of research comparing the performance of these protocols when simulated using OMNET++ and NS3. Additionally, simulating these mature and standardized protocols should result in accurate and reliable results, making them a valuable addition to the study.
Results

The results of the simulation were analyzed and compared based on the network performance criteria mentioned above.
The study found that when simulating the half-duplex CSMA/CD protocol, NS3 gave more realistic results than OMNET++. This is because NS3 allows the simulation of the Tx buffer size while OMNET++ has an unlimited Tx buffer size. Additionally, the study found that OMNET++ had a shorter simulation time than NS3.

## Conclusion

The study found that OMNET++ and NS3 both have their strengths and weaknesses when it comes to simulating communication networks. OMNET++ is a more general-purpose simulator that can simulate other fields besides networks, such as (such as transportation system, power systems and some biological system) while NS3 is more specialized in network simulations. However, when it comes to simulating legacy telecommunication technologies such as CSMA/CD and PPP protocols, the study found that NS3 gave more realistic results than OMNET++. Additionally, the study found that OMNET++ has modules ( The Tcp section of Inet framework ) that are unfinished and contain comments such as 'Todo'. OMNET++ could simulate the TxBuffer size if an extension such as TcpNsc was used.

