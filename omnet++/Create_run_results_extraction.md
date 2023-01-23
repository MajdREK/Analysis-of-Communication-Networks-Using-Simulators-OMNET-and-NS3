
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

Running Simulations
======================
The project will now be loaded into the OMNET++ IDE and you should see the project files in the "Project Explorer" window.

To run simulations, an OMNeT++ , open the "omnetpp.ini" file, located in the project's root directory of the project and then press the "Run" button on the toolbar or use the keyboard shortcut (Ctrl + F11) to start the simulation. The "Run" button is represented by a green arrow and can be found on the toolbar, which is located on the top of the screen.
The following is a topology we used : 
![topology](run_project.PNG?raw=true "Title")

Then the following window should appear. 

The simulation will begin running and you can view the OMNET++ QTenv in the "Simulation Output" window. 


* Network Description files (NED files): These files describe the topology of the network and the properties of the modules. They are written in the NED language and define the structure of the simulation. They specify the modules, channels, and connections used in the simulation.
* C++ implementation files (CC and H files): These files contain the implementation of the modules' behavior in the simulation. They are written in C++ and define the functions that are executed during the simulation.

* Configuration files (INI files): These files contain the configuration parameters for the simulation. They are typically in the form of key-value pairs. The main configuration file is the "omnetpp.ini" file, which contains the parameters that define the simulation's behavior, such as the number of runs, the duration of the simulation, and the seed for the random number generator.
* Makefile : It's used to build the project and is used to specify the compilation options and dependencies for the project.


## Help

If you have any question or clarifications related to OMNeT++, please check the documentation provided at the [OMNeT++ site](https://www.omnetpp.org) and
[INET](https://inet.omnetpp.org) sites. Here are the important documents.

1. OMNeT++ - [Install Guide](https://www.omnetpp.org/doc/omnetpp/InstallGuide.pdf), 
   [Simulation Manual](https://www.omnetpp.org/doc/omnetpp/SimulationManual.pdf), 
   [IDE User Guide](https://www.omnetpp.org/doc/omnetpp/UserGuide.pdf)

2. INET - [Documentation](https://inet.omnetpp.org/Introduction.html)

3. Results processing in OMNeT++ IDE - Chapter 10 of the [IDE User Guide](https://www.omnetpp.org/doc/omnetpp/UserGuide.pdf)


