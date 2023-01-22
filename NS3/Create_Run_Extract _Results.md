
Create , run and results extraction 
======================

This part explains the files used for our programme.

In the NS3 root directory, under the scratch folder, I created three files:

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

**Step 5:**  Now, you can run the simulation by executing the "run_point_to_point.sh" file using the command "./waf --run wired" in the command prompt or terminal.

```
$ ./scratch/run_point_to_point.sh

```
Note: this command is excutble only in the ns-3.34 directory whre the waf s










Windows Subsystem for Linux (WSL) is a compatibility layer that allows running Linux command-line tools natively on Windows. It provides a Linux-compatible kernel interface developed by Microsoft, which can then be used to run a user-space environment such as Ubuntu, Debian, Kali, or Alpine Linux. This allows developers to use their preferred Linux tools and environments on Windows, while still being able to access the Windows file system and other Windows features. 

Please note that your computer should meet the minimum system requirements for WSL, and your Windows version should be at least Windows 10 version 1607 or later with the latest updates installed.

Installing Windows Subsystem for Linux (WSL) through the command line involves the following steps:

**Step 1:**  Open Windows PowerShell as an administrator by pressing the Windows key + X and selecting "Windows PowerShell (Admin)".
**Step 2:**  Enable the Windows Subsystem for Linux feature by running the following command:
```
$ dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
```
**Step 3:**  Enable the Virtual Machine feature by running the following command:
```
$ dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```
**Step 4:**  Restart your computer when prompted to complete the installation of the Windows Subsystem for Linux feature.

For more information, please visit the official website of Microsoft https://learn.microsoft.com/de-de/windows/wsl/install ,  https://learn.microsoft.com/en-us/windows/wsl/install and https://learn.microsoft.com/en-us/windows/wsl/install-manual .

2- Install Linux distribution  of your choice on WSL
---------------------
Open the Microsoft Store and search for a Linux distribution, such as Kali linux, and install it.

Once the Linux distribution is installed, open the command prompt and type "**Kali**" to start the Linux shell.

Follow the on-screen instructions to set up your user account and password.

Update the package list by running the command: 
```
$ sudo apt-get update && apt-get upgrade
```

3- Install the necessary libraries for NS-3
---------------------
NS-3 is a discrete-event network simulator, and it depends on several libraries to provide its functionality. The necessary libraries for NS-3 are:

* GCC (GNU Compiler Collection): NS-3 is written in C++ and requires GCC to build and run.
* Python: NS-3 uses Python as its primary scripting language, and it requires Python >= 2.7 to be installed on the system. So it's necessary to have a recent version of Python installed on your system.
* PyViz: PyViz is a Python-based visualization tool that can be used to visualize the simulation results from NS-3.
* Python Bindings: NS-3 uses Python bindings to provide an interface between C++ code and Python scripts (pybindgen >= 0.17.0).
* Gnuplot: Gnuplot is used to generate plots and graphs from simulation data.
* SQLite3: SQLite3 is used to store and retrieve simulation data.
* OpenMPI: OpenMPI is used for parallel simulations.
* GTK: GTK is used for creating graphical user interfaces.
* Netanim: Netanim is an animation tool for visualizing network topologies and protocols.
* Boost: Boost is a collection of libraries for C++ that provide support for things like threading, signals, and system calls.
* LibXml2: LibXml2 is a library for parsing and manipulating XML files.
* Gnu Scientific Library (GSL): This library provides a wide range of mathematical functions, including statistics, linear algebra, and optimization.
* QT: NS-3 includes a QT-based GUI, so it is necessary to have QT installed on the system.

The libraries used in my application are provided in the following command:
```
$ sudo apt-get install gcc g++ git mercurial cmake libc6-dev  libc6-dev-i386 g++-multilib gdb valgrind gsl-bin libgsl0-dev flex bison 
libfl-dev tcpdump wireshark sqlite3 libsqlite3-dev libxml2 libxml2-dev libgtk2.0-0 libgtk2.0-dev vtun lxc uncrustify doxygen graphviz 
imagemagick texlive texlive-extra-utils texlive-latex-extra texlive-font-utils dvipng dia libboost-filesystem-dev openmpi-bin 
openmpi-common openmpi-doc libopenmpi-dev gnuplot
```

Please note that this is not a complete list of libraries that may be required for NS-3, and the specific libraries required may vary depending on the version of NS-3 and the features you plan to use.

4- Downloading a release of NS-3 as a source archive
---------------------
This option is for the new user who wishes to download and experiment with the most recently released and packaged version of NS-3. NS-3 publishes its releases as compressed source archives, sometimes referred to as a tarball. Any release of NS-3 is availble at https://www.nsnam.org/releases/.
Let's assume that you, as a user, wish to build NS-3 in a local  directory called ns3. If you adopt the workspace directory approach, you can get a copy of a release by typing the following into your Linux distribution by running these commands:

```
$ mkdir ns3
$ cd ns3
$ wget https://www.nsnam.org/release/ns-allinone-3.34.tar.bz2
$ tar xvjf ns-allinone-3.34.tar.bz2
```
Notice: **wget** is a command-line tool for downloading files from the internet in the other hand the command **tar xvjf** is used to extract the content of a tarball file that is compressed using bzip2 algorithm and has a .tar.bz2 file extension. It allows users to unpack the content of the archive and access the files and directories inside it, this command is commonly used to install NS-3 software from its source code. 

After this , you should have a directory called ns-allinone-3.34 , there you can see a number of files and directories by typing these commands:

```
$ cd ns-allinone-3.34
$ ls
bake  build.py  constants.py  netanim-3.108 ns-3.34  README.md  util.py
```


5- Building NS-3 
---------------------
You are now ready to build NS-3 Simulator. If you downloaded using a tarball you should have a directory called something like ns-allinone-3.34 under your ~/ns3 directory and then type the following command:
```
$  ./build.py --enable-examples --enable-tests
```
You will see lots of compiler output messages displayed as the build script builds the various pieces of NS-3.

To check if the build is successfully completed type this command :
```
$  ./waf --run hello-simulator
```
6- How to create and run a project NS-3 
---------------------
When creating a new project in NS-3, it is necessary to create it under the  **"scratch"** folder.

The  **"scratch"** folder is a directory provided by NS-3 that is intended for users to place their own simulation scripts and sample code. 

You could find the **"scratch"** folder under **"ns-3.34"** folder.

To add a new project to the **"scratch"** folder in NS-3, you can start by opening the Linux terminal and navigating to the **"ns-3.34"** directory. Once you are in the correct directory, navigate to the "scratch" folder by running the command
```
$  cd scratch
```
To confirm that you are in the correct directory, you can use the  **"pwd"** command, which will display the current working directory.
Once you are in the "scratch" folder, you can create a new file by running the command
```
$  touch filename.ccd
```
Note: **"filename"** is the name of your new file.
Next, open the new file in a text editor by running the command
```
$  nano filename.cc
```
and write your C++ code in the new file, then save it. However, you can use other text editors such as VS Code or sublime text and they will work perfectly fine.

Finally, to run your new file, you can use the command 
```
$  ./waf -v --run "scratch/filename"
```
The **"./waf"** command should be run in the root directory of your NS-3 installation. This is the directory where the "waf" script is located.
