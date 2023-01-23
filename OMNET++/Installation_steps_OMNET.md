
OMNeT++ Installation on Windows
======================

This guide will walk you through the process of installing OMNeT++ on a Windows operating system.


Installation Steps
---------------------

1- Create a new folder on your desktop called "OMNeT++".

2- Download the OMNeT++ version 5.6.2 installer for Windows from the official website (https://omnetpp.org/download/old/).

3- Extract the downloaded file to the "OMNeT++" folder.

4- Open the "mingwenv" terminal from the extracted folder.

5- Run the following command to configure the installation:
```
$ ./configure
```

6- Run the following command to build the software:

```
$ make
```

7- Once the installation is complete, verify the installation of OMNeT++ and ensure that all the sample files are installed correctly, you can run one of the sample simulations that come with the installation. by using the following command in the "mingwenv" terminal:
```
$ cd samples/aloha
```
This will navigate to the "aloha" sample simulation directory. Then you can run the simulation by using the following command:

```
$ ./aloha
``` 
This will open the OMNET++ Qtenv GUI for running simulations , in this case the ALOHA project.  If the simulation runs successfully , it means that OMNeT++ is installed correctly and all the sample files are working properly.

8-  you can start the OMNeT++ IDE by running the following command in the "mingwenv" terminal:
```
$ omnetpp
``` 
Additional Notes
---------------------
* The INET framework will automatically be installed to provide the user with the primary library for the simulation of communication networks.

* INET (Internet Protocol (IP) Network Simulation Framework) is a simulation framework that provides the necessary modules and libraries to simulate communication networks. It is a widely used framework in OMNeT++ and is included by default with the installation of OMNeT++. INET provides a wide range of features and functionalities to simulate communication networks such as: 
                                                            Support for IPv4, IPv6, and MPLS protocols.
                                                            Support for wired and wireless networks.
                                                            Support for transport protocols such as TCP, UDP, and SCTP.
                                                            Support for routing protocols such as OSPF, BGP, and AODV.
                                                            Support for mobility models, such as random walk, random waypoint, and group mobility.
                                                            Support for network devices such as switches, routers, and hosts.
                                                            Support for network visualization and analysis tools.

* The INET framework is designed to be highly modular and extensible, making it easy to add new protocols and models to the simulation. It also provides a large number of example simulations that can be used as a starting point for creating new simulations.

* One of the main reasons for using INET is that it provides a comprehensive set of libraries and modules to simulate communication networks, which saves a lot of time and effort when developing new simulations. Instead of having to create all the protocols, models, and modules from scratch, developers can use the ones provided by INET, which have already been tested and validated.

* Another advantage of INET is that it is widely used in the research and academic communities, which means that there are many resources and a large community of users that can provide help and support.

* In summary, INET is a highly useful and versatile simulation framework that provides a wide range of modules and libraries for simulating communication networks. It is widely used in OMNeT++ and provides a lot of features that makes it easy to develop new simulations and save time and effort.
