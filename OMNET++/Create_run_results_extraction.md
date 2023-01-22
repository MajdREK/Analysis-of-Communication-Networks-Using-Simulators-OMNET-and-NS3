OMNeT++ Project Creation and Execution
======================

This guide will walk you through the process of creating and running a project in OMNeT++.

It's important to note that the below informations may vary depending on the complexity and requirements of the simulation.

 Start the OMNeT++ IDE
---------------------
Open the OMNeT++ IDE by running the "omnetpp" executable fromin the "mingwenv" terminal.

 Create a new project
---------------------
Go to "File" -> "New" -> "Project...", select the "OMNeT++ Simulation Model" template from the menu, and click "Next". 

Name the project and select a location
---------------------
Give a name to the project and select a location for the project files, and click "Next". 


Choose the initial Contents
---------------------
In this step choose the **"Empty project with 'src and simulation' folder"** , and click "Next". 


 Finish the project creation
---------------------
Click "Finish" to create the project.

Required Files
======================
An OMNeT++ project typically includes the following files:

 INI file
---------------------
The INI file is a plain-text file that contains the configuration parameters for an OMNeT++ simulation. It includes information such as:

* The number of runs: Specifies how many times the simulation will be executed.
* The duration of the simulation: Specifies the length of time that the simulation will run.
* Network topology: Information about the modules, channels, and connections used in the simulation.
* Module parameters: Values for the parameters of the modules in the simulation, such as the number of packets to send or the data rate of a channel.
* Simulation parameters: Information about the overall behavior of the simulation, such as the seed for the random number generator.
* Output files: Information about the files that will be used to store the simulation results, such as scalar files, vector files, and histogram files.

NED files (*.ned)
---------------------
NED files are Network Description files that describe the topology of the network and the properties of the modules. They are written in the NED language and define the structure of the simulation. They specify:

* The modules: Describes the different types of modules used in the simulation and their properties.
* Channels: Specifies the channels that are used to connect the modules.
* Connections: Describes how the modules and channels are connected to form the network topology.

C++ implementation files (.cc and .h)
---------------------
C++ implementation files contain the source code that implements the behavior of the modules in the simulation. They are written in C++ and define the functions that are executed during the simulation. The .cc files contain the function's implementation while the .h files contain the declarations of functions and variables that are used in the implementation files.

Makefile
---------------------
A makefile is a simple text file used to specify the compilation options and dependencies for the project. It is used to automate the process of building the project and ensures that the code is built in the correct order.

Running the Project
======================
The project will now be loaded into the OMNET++ IDE and you should see the project files in the "Project Explorer" window.

Open the "omnetpp.ini" file, located in the project's root directory of the project and then press the "Run" button on the toolbar or use the keyboard shortcut (Ctrl + F11) to start the simulation. The "Run" button is represented by a green arrow and can be found on the toolbar, which is located on the top of the screen.

The simulation will begin running and you can view the OMNET++ QTenv in the "Simulation Output" window. 


* Network Description files (NED files): These files describe the topology of the network and the properties of the modules. They are written in the NED language and define the structure of the simulation. They specify the modules, channels, and connections used in the simulation.
* C++ implementation files (CC and H files): These files contain the implementation of the modules' behavior in the simulation. They are written in C++ and define the functions that are executed during the simulation.

* Configuration files (INI files): These files contain the configuration parameters for the simulation. They are typically in the form of key-value pairs. The main configuration file is the "omnetpp.ini" file, which contains the parameters that define the simulation's behavior, such as the number of runs, the duration of the simulation, and the seed for the random number generator.
* Makefile : It's used to build the project and is used to specify the compilation options and dependencies for the project.




















1- WiredTcpClientServer.cc
---------------------
1- WiredTcpClientServer.cc
---------------------



To create a new module, you can right-click on the project and select "Add new module" and then select the type of module you want to create, for example, simple module, compound module, or network. you can also configure the properties of the module, such as its name and parameters.

Click "Finish" to create the project.

Once the project is created, you can open the "omnetpp.ini" file, which is located in the


Sure, here is an example of how you can include information about the INI and NED files in a "readme" file for an OMNeT++ project:

Project Files
The "omnetpp.ini" file is the main configuration file for the simulation. It contains the parameters that define the simulation's behavior, such as the number of runs, the duration of the simulation, and the seed for the random number generator.

The "*.ned" files are the Network Description files, which describe the topology of the network and the properties of the modules. These files are written in the NED language and define the structure of the simulation. They specify the modules, channels, and connections used in the simulation.

The ".cc" and ".h" files are the source code files that implement the behavior of the modules in the simulation. They are written in C++ and define the functions that are executed during the simulation.

The "makefile" is used to build the project and is used to specify the compilation options and dependencies for the project.

"README" file is a documentation file that provides information about the project and its usage.

It's important to note that the above list is not exhaustive and the actual project files may vary depending on the complexity and requirements of the simulation.

Project Execution
Open the "omnetpp.ini" file, located in the project's root directory, and configure the simulation's parameters such as the number of runs, the duration of the simulation, and the seed for the random number generator.
To run the simulation, you can press the "Run" button in the IDE or use the command line in the "mingwenv" terminal by typing "./<project_name> -u Cmdenv -c <config_name>".
After the simulation is completed, you can view the results using the built-in visualization tools, such as the "Result Analysis" and "Scalar Results" windows.
Project Files
The "omnetpp.ini" file is the main configuration file for the simulation. It contains the parameters that define the simulation's behavior, such as the number of runs, the duration of the simulation, and the seed for the random number generator.

Project Execution
Open the "omnetpp.ini" file, located in the project's root directory, and configure the simulation's parameters such as the number of runs, the duration of the simulation, and the seed for the random number generator.
To run the simulation, you can press the "Run" button in the IDE or use the command line in the "mingwenv" terminal by typing "./<project_name> -u Cmdenv -c <config_name>".
After the simulation is completed, you can view the results using the built-in visualization tools, such as the "Result Analysis" and "Scalar Results" windows.
Project Files
The "omnetpp.ini" file is the main configuration file for the simulation. It contains the



Project Execution
Open the "omnetpp.ini" file, located in the project's root directory, and configure the simulation's parameters such as the number of runs, the duration of the simulation, and the seed for the random number generator


Required Files
The "omnetpp.ini" file is the main configuration file for the simulation. It contains the parameters that define the simulation's behavior, such as the number of runs, the duration of the simulation, and the seed for the random number generator.
The "*.ned" files are the Network Description files, which describe the topology of the network and the properties of the modules. These files are written in the NED language and define the structure of the simulation. They specify the modules, channels, and connections used in the simulation.
The ".cc" and ".h" files are the source code files that implement the behavior of the modules in the simulation. They are written in C++ and define the functions that are executed during the simulation.
The "makefile" is used to build the project and is used to specify the compilation options and dependencies for the project.
"README" file is a documentation file that provides information about the project and its usage.

An empty project in OMNeT++ typically contains two main folders: the "src" folder and the "simulation" folder.

The "src" folder contains the source code files for the project, including the ".cc" and ".h" files, which implement the behavior of the modules in the simulation.

The "simulation" folder contains the configuration files for the simulation, including the "omnetpp.ini" file, which contains the parameters that define the simulation's behavior, such as the number of runs, the duration of the simulation, and the seed for the random number generator.

Additionally, the project may also contain other folders and files, such as:

The "*.ned" files are the Network Description files, which describe the topology of the network and the properties of the modules. These files are written in the NED language and define the structure of the simulation. They specify the modules, channels, and connections used in the simulation.

The "makefile" is used to build the project and is used to specify the compilation options and dependencies for the project.

"README" file is a documentation file that provides information about the project and its usage.

It's important to note that the above list is not exhaustive and the actual project files may vary depending on the complexity and requirements of the simulation.

Creating a client-server network in OMNeT++ typically requires several files, including:

Network Description files (NED files): These files describe the topology of the network and the properties of the modules. They are written in the NED language and define the structure of the simulation. They specify the modules, channels, and connections used in the simulation. For a client-server network, you will need to create a NED file that defines the client and server modules, as well as the communication channel between them.

C++ implementation files (CC and H files): These files contain the implementation of the modules' behavior in the simulation. They are written in C++ and define the functions that are executed during the simulation. For a client-server network, you will need to create implementation files for the client and server modules.

Configuration files (INI files): These files contain the configuration parameters for the simulation. They are typically in the form of key-value pairs. The main configuration file is the "omnetpp.ini" file, which contains the parameters that define the simulation's behavior, such as the number of runs, the duration of the simulation, and the seed for the random number generator. You will need to edit this file to configure the client-server network simulation.

Makefile : It's used to build the project and is used to specify the compilation options and dependencies for the project.

README file : is a documentation file that provides information about the project and its usage.

After the simulation is completed, you can view the results using the built-in visualization tools, such as the "Result Analysis" and "Scalar Results" windows.
Results extraction 


i need to get a usfel readme from all the above information in order to get a nice readme about how can i create a simple topolgy like client server (wired network) and the fonctionalty for differnts files needed such as .cc .h .ned .ini make. what to do exctly to run the project ist it from the ini file and than wht i am going to get where i can see the simulation working and how the results are extracted ???  









1- WiredTcpClientServer.cc
---------------------
1- WiredTcpClientServer.cc
---------------------








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


