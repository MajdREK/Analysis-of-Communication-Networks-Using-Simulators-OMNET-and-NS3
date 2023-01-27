

OMNET++ Result
======================
Unlike NS3, in OMNET++ each client data rate has to be simulated separately for each mode (full-duplex using PPP protocol and half-duplex using CSMA protocol). In this part, we will explain how and where to get the results from our program, which are used for the graphs and saved in the Excel file.


1- Application layer statistic
---------------------
To get the results of the Application layer, you have first : 
- to choose the configuration that you intended to  simulate:
    - Ethernet_CSMACD_Half_duplex
    - PPP
- Then you have to choose the data rate: (0. 5Mbps, 1Mbps, 2Mbps, 4Mbps, 8Mbps, 16Mbps, 32Mbps, 64Mbps, 128Mbps, 256Mbps, 512Mbps) 

![pppcsma.PNG](pppcsma.PNG?raw=true "Title")
![datarate.PNG](datarate.PNG?raw=true "Title")

The result of the application layer will be generated in the console of the OMNET++ Qtenv IDE 
- Simulation time 
- event 
- Client-side
    - recived bytes 
    - sent bytes
    - recived packets 
    - sent packets
    - throughput 
    - lastSentPacketTime
    - firstSentPacketTime
    - lastRcvdPacketTime
    - delay
    - avrgDelayCounter
    - avrgDelayAcc
    - client reciption average jitter 
- Server-side
    - recived bytes 
    - sent bytes
    - recived packets 
    - sent packets
    - throughput 
    - lastSentPacketTime
    - firstSentPacketTime
    - delay
    - avrgDelayCounter
    - server reciption average jitter


![applicationstatistic.PNG](applicationstatistic.PNG?raw=true "Title")

2- Phsical layer statistic
---------------------
All the physical layer statistic is extracted from the file .anf (for more information see the readme file of the Create_run_results_extraction)



Here will only need some specific data to search for, the data needed are :

- Client and server-side
    - txPk:count ==> to get the transmitted packet
    - txPk:sum(packetBytes) ==> to get the transmitted bytes
    - rxPkOk:count ==> to get the received packet 
    - rxPkOk:sum(packetBytes) ==> to get the received bytes 
    - bits/sec*  ==> to get the throughput 
    - collision:count ==> to get the number of collision
![phy.PNG](phy.PNG?raw=true "Title")

