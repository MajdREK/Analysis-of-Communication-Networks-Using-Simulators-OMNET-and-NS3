WiredTcpClientServer.cc file explanation
======================

The wiredtcpclientserver.cc file is a C++ program that simulates a network with a server and client, transmitting data between them over a wired channel.
*  The file starts by including headers for different NS-3 modules, such as core-module, point-to-point-module, csma-module, internet-module, applications-module, netanim-module, and flow-monitor-module.
*  It also includes a map container from the C++ standard library.
* It defines a number of constants such as CLIENT_MACHINE_NUM and SERVER_MACHINE_NUM, which represent the indices of the client and server nodes in the simulation.
*  It also disables the console logging for the default logging function.
* It defines a number of parameters for the simulation such as the client's data rate, the number and size of packets sent by the client, the start and stop times for the client and server, and the length of the simulation.
*  It also includes a template class called SimpleHistogram, which is used to count occurrences of a particular value.
*  The simulation is defined in the main function and it involves creating the nodes (client and server), setting up the network topology, installing protocols, setting up the application, configuring the simulation, running the simulation, and collecting and printing the results.

* The namespace ns3 contains a number of classes, including Application, Socket, and Packet.
* The class PacketCreationTimeTag is defined, which is a subclass of the Tag class.
* The PacketCreationTimeTag class has a static method GetTypeId which returns a unique identifier for this class and sets the parent class and constructor.
* The PacketCreationTimeTag class also has a public method SetSimpleValue and GetSimpleValue which sets and gets the value of a private member variable m_simpleValue.
* There are two global variables defined ServerMacTxBackoffOccurCount and ClientMacTxBackoffOccurCount which are both initially set to 0.
* There are two global functions defined ServerMacTxBackoffOccur and ClientMacTxBackoffOccur. These functions take in a string and a pointer to a Packet object and increment the corresponding global variable count.

* The TcpEchoClient class is an implementation of an Application in NS3. It is used to create a TCP client that can send a specified number of packets of a specified size to a specified server at a specified data rate and starting time.
* It has several member variables such as a socket pointer, the address of the peer, packet size, number of packets, data rate, send event, running status, send time, packets sent/received, bytes sent/received, packets transmission time, maximum/minimum received packet size, histograms for received/sent packet sizes, send interval, and various statistics related to timing.
* It also has several methods such as Setup, ShowStats, HandleRead, HandleClose, ConnectionSucceeded, ConnectionFailed, StartApplication, StopApplication, SendPacket, ScheduleTx, and others for setting up and managing the application's behavior.
* The TcpEchoClient has several functions, including: 

**Setup()** The "Setup" method is used to set up the TcpEchoClient Application by assigning values to its attributes. It takes several parameters as input such as a socket object, the network address of the local machine and the peer machine that the application will connect to as a server, the packet size, the total number of packets to be sent, the data rate at which the traffic will be generated, and the send time for the first packet. The method then sets up the callbacks for the socket object, and binds the local address to the socket. The application then connects to the specified peer address. The method also logs some information about the setup process, such as the time it was called, the bind response, and the scheduling of the first packet send.

**ShowStats()**  is a method that prints out various statistics about the client's performance. It logs information such as the number of packets sent, received, and lost, the minimum and maximum packet sizes, the average packet delay, and more.

**HandleRead()**   method is called when the socket object receives a packet from the peer. The method takes a single argument, which is a pointer to the socket object that received the packet. Inside the method, it reads the data from the socket and logs some information about the packet, such as its size and the time it was received. The method also increments the number of packets received and the number of bytes received. Additionally, the method updates the minimum and maximum packet sizes, and adds the packet size to the histogram of received packet sizes. After that, the method calls the SendPacket method to send another packet to the peer.
        
**HandleClose()**   method is a private method of the TcpEchoClient class. It is called when the socket is closed. The method takes a Ptr<Socket> socket as an argument, which represents the socket that is being closed. It does not perform any action within the method, it is typically used to clean up or log any information related to the closed socket. However, in this case, it is not implemented and is an empty method.

**ConnectionSucceeded()**  method is a callback function that is called when the client's socket successfully establishes a connection with the server. It is passed the socket object as a parameter, which can be used to access information about the connection, such as the remote endpoint's address and port. This function is typically used to perform any necessary setup or configuration for the connection, such as configuring the send and receive buffers or enabling flow control. The exact behavior of this function will depend on the specific implementation of the TcpEchoClient class and the needs of the application using it.
  
**ConnectionFailed()**  this method is called when the socket fails to connect to the server.

**StartApplication()**  this method is called when the simulation starts. In this method, the client sets up its socket by binding to a local address and connecting to a peer server address. It also initializes some variables to  track its sent and received packets, bytes and other statistics.

**StopApplication()**  this method is called when the simulation stops. 

**SendPacket()**  method is responsible for sending data packets over the socket. It is called by the ScheduleTx method, which is scheduled to run at specific intervals. This method first creates a new packet of the specified size, then attaches a "PacketCreationTimeTag" to it, which stores the time at which the packet was created. The packet is then sent over the socket using the Send method, and the statistics such as the number of packets sent, bytes sent, and the size histogram of sent packets are updated. Additionally, the first packet send time and the last packet send time are stored to compute the average send time and the average throughput.

**ScheduleTx()**  method is responsible for scheduling the transmission of packets. It is typically called when the application starts, and it sets up an event to send the first packet at a specified time. After the first packet is sent, the method is called again to schedule the next packet transmission, and so on. The time between each packet transmission is determined by the data rate specified in the Setup method. This allows the application to send packets at a specified rate. The method uses the Simulator class from the ns-3 library to schedule the event, which ensures that the transmission of packets is coordinated with the simulation's event loop.
        
The TcpEchoClient class also has several member variables such as m_socket, m_peer, m_packetSize, m_nPackets, m_dataRate, m_sendEvent, m_running, m_sendTime, m_packetsSent, m_packetsRecieved, m_bytesSent, m_bytesRecieved, m_packetsTransmissionTime, and m_maxRecievedPacketSize, m_minRecievedPacketSize which are used to store the client's socket, the server's address, the size of the packets, the number of packets, the data rate, the event for sending packets
  
  
* The TcpEchoServer class is an implementation of the ns-3 Application class. It is used to create a server that listens on a specific port and IP address, receives packets, and sends back an echo of the received packet after a specified delay. 
  
The class has several methods that are called at different stages of the server's lifetime:
  
**Setup()** This method is called at the start of the simulation to set up the server. It assigns the local IP address and port to listen on, as well as the delay time for sending back the echo packet and the echo factor (which determines the size of the echo packet relative to the received packet).

**StartApplication()**  This method is called when the server starts. It sets up the socket and binds it to the local IP address and port.

**StopApplication()**  This method is called when the server stops. It can be used to clean up any resources used by the server.

**HandleRead()** This method is called when a packet is received by the server. It reads the packet, logs information about it, and sends back an echo packet after the specified delay.

**HandleAccept()** This method is called when a connection is accepted by the server. It logs information about the connection.

**HandleClose()**  This method is called when a connection is closed. It logs information about the closed connection.

**ConnectionSucceeded()**: This method is called when a connection is successfully established. It logs a message.

**ConnectionFailed()** This method is called when a connection attempt fails. It logs a message.

**SendEchoPacket()** This method sends the echo packet back to the client, it logs the packet size and the time at which it was sent.

**ShowStats()** This method logs various statistics about the server's performance, such as the number of packets sent and received, the number of bytes sent and received, and the minimum and maximum packet sizes.

The class also maintains several member variables to keep track of statistics such as the number of packets sent and received, the number of bytes sent and received, and the minimum and maximum packet sizes. The class also has histograms to keep track of packet size statistics.
  
  
* The code creates a simulation with 2 nodes: a client and a server
* The channel or link between the nodes can either be a CSMA channel or a point-to-point channel, depending on the value of the variable "use_csma"
* The channel attributes such as data rate and delay are set based on the values of the variables "channel_data_rate" and "channel_delay"
* The queue size for the channel is also set using the variable "point_to_point_queue_size"
* Error rate is also set for the devices using the variable "error_rate"
* The IP addresses for the nodes are assigned using the IP address helper
* A TcpEchoServer and TcpEchoClient application are created and added to the corresponding nodes
* The start and stop time for the client and server applications are set using the variables "client_start_time", "client_stop_time", "server_start_time", and "server_stop_time"
* Other parameters for the client and server applications are also set such as packet size, packet count, data rate, and echo delay.
  
  
====> In summary, the provided C++ code is a simulation of a client-server network using the ns-3 library. The simulation creates two nodes, one acting as the client and one acting as the server, and connects them via either a CSMA or Point-to-Point channel. Error rate is also introduced to the simulation through the use of a RateErrorModel. The client and server applications, TcpEchoClient and TcpEchoServer, respectively, are then installed on the corresponding nodes. The TcpEchoClient sends packets to the TcpEchoServer, which then echoes them back with a delay and a specified echo factor. The simulation also includes the ability to capture pcap traces for the devices, and several statistics are collected and printed out at the end of the simulation such as packets sent and received, bytes sent and received, and packet delay.




 
  
 
  
  
  
  
  

      


























