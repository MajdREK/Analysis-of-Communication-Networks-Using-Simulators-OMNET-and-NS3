
Analysis of Communication Networks Using Simulators OMNET++ and NS3
======================

Introduction
---------------------
The objective of the Master's thesis project is to investigate and compare the performance of the OMNET++ and NS3 network simulators.
The project creates identical simulations for each simulator and measures key network performance metrics such as packet loss rate, throughput, end-to-end delay, jitter, collisions, number of events, and simulation time.  The focus of the project is on simulating legacy telecommunications technologies such as CSMA/CD and PPP protocols. The results of the simulations are analyzed in depth to determine the relative performance of each simulator.

Technical requirements
---------------------
* OMNET++ 5.6.2 
* NS3 3.34
* Windows operating system
* C++ programming knowledge

Setup
---------------------
* Install windows subsystem for linux (wsl)
* Install OMNET++ and NS3, installation guides and required files are available in the respective Github repositories.
* Clone or download the project repository, one for OMNET++ and one for NS3.
* Follow the guide provided in the repository's README file to set up and create new projects for each simulator.
* Follow the guide and video tutorials provided on how to run the code and extract the results.

Methodology
--------------------- 
We conducted the study by creating two identical projects, one for each simulator (OMNET++ 5.6.2 and NS3 3.34). The simulation was run on a windows OS. The simulation setup was as follows:
* Network topology: wired peer-to-peer network with a client and a server.

* Transmission medium: cable configured with a delay of 0.4ms and a data rate of 100Mbps.

* Protocols: CSMA/CD CSMA/CD in half-duplex  and PPP full-duplex mode.


* Application: single TCP application running on the client and server.

* Simulation time: 100 seconds.

* Packet generation: The client establishes a TCP connection with the server, then sends a preset number of packets (1000 packets with a packet size of 512 bytes) to the server. The data rate on the client side is increasing from 0.5Mbps to 512Mbps.

* Echo response: The server responds with an echo packet with the same size of the received packet, with no delay. The echo factor can be modified.

* Queue: DropTail queue is used with default configuration

* Time at which each application starts/stops: The time of the start is 0 and stop will be when all packets that are intended to be sent are sent.

The following is a topology we used : 
![topology](topology.jpeg?raw=true "Title")


This table shows the default setup configuration:

![setup](setup.png?raw=true "Title")

Usage
---------------------
* The project includes simulation codes for both OMNET++ and NS3. Once the project is set up, following the instructions in the README file, the user can run the simulation in Both OMNET++ and  NS3 .
* The simulation can be started, paused, and resumed at any time as per the user's preference. This allows the user to control the simulation and make adjustments as needed.
* The results of the simulation can be viewed in real-time on the OMNET++ or NS3  while the simulation is running. This allows the user to monitor the progress of the simulation and make adjustments if necessary.
* The simulation allows the user to adjust various parameters such as client data rate, protocol settings (PPP, CSMA/CD), packet size, client delay, server delay, packet echoed to the client, to analyze the impact of different scenarios on network performance.
* The results can be exported from the IDE in the form of graphs and tables. These results can then be analyzed further using other software such as Excel or Google Colab to gain deeper insights and draw more accurate conclusions.

Results
---------------------
The results of the simulation will  include the following network performance metrics:

* Packet loss rate
* Throughput
* End-to-end delay
* Jitter
* Collisions
* Number of events
* Simulation time

Conclusion
---------------------
The results of the simulation show that both OMNET++ and NS3 are powerful network simulators that can be used to analyze different scenarios and network performance. 
While both simulators have their strengths and weaknesses, the results of the simulation indicate that NS3 has higher packet loss rates and jitter values, while OMNET++ has zero packet loss and lower jitter values. NS3 has a decreasing trend in end-to-end delay as the client data rate increases, while OMNET++ has an unchanged delay until a critical data rate is reached. In terms of collisions and throughput, OMNET++ has less collisions and higher throughput than NS3. Additionally, OMNET++ generates more events in the simulation process. The choice of simulator ultimately depends on the specific requirements of the network scenario being simulated.

In conclusion, while both NS3 and OMNET++ have their strengths and weaknesses, they both provide valuable insights into network performance and can be used to evaluate and optimize network design. The choice of simulator depends on the specific requirements of the network scenario being simulated. OMNET++ is suitable for simulating scenarios with a high level of accuracy and detail, while NS3 is more suitable for scenarios that require a more efficient simulation process.


Future work 
---------------------
In terms of future work, there are several areas that could be further explored to improve the understanding of the performance of NS3 and OMNET++. One area of focus could be to investigate the impact of different network protocols on the results obtained in this study. For example, by comparing the performance of the two simulators when using TCP and UDP protocols. Additionally, the impact of different network topologies, such as mesh and star networks, on the performance of the two simulators could be studied.
Another area of focus could be to investigate the performance of the two simulators in more complex network scenarios, such as those involving multiple clients and servers. This would allow for a more in-depth analysis of how the different characteristics of the simulators impact the overall performance of the network.
It could also be interesting to compare the performance of the two simulators in wireless networks, and see if the results are similar or different from those obtained in this study for wired networks.
Finally, it would be beneficial to evaluate the performance of the two simulators using real-world measurements and data, in order to validate the results obtained in this study and to better understand the real-world applicability of the two simulators.

Note
---------------------
This project is based on a Master's thesis at the University of Applied Sciences Berlin and is intended for academic and research purposes only.

Contact 
---------------------
You can contact the author by email or through the GitHub repository, if you have any questions or issues with the project.

Additional Resources 
---------------------
* Code explanations for each software are provided in the Github repositories.
* Video tutorials on how to run the code and extract results are available on the project's Github repositories

