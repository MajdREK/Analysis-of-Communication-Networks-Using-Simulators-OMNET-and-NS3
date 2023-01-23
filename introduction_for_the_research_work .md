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

Overview

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


This table shows the default setup configuration:

![setup](setup.png?raw=true "Title")

