OMNeT++ Project Creation and Execution
======================

This guide will walk you through the process of creating and running a project in OMNeT++.

It's important to note that the below informations may vary depending on the complexity and requirements of the simulation.


Step 1: Start the OMNeT++ IDE
---------------------
Open the OMNeT++ IDE by running the "omnetpp" executable fromin the "mingwenv" terminal.

Step 2: Create a new project
---------------------
Go to "File" -> "New" -> "Project...", select the "OMNeT++ Simulation Model" template, and click "Next". 

Step 3: Name the project and select a location
---------------------
Give a name to the project and select a location for the project files, and click "Next". 


Step 4: Choose the initial Contents
---------------------
In this step choose the **"Empty project with 'src and simulation' folder"** , and click "Next". 


Step 6: Finish the project creation
---------------------
by clicking finish afetr selcting the contents of the project.

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


