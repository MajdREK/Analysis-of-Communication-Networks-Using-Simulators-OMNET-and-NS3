# Analysis of Communication Networks Using Simulators OMNET++ and NS3

## Introduction
---------------------
Communication networks are an essential part of modern society, and their efficient and reliable operation is crucial for various applications such as the internet, telecommunication, and transportation systems. One of the key methods to analyze and design communication networks is through simulation, which allows for the testing and evaluation of different network configurations and protocols in a controlled environment.

This Master's Thesis studies the use of OMNET++ and NS3 network simulators for analyzing communication networks. The study compares the performance of the two simulators based on network performance criteria such as packet loss rate, throughput, end-to-end delay, jitter, collisions, number of events, and simulation time. This work is necessary due to a lack of research comparing the two simulators when it comes to simulating legacy telecommunication technologies such as CSMA/CD and PPP protocols.

## Motivation
---------------------
CSMA/CD and PPP protocols were chosen in this study as they are legacy telecommunication technologies that have been widely used in the past and have a significant impact on the performance of communication networks. Despite their widespread use, there is a lack of research comparing the performance of these protocols when simulated using OMNET++ and NS3. Additionally, simulating these mature and standardized protocols should result in accurate and reliable results, making them a valuable addition to the study.

## Technical requirements
---------------------
* OMNET++ 5.6.2 
* NS3 3.34
* Windows operating system


## Usage
---------------------
* This repository includes simulation codes for both OMNET++ and NS3. Once the project is set up, following the instructions in the README file, the user can run the simulation in Both OMNET++ and  NS3 .
* The simulation allows the user to adjust various parameters such as client data rate, protocol settings (PPP, CSMA/CD), packet size, client delay, server delay, packet echoed to the client, to analyze the impact of different scenarios on network performance.
* The results can be exported from the IDE/Console in the form of graphs and tables. These results can then be analyzed further using other software such as Excel or Google Colab to gain deeper insights and draw more accurate conclusions.


## Methodology
---------------------
We conducted the study by creating two identical projects, one for each simulator (OMNET++ 5.6.2 and NS3 3.34). The simulation was run on a windows OS. The simulation setup was as follows:
* Network topology: wired peer-to-peer network with a client and a server.

* Transmission medium: cable configured with a delay of 0.4ms and a data rate of 100Mbps.

* Protocols: CSMA/CD CSMA/CD in half-duplex and PPP full-duplex mode.


* Application: single TCP application running on the client and server.

* Simulation time: 100 seconds.

* Packet generation: The client establishes a TCP connection with the server, then sends a preset number of packets (1000 packets with a packet size of 512 bytes) to the server. The data rate on the client side is increasing from 0.5Mbps to 512Mbps.

* Echo response: The server responds with an echo packet of the same size of the received packet, with no delay. The echo factor can be modified.

* Queue: DropTail queue is used with default configuration

* Time at which each application starts/stops: The time of the start is 0 and stop will be when all packets that are intended to be sent are sent.

The following is a topology we used : 
![topology](topology.jpeg?raw=true "Title")


This table shows the default setup configuration:

![setup](setup.png?raw=true "Title")


## Documentation
---------------------
Here is a highlight of the structure of the repository:
- Two Folders: `ns3`, `omnet++` each containing the following :
    - The simulation program code ( commented code )
    - The results is raw excel table 
    - A readme for how to create the project and run and get the results ( with video too )
    - A readme that explains the C++ code
    - A readme for the installation steps of the simulator
    - A web based documentation site in form or archieve ( extract it and open index.html 
- A results folder that contains the following:
  - Results of the simulation 
  - Python code (colab) used for plotting graphs
  - Results interpretation

To make configuration changes, you can:
  - Change the omnet.ini file for Omnet++ ( To better understand Omnet++ ".ini" files use this link [https://doc.omnetpp.org/omnetpp/IDE-Overview.pdf](https://doc.omnetpp.org/omnetpp/IDE-Overview.pdf) )
When you run the simulation however, you can use the popup to pick the configuration you want.
  - Change run_point_to_point.sh file for Ns3 ( It is a bash file that runs the simulation and passes the desired arguments, then it extracts the program output and saves it to a file and greps the results. You can change the passed parameters, to better understand the function of these parameters run the command :
./waf -v --run "scratch/tcpClientServer.cc --help" ).

## Conclusion
---------------------
The results of the simulation were analyzed and compared based on the network performance criteria mentioned above.
The study found that when simulating the half-duplex CSMA/CD protocol, NS3 gave more realistic results than OMNET++. This is because NS3 allows the simulation of the Tx buffer size while OMNET++ has an unlimited Tx buffer size. Additionally, the study found that OMNET++ had a shorter simulation time than NS3.

The study found that OMNET++ and NS3 both have their strengths and weaknesses when it comes to simulating communication networks. OMNET++ is a more general-purpose simulator that can simulate other fields besides networks such as transportation systemand  while NS3 is more specialized in network simulations. However, when it comes to simulating legacy telecommunication technologies such as CSMA/CD and PPP protocols, the study found that NS3 gave more realistic results than OMNET++. Additionally, the study found that OMNET++ has modules ( The Tcp section of Inet framework ) that are unfinished and contain comments such as 'Todo'. OMNET++ could simulate the TxBuffer size if an extension named TcpNsc was used, but it does not do that by default like NS3 does.
