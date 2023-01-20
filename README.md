# Analysis-of-Communication-Networks-Using-Simulators-OMNET-and-NS3
Master Thesis in University of Applied Sciences Berlin : Communication networks are analyzed using NS3 and OMNET++. The two simulators are studied and compared based on network performance criteria such as packet loss rate, throughput, end-to-end delay, jitter, collisions, number of events, and simulation time.

**Why this work was needed?** 

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
, extracted the results, interpreted the results, and made conclusion.

Here we describe the default setup, ( note : you will find bellow how to reconfigure the network) :

We simulated a wired peer-to-peer network containing a client and a server running
a single TCP application. The cable is configured with a data rate of 100Mbps and
a delay of 0.4 microseconds.

Scenario: The client establishes a TCP connection with the server. Then, the client sends a
preset number of packets, fixed at 1000 packets with a packet size of 512 bytes, to the
server periodically following a configurable data rate from 512Kbps to 512Mbps.
Depending on the configuration of each packet the server receives, it can respond
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

This table shows the default setup configuration:

![Alt text](setup.png?raw=true "Title")

**How to run the projects?**
For the installlation of the software, check the folder **installation**

There following are two videos that show how to run the code. 

Omnet++ : [https://www.youtube.com/watch?v=aMrikVXSh4Q](https://www.youtube.com/watch?v=bYftoLBCXA4)

Ns3 : [https://www.youtube.com/watch?v=bYftoLBCXA4](https://www.youtube.com/watch?v=bYftoLBCXA4)

**How to change the code and reconfigure the setup?**

The code is commented and there is a web-based documentation you can browse to further understand the C++ code, you can find it under the folder **documentation**. Also you can read the document **C++ code explaination** that further explains the code.

To make configuration changes, you can work on the omnet.ini file for Omnet++ and run_point_to_point.sh file for Ns3.

Omnet++ : To better understand Omnet++ ".ini" files use this link [https://doc.omnetpp.org/omnetpp/IDE-Overview.pdf](https://doc.omnetpp.org/omnetpp/IDE-Overview.pdf)
When you run the simulation however, you can use the popup to pick the configuration you want. 
The ".ini" file can be used to change the setup, like adding another machine...

Ns3 : the file run_point_to_point.sh is a bash file that run the simulation and passes the desired arguments, then
it extracts the program output and saves it to a file and greps the results.
You can change the passed parameters, to better understand the function of these parameters run the command : 
./waf -v --run "scratch/tcpClientServer.cc --help"


To change the NS3 setup/topology, you need to change the function **simulate()** in the ".cc" file. This link should be useful [How to setup Ns3 topology?](https://www.nsnam.org/docs/tutorial/html/building-topologies.html)

**How to interpret the graph?**

Read the document **results interpretation**

**Where to go from here?**

The code available in this repostry is configurable. changing the **Echo factor** and/or "EchoDelay" can and will change the behaviour of the network which can be further studied.

**Final notes**

This repository studied the diffrence between NS3 and Omnet++ in terms of the performace and behaviour for client server wired connection.
Feel free to post issues and patches.
 
