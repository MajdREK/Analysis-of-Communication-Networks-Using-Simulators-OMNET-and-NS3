
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



