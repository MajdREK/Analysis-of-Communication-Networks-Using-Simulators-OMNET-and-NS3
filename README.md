
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

Usage
---------------------
* The project includes simulation codes for both OMNET++ and NS3. Once the project is set up, following the instructions in the README file, the user can run the simulation in Both OMNET++ and  NS3 .
* The simulation can be started, paused, and resumed at any time as per the user's preference. This allows the user to control the simulation and make adjustments as needed.
* The results of the simulation can be viewed in real-time on the OMNET++ or NS3 IDE while the simulation is running. This allows the user to monitor the progress of the simulation and make adjustments if necessary.
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
While both simulators have their strengths and weaknesses, the results of the simulation indicate 


Future work 
---------------------

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

Much work was done in comparing the differences
between OMNET++ and NS3 network simulators in terms of general instruction
or description of the software. On the other hand, fewer papers are comparing the
two simulators regarding simulating legacy telecommunication technologies such as
CSMA/CD and PPP protocols. Simultaneously, interest is high in relatively new
protocols such as Wi-Fi.

One may think that stimulating legacy protocols gives more accurate results.
However, interestingly, when we started this work, we noticed a significant contrast
in the implementation of both protocols ( CSMA & PPP ) in NS3 and Omnet++.

Comparing the two simulators regarding their support for legacy protocols
has important implications because NS3 and OMNET++ were first released after
protocols like CSMA/CD and PPP had matured and were finalized. While relatively
newer protocols like Wi-Fi are still changing, newer versions are continually being
released.

**What did we do?**

We have created two identical projects, one for each simulator. We have run the projects
, extracted the results, interpreted the results, and made conclusions.

Here we describe the default setup, ( note : you will find bellow how to reconfigure the network) :

We simulated a wired peer-to-peer network containing a client and a server running
a single TCP application. The cable is configured with a data rate of 100Mbps and
a delay of 0.4 microseconds.

Scenario: The client establishes a TCP connection with the server. Then, the client sends a
preset number of packets, (by default we set this number to 1000 packets with a packet size of 512 bytes), to the
server one packet at a time following a configurable data rate from 512Kbps to 512Mbps.
Depending on the configuration of the server, each packet the server receives, it can respond
with an echo packet whose size is equal to that of the received packet multiplied by
an echo factor. The echo can be immediate or after a configurable delay.
The time at which each application starts/stops and the time at which data trans-
mission begins are configurable and are specified for each simulation session we
run.

After all packets are sent, the client application closes the TCP connection, and
both applications exit. For the simulation time, we set 100 seconds as the time limit
to allow the execution until the end.

In this experiment, the setup described above is simulated with two different cable
types: in full-duplex mode with PPP protocol, which ensures data transmission in
both directions simultaneously, and in half-duplex mode with CSMA/CD protocol,
which ensures data transmission in both directions, but only in one direction at a
time.

The following is a topology we used : 
![topology](topology.jpeg?raw=true "Title")


This is the socket diagram that shows what each machine does:
![socket diagram](socket.jpeg?raw=true "Title")


This table shows the default setup configuration:

![setup](setup.png?raw=true "Title")

**How to run the projects?**

For the installlation of the software, check the folder ![installation](installation)

In the folders [ns3](ns3) and [omnet++](omnet++) you find the source code of the projects for both simulators.

For Ns3 you place the source code with the bash file under the **scratch** folder and then you run the bash file.

For Omnet++ you place the **WiredTcpClientServer** folder under the **samples** folder of Omnet++.

There following are two videos that show how to run the code. 

Omnet++ : [https://www.youtube.com/watch?v=aMrikVXSh4Q](https://www.youtube.com/watch?v=bYftoLBCXA4)

Ns3 : [https://www.youtube.com/watch?v=bYftoLBCXA4](https://www.youtube.com/watch?v=bYftoLBCXA4)

**How to change the code and reconfigure the setup?**

The code is commented and there is a web-based documentation you can browse to further understand the C++ code, you can find it under the folder [documentation](documentation). Unzip the files then open index.html from each resultant folder. Also you can check the folder ![code_explained](code_explained) that further explains the code.

To make configuration changes, you can work on the omnet.ini file for Omnet++ and run_point_to_point.sh file for Ns3.

Omnet++ : To better understand Omnet++ ".ini" files use this link [https://doc.omnetpp.org/omnetpp/IDE-Overview.pdf](https://doc.omnetpp.org/omnetpp/IDE-Overview.pdf)
When you run the simulation however, you can use the popup to pick the configuration you want. 
The ".ini" file can be used to change the setup, like adding another machine...

Ns3 : the file run_point_to_point.sh is a bash file that runs the simulation and passes the desired arguments, then
it extracts the program output and saves it to a file and greps the results.
You can change the passed parameters, to better understand the function of these parameters run the command : 
./waf -v --run "scratch/tcpClientServer.cc --help"


To change the NS3 setup/topology, you need to change the function **simulate()** in the ".cc" file. This link should be useful [How to setup Ns3 topology?](https://www.nsnam.org/docs/tutorial/html/building-topologies.html)

**What are the results and how to interpret them?**

Under the [results](results) folder you find the results table for both simulators.

This ![jupyter notebook](render_results_graphs.ipynb) file renders the results in the form of graphs.

For the interpretation of the graphs, read the document ![results interpretation](results_interpretation.pdf)

**Where to go from here?**

The code available in this repostry is configurable. changing the **Echo factor** and/or **Echo Delay** can and will change the behaviour of the network which can be further studied.

**Conclusion**

We have concluded that Ns3 gives more accurated and realistic results, and that Omnet++ is more genral purpose than Ns3.
We also found that Omnet++ has modules, in this exact subject, that require more development and are obsolete. the exact
function that we needed was the control of TxBuffer size which was available only in NS3 with the default setup.
( Omnet++ provides this functionality with an extension called ![TcpNsc](https://inet.omnetpp.org/docs/users-guide/ch-transport.html) )

**Final notes**

This repository studied the diffrence between NS3 and Omnet++ in terms of the performace and behaviour for client server wired connection.
Feel free to post issues and patches.






Create , run and results extraction 
======================

This part explains the files used for our programme.

In the NS3 root directory, under the scratch folder,  three files are created :

* WiredTcpClientServer.cc
* run_point_to_point.sh
* wired.txt

These files are used to simulate a network with a server and client, transmitting data over a wired channel using two different types of protocols (CSMA/CD and PPP), and to collect and analyze the results of the simulation. Each file has a specific purpose. The WiredTcpClientServer.cc file contains the main C++ code for the simulation, while the run_point_to_point.sh file is used to configure and run the simulation. The wired.txt file is used to store the results of the simulation.

The source code for each file can be found in the NS3_code folder, which is located under the NS3 folder in this Github repository.

1- WiredTcpClientServer.cc
---------------------
This file contains the C++ code for the wired tcp client-server simulation. It contains the main code for the simulation where the behavior of the nodes, the network topology and other simulation parameters are defined.

Here are some tasks that are included in this file:

* Creating nodes: The code creates the nodes that will be used in the simulation, such as clients and servers.
* Setting up the network topology: The code defines the network topology, such as the number of nodes, links between nodes, and any other network-related information.
* Installing protocols: The code installs the protocols that will be used in the simulation, such as TCP, IPV4 and CSMA.
* Setting up the application: The code sets up the application that will be used in the simulation, such as a client-server application.
* Configuring the simulation: The code configures the simulation parameters, such as the simulation time, the number of packets to be sent, the packet size, the data rate and other parameters.
* Running the simulation: The code runs the simulation using the NS-3 simulation engine.
* Collecting and printing the results: The code collects the simulation results and prints them to the standard output or a file.


2- run_point_to_point.sh
---------------------

The run_point_to_point.sh file is a shell script that is used to automate the process of running the simulation. It contains commands to set up the environment, invoke the NS-3 simulation engine, and execute the simulation. The script performs the following tasks:
* It first removes any existing file named wired.txt, using the command rm -f scratch/wired.txt
* It then runs a loop that iterates over different data rates (0.5Mbps, 1Mbps, 2Mbps, 4Mbps, 8Mbps, 16Mbps, 32Mbps, 64Mbps, 128Mbps, 256Mbps, 512Mbps) and for each iteration, it invokes the simulation engine by running the command ./waf -v --run
* The simulation file name is passed as an argument, in this case, it's "scratch/WiredTcpClientServer.cc"
* It specifies various simulation parameters such as the use of the CSMA protocol, channel data rate, delay, error rate, packet count, packet size, start and stop time for client and server, and the length of the simulation.
* The simulation output is redirected to a file named wired.txt using the command | tee -a scratch/wired.txt
* After the loop finishes, the script ends.

Overall, this script automates the process of running the simulation multiple times with different parameters and collects the results in one file.

3- wired.txt
---------------------

The wired.txt file is used to store the results of the simulation that is run by the WiredTcpClientServer.cc file , it's used to store the output of the simulation . It contain information such as packet loss rate, throughput, end-to-end delay, jitter, collisions, number of events, and simulation time, which are collected by the simulation and written to the file for later analysis. 

The contents of the file will depend on the specific implementation of the simulation, and how the results are being collected and formatted. The file may be in a plain text format, and can be opened and viewed using a text editor such as Notepad , TextEdit or VS Code.

4- Steps required 
--------------------- 
**Step 1:**  Navigate to the Scratch directory.

**Step 2:**  Create three new files in the "scratch" directory, named "WiredTcpClientServer.cc", "run_point_to_point.sh", and "wired.txt" by typing the following command:
```
$ touch WiredTcpClientServer.cc
$ touch run_point_to_point.sh
$ touch wired.txt
```
**Step 3:** Open the "WiredTcpClientServer.cc" file in your preferred text editor and copy and paste the C++ code for the simulation into this file.

**Step 4:**  Open the "run_point_to_point.sh" file and copy and paste the code for the simulation into this file.

**Step 5:**  Now, you can run the simulation by executing the "run_point_to_point.sh" file using the following  command in the kali Linux terminal.

```
$ ./scratch/run_point_to_point.sh
```
Note: This command can only be executed in the root directory of your NS-3, which is ns-3.34, where the script "waf" is also located.

**Step 6:**  Once the simulation is complete, you can view the results in the "wired.txt" file, and use them to analyze the performance of the network.

**Step 7:** To search for and match specific patterns in the "wired.txt" file  the following  command in the kali Linux terminal is used .

```
$ grep -E "client intended packets sent" scratch/wired.txt
```
The specific pattern being searched for in this command is "client intended packets sent", which is output by the WiredTcpClientServer.cc program . The file being searched is scratch/wired.txt, which is the file where the results of the simulation are stored.

The command searches for the pattern "client intended packets sent" in the wired.txt file and returns all the lines that contain this output. This command is useful for extracting specific information from the output file and making it easier to analyze the simulation results.



 
