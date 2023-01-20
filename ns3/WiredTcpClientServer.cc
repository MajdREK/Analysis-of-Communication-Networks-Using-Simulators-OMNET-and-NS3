/* 
This C++ program is to simulate a network with a server and client, transmit data between them over a wired channel , 
and collect various statistics about the transmission , using the Network Simulator 3 (ns-3).  
It includes various headers for different ns-3  modules as well as some functionalities that are used throughout the program 
in order to  studied and compared the network performance criteria such as packet loss rate, throughput, 
end-to-end delay, jitter, collisions, number of events, and simulation time. 
It sets up a simulation environment with two nodes (representing the client and server) and a TCP/IP stack on each node.
*/
/*
The code begins by including all needed modules.
*/
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/flow-monitor-module.h"
#include <map> 
/*
Next, a number of constants are defined, such as CLIENT_MACHINE_NUM and SERVER_MACHINE_NUM, 
which represent the indices of the client and server nodes in the simulation.
*/
// a reference number for the client machine object in the code
#define CLIENT_MACHINE_NUM 0
// a reference number for the server machine object in the code   
#define SERVER_MACHINE_NUM 1  
// console logging will be disabled for the default logging function 
//(The ns-3 logging facility can be used to monitor or debug the progress of simulation programs.)
#define DISABLE_LOG true      
/*
handle and manage logging  function
https://www.nsnam.org/docs/release/3.17/manual/html/logging.html
https://www.nsnam.org/docs/manual/html/logging.html
https://www.nsnam.org/docs/release/3.7/tutorial/tutorial_21.html
https://www.nsnam.org/docs/release/3.16/doxygen/group__logging.html
*/
#define DISABLE_LOG true           
#if defined DISABLE_LOG 
#if DISABLE_LOG == true
#undef NS_LOG_UNCOND 
#define NS_LOG_UNCOND(...) std::cout<<__VA_ARGS__<<std::endl
#define NS_LOG_UNCOND_ON_OFF(...)
#endif  
#else   
#define NS_LOG_UNCOND_ON_OFF NS_LOG_UNCOND
#endif 
#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)
#define DEBUG_VAR(X) NS_LOG_UNCOND(STRINGIZE(X) << " : " << X)
/*
The simulation is defined by a number of parameters, such as the client's data rate, the number and size of packets sent by the client, 
the start and stop times for the client and server, and the length of the simulation.
*/
#define ERROR_RATE 0               
#define CHANNEL_DATA_RATE "100Mbps"
#define CHANNEL_DELAY "0.0004ms"
#define POINT_TO_POINT_QUEUE_SIZE "99999p"
#define SERVER_ECHO_FACTOR 1
#define SERVER_ECHO_DELAY 0
#define CLIENT_DATA_RATE "160Mbps"
#define CLIENT_PACKETS_COUNT 10000
#define CLIENT_PACKET_SIZE 500
#define CLIENT_START_TIME 0.1f
#define CLIENT_SEND_TIME 0.1f
#define SERVER_START_TIME 0.0f
#define CLIENT_STOP_TIME 4999.0f
#define SERVER_STOP_TIME 4999.0f
#define SIMULATION_LENGTH 5000.0f
#define NEW_RENO_ENABLED false
#define USE_CSMA false
/*
There is also a template class called SimpleHistogram, which is used to count occurrences of a particular value. 
This class has a std::map member variable called m_map, which stores the counts of values, and a number of methods
for adding values to the histogram and printing it out. 
==> This class records the frequency of every value it recieves wich is used to build 
a histogram of packet sizes for both  the server and client machine.
https://www.nsnam.org/docs/release/3.19/doxygen/classns3_1_1_histogram.html
https://www.nsnam.org/docs/release/3.19/doxygen/histogram_8cc_source.html
https://www.nsnam.org/docs/release/3.28/doxygen/classns3_1_1_histogram.html
https://www.nsnam.org/docs/release/3.18/doxygen/histogram-test-suite_8cc_source.html
https://www.nsnam.org/docs/release/3.18/doxygen/histogram_8h_source.html
*/
template <class T>
class SimpleHistogram
{
 private:
  std::map<T, uint32_t> m_map;
 public:
  SimpleHistogram() {}
  void AddOne(T v)
  {
    if (m_map.find(v) == m_map.end())
    {
      m_map[v] = 1;
    }
    else
    {
      m_map[v] = m_map[v] + 1;
    }
  }
  void Print(std::ostream &stream)
  {
    for (auto pair : m_map)
    {
      stream << pair.first << " ==> " << pair.second << std::endl;
    }
  }
};

namespace ns3
{
  /*
 The namespace ns3 contains all classes that inherent from NS3.
 */
  class Application;
  class Socket;
  class Packet;

  /**
  * A tag is a meta information that can be put inside the TCP packet header it can be used to store any information depending 
  * on the need. 
  * Here a  class "PacketCreationTimeTag" is created  on the sender side,  the received can then calculate the application level delay
  * for Every machine before sending a packet with  inserting a timecreation tag into  the header of a TCP packet. 
  * The "PacketCreationTimeTag" class is derived from the Tag class of ns-3. This class is used to tag packets with the time they were
  * created, so that the delay between the packet creation from the client sde  and the packet reception from the server side 
  * can be measured. 
  * The "PacketCreationTimeTag" class has a member variable called m_simpleValue, which stores the time a packet was created,
  * and a number of methods for setting and getting this value, as well as for serializing and deserializing the tag.
  * https://www.nsnam.org/docs/release/3.18/doxygen/classns3_1_1_tag.html#details
  * https://www.nsnam.org/docs/release/3.18/doxygen/tag_8h_source.html
  * https://www.nsnam.org/docs/release/3.18/doxygen/tag_8cc_source.html
  * https://www.nsnam.org/docs/release/3.10/manual/html/packets.html
  * https://www.nsnam.org/doxygen/d1/d36/classns3_1_1_tag.html
  * https://www.nsnam.org/docs/release/3.2/manual/manual_29.html
  * https://groups.google.com/g/ns-3-users/c/IWs4QKcHdYg?pli=1
  * https://www.youtube.com/watch?v=aJxM1P9XLCQ&t=1031s
  */
  class PacketCreationTimeTag : public Tag
  {
    public:
      static TypeId GetTypeId(void);
      virtual TypeId GetInstanceTypeId(void) const;
      virtual uint32_t GetSerializedSize(void) const;
      virtual void Serialize(TagBuffer i) const;
      virtual void Deserialize(TagBuffer i);
      virtual void Print(std::ostream &os) const;
      void SetSimpleValue(double value);
      double GetSimpleValue(void) const;
    private:
      double m_simpleValue;
  };
  TypeId PacketCreationTimeTag::GetTypeId(void)
  {
    static TypeId tid = TypeId("ns3::PacketCreationTimeTag")
                            .SetParent<Tag>()
                            .AddConstructor<PacketCreationTimeTag>()
                            .AddAttribute("SimpleValue",
                                          "A simple value",
                                          EmptyAttributeValue(),
                                          MakeDoubleAccessor(&PacketCreationTimeTag::GetSimpleValue),
                                          MakeDoubleChecker<double>());
    return tid;
  }
  TypeId PacketCreationTimeTag::GetInstanceTypeId(void) const
  {
    return GetTypeId();
  }
  uint32_t PacketCreationTimeTag::GetSerializedSize(void) const
  {
    return sizeof(m_simpleValue);
  }
  void PacketCreationTimeTag::Serialize(TagBuffer i) const
  {
    i.WriteDouble(m_simpleValue);
  }
  void PacketCreationTimeTag::Deserialize(TagBuffer i)
  {
    m_simpleValue = i.ReadDouble();
  }
  void PacketCreationTimeTag::Print(std::ostream &os) const
  {
    os << "v=" << (double)m_simpleValue;
  }
  void PacketCreationTimeTag::SetSimpleValue(double value)
  {
    m_simpleValue = value;
  }
  double PacketCreationTimeTag::GetSimpleValue(void) const
  {
    return m_simpleValue;
  }
  int ServerMacTxBackoffOccurCount = 0;
  void ServerMacTxBackoffOccur  (std::string context, Ptr<const Packet> packet)
  {
    ServerMacTxBackoffOccurCount++;
  }
  int ClientMacTxBackoffOccurCount = 0;
  void ClientMacTxBackoffOccur  (std::string context, Ptr<const Packet> packet)
  {
    ClientMacTxBackoffOccurCount++;
  }
  /**
    * A class "Application", which is a class for defining network applications in NS3. In this code the Application calss
    * encapsulates all the logic of the client and server application, which are used to simulate the needed behavior, 
    * building the topology and to install it on target host machines in the network.
    * The class "TcpEchoClient" , is responsible for sending packets to the server and receiving a responses from the server.
    * The  class "TcpEchoServer" , is responsible for receiving packets from the client and sending responses back to 
    * the client. 
    * Overall, the "TcpEchoClient" and "TcpEchoServer" classes work together to simulate the behavior of a client and a server
    * in a network.  The client sends packets to the server, and the server receives and responds it.
    * "TcpEchoClient" ==> https://github.com/samueljero/snake/blob/master/ns-3-dev/src/applications/model/tcp-echo-client.cc
    * "TcpEchoServer" ==> https://github.com/samueljero/snake/blob/master/ns-3-dev/src/applications/model/tcp-echo-server.cc
  */
  class TcpEchoClient : public Application
        {
          public:
                  TcpEchoClient();
                  virtual ~TcpEchoClient();
                  /**
                  * ns3 classes use "GetTypeId" to provide access to type "reflection".
                  * ns3::TypeId Class is a unique identifier for an interface. This class records a lot of meta-information about a subclass of the Object base class.
                  * http://www.cs.sjsu.edu/~pearce/modules/lectures/oop/types/reflection/ReflectionCpp.htm
                  * https://www.nsnam.org/docs/release/3.15/doxygen/classns3_1_1_type_id.html#details
                  * https://www.nsnam.org/docs/release/3.15/doxygen/type-id_8cc_source.html
                  * https://www.nsnam.org/docs/release/3.24/doxygen/classns3_1_1_type_id.html
                  */
                  static TypeId GetTypeId(void);
                  /**
                  * This method is called at the network setup . It sets up the Application by assining the attributes to given values
                  * the callbacks of the socket object are set here 
                  * @param socket Socket object passed as params so that the consumer of this class can use a socket of his own, this allows him to listen for socket events
                  * @param local the network address of the machine this app is running on
                  * @param peer  the network address of the machine that the app will connect to as a server
                  * @param packetSize the size of every emitted data packet
                  * @param nPackets the total number of the data packets that the app will be sending
                  * @param dataRate the rate of which the application's traffic will be generated 
                  * @param sendTime the time in which the first data packet is sent
                  */
                  void Setup(
                    Ptr<Socket> socket, 
                    InetSocketAddress local, 
                    InetSocketAddress peer,
                    uint32_t packetSize,
                    uint32_t nPackets, 
                    DataRate dataRate , 
                    double sendTime);
                  /**
                  * This method is called after the simulation stops and before it is destroyed it logs all the statistics of the application layer 
                  * of the client side.
                  */
                  void ShowStats();
          private:
                  /**
                  * This method is called when a packet is received, it logs to the console if thats enabled and it updates the statistics 
                  * like the number of received packets/bytes.
                  */
                  void HandleRead(Ptr<Socket> socket);
                  /**
                  * This method is called  when TCP connection is closed ,it does nothing but logging the event to the console
                  */
                  void HandleClose(Ptr<Socket> socket);
                  /**
                  * This method is called  when TCP connection starts, it schedules the first send event to "m_tSend"
                  */
                  void ConnectionSucceeded(Ptr<Socket> socket);
                  /**
                  * This method is called when the TCP connection fails, it aborts the simulation immediatly
                  */
                  void ConnectionFailed(Ptr<Socket> socket);
                  /**
                  * This method is called by ns3 core when the application's start.The start time is
                  * set when building the network, here we bind our socket and try to connect to the server
                  */
                  virtual void StartApplication(void);
                  /**
                  * This method is called automatically by ns3 core when the time comes to stop the application.
                  * the application's stop time is set when building the network.
                  */
                  virtual void StopApplication(void);
                  /**
                  * This method sends a single packet to the destination which is in our case the server and updates statistics.
                  * when the TCP connection is establshed, a call for this method is scheduled. After every execution this methods 
                  * scheduals the next call of itself using "TcpEchoClient::ScheduleTx" , this pattern ensures a continous emition 
                  * of traffic. The traffic is generated until the application is closed or until all packets are sent .
                  */
                  void SendPacket(void);
                  /**
                  * This is a helper method to Schedule the next packet send
                  */
                  void ScheduleTx(void);
                  
                  /**
                  *  socket object [https://docs.oracle.com/javase/tutorial/networking/sockets/definition.html]
                  */
                  Ptr<Socket> m_socket;
                  /**
                  *  server address
                  */
                  Address m_peer;
                  /**
                  *  packet side
                  */
                  uint32_t m_packetSize;
                  /**
                  *  number of packets to be sent
                  */
                  uint32_t m_nPackets;
                  /**
                  *  server application port
                  */
                  uint16_t m_peer_port;
                  /**
                  *  client machine address
                  */
                  Ipv4Address m_local;
                  /**
                  *  client application datarate
                  */
                  DataRate m_dataRate;
                  /**
                  *  used to store the schdualed event for next send , so that it is cancelled when needed
                  */
                  EventId m_sendEvent;
                  /**
                  *  a flag to indicate if this  application is emmiting traffic 
                  */
                  bool m_running;
                  /**
                  *  the timestamp in which to start emmiting traffic
                  */
                  double m_sendTime;
                  /**
                  *  number of packets send
                  */
                  uint32_t m_packetsSent;
                  /**
                  *  number of echo packets received
                  */
                  uint32_t m_packetsRecieved;
                  /**
                  *  the number of bytes sent
                  */
                  uint32_t m_bytesSent;
                  /**
                  *  the number of bytes received
                  */
                  uint32_t m_bytesRecieved;
                  /**
                  *  an accumilator used to compute average  received packet delay 
                  */
                  double m_packetsTransmissionTime;
                  /**
                  *  used to store the size of the biggest received packet
                  */
                  uint32_t m_maxRecievedPacketSize;
                  /**
                  *  used to store the size of the smallest received packet
                  */
                  uint32_t m_minRecievedPacketSize;
                  /**
                  *  histogram for the size of received packets
                  */
                  SimpleHistogram<uint32_t> m_RecievedPacketsSizeHistogram;
                  /**
                  *  histogram for the size of sent packets
                  */
                  SimpleHistogram<uint32_t> m_sentPacketsSizeHistogram;
                  /**
                  *  the time interval after which to send a packet periodically following the given datarate
                  */
                  double m_sendInterval;
                  double m_firstPacketSendTime = 0.0d,m_lastPacketSendTime = 0.0d; // recording when the traffic started and finished to compute throughout
                  double m_average_send_time = 0.0;
                  double m_average_receive_time = 0.0;
                  double m_lastPacketReceiveTime = 0.0f;
                  double m_PreviousPacketDelay  = 0.0f;                                // last received packer delay
                  // Jitter = Sum( Abs( Delay( Packet_(m) ) - Delay(  Packet_(m-1) ) ) ) / Number of received packets
                  double m_jitterAccumulator = 0.0f;                                // sum of all packet delays that is later devided over the number of received packets to get the jitter
        };
        TcpEchoClient::TcpEchoClient()
          : m_socket(0),
            m_peer(),
            m_packetSize(0),
            m_nPackets(0),
            m_dataRate(0),
            m_sendEvent(),
            m_running(false),
            m_packetsSent(0),
            m_packetsRecieved(0),
            m_bytesSent(0),
            m_bytesRecieved(0)
        {
        }

        TcpEchoClient::~TcpEchoClient()
        {
          m_socket = 0;
        }
        /* static */
        TypeId TcpEchoClient::GetTypeId(void)
        {
          static TypeId tid = TypeId("TcpEchoClient")
                                  .SetParent<Application>()
                                  .SetGroupName("Tutorial")
                                  .AddConstructor<TcpEchoClient>();
          return tid;
        }
         /**
         * This method  "TcpEchoClient::Setup" is used to configure the client's parameters such as the data rate,
         * packet size, and number of packets to send.It create also an object for the TCP socket that will be used 
         * to send data to the server and  sets up the event handler for  the socket when it is connected to the server.
        */
        void TcpEchoClient::Setup(
                                  Ptr<Socket> socket,
                                  InetSocketAddress local,
                                  InetSocketAddress peer,
                                  uint32_t packetSize,
                                  uint32_t nPackets, 
                                  DataRate dataRate, 
                                  double sendTime
                                  )
        {
          m_socket = socket;
          m_peer = peer;
          m_packetSize = packetSize;
          m_nPackets = nPackets;
          m_dataRate = dataRate;
          m_local = local.GetIpv4();
          m_maxRecievedPacketSize = 0;
          m_minRecievedPacketSize = 99999;
          m_packetsTransmissionTime = 0;
          m_sendInterval =  m_packetSize * 8 / static_cast<double>(m_dataRate.GetBitRate());
          m_sendTime = sendTime;
          NS_LOG_UNCOND_ON_OFF("Client setup ...");  

          std::cout.setf(std::ios::fixed, std::ios::floatfield);
          std::cout.setf(std::ios::showpoint);
          std::cout.precision(10);
          NS_LOG_UNCOND("data rate : " << double(m_dataRate.GetBitRate()) << " bps");
          NS_LOG_UNCOND("m_sendInterval : " << m_sendInterval << " seconds");

          m_socket->SetRecvCallback(MakeCallback(&TcpEchoClient::HandleRead, this));
          m_socket->SetConnectCallback(
              MakeCallback(&TcpEchoClient::ConnectionSucceeded, this),
              MakeCallback(&TcpEchoClient::ConnectionFailed, this));
          m_socket->SetCloseCallbacks(MakeCallback(&TcpEchoClient::HandleClose, this), MakeCallback(&TcpEchoClient::HandleClose, this));
        }
        /**
        * This method "StartApplication" is called when the client starts sending packets to the server.
        * It creates first a socket and than  binds it to an address and port, and starts the process of sending data to the server.
        * It happens at the time specified by the CLIENT_START_TIME.
        */
        void TcpEchoClient::StartApplication(void)
        {
          m_running = true;
          m_packetsSent = 0;
          m_packetsRecieved = 0;
          m_bytesRecieved = 0;
          m_bytesSent = 0;
          InetSocketAddress local = InetSocketAddress(m_local, 1212);
        #if not defined DISABLE_LOG
          const auto clientBindRes = m_socket->Bind(local);
        #else
          m_socket->Bind(local);
        #endif
          NS_LOG_UNCOND("TcpEchoClient::StartApplication At : "<<Simulator::Now().GetSeconds() << " second");
          NS_LOG_UNCOND_ON_OFF("Client bind response : " << clientBindRes << " => " << (!clientBindRes ? " success " : " failed "));
          m_socket->Connect(m_peer);
          NS_LOG_UNCOND_ON_OFF("Client will schedual a send ...");
        }
        /**
        * This method "StopApplication" is called when the client stops sending packets.  It closes the socket and stops sending packets.
        * It happens at the time specified by the CLIENT_STOP_TIME.
        */
        void TcpEchoClient::StopApplication(void)
        { 
        }
        /**
        * This method "ShowStats" is useed to display result of the Appllication level of client side .
        */
        void TcpEchoClient::ShowStats()
        {
          NS_LOG_UNCOND("----------------   Appllication level stats for client app -------------");
          NS_LOG_UNCOND("client intended packets sent         : " << m_nPackets <<" packets");
          NS_LOG_UNCOND("client packets sent                  : " << m_packetsSent <<" packets");
          NS_LOG_UNCOND("client packets received              : " << m_packetsRecieved<<" packets");
          NS_LOG_UNCOND("client bytes sent                    : " << m_bytesSent<< " bytes");
          NS_LOG_UNCOND("client bytes received                : " << m_bytesRecieved<< " bytes");
          NS_LOG_UNCOND("client average received packet size  : " << double(m_bytesRecieved) / double(m_packetsRecieved) << " bytes");
          NS_LOG_UNCOND("client min received packet size      : " << m_minRecievedPacketSize << " bytes");
          NS_LOG_UNCOND("client max received packet size      : " << m_maxRecievedPacketSize << " bytes");
          NS_LOG_UNCOND("client packet total transmission time : " << double(m_packetsTransmissionTime) << " seconds");
          NS_LOG_UNCOND("client average received packet delay : " << double(m_packetsTransmissionTime) / double(m_packetsRecieved)<< " seconds");
          NS_LOG_UNCOND("client first packet send time : " <<  this->m_firstPacketSendTime<<" seconds");
          NS_LOG_UNCOND("client last packet send time : " <<  this->m_lastPacketSendTime<<" seconds");
          NS_LOG_UNCOND("client average send time : " <<  m_average_send_time / m_packetsSent<<" seconds");
          NS_LOG_UNCOND("client average receive time : " <<  m_average_receive_time / m_packetsRecieved<<" seconds");
          NS_LOG_UNCOND("client average throughput : " << ( (double(this->m_bytesSent) / 125  )/ (this->m_lastPacketSendTime - this->m_firstPacketSendTime))<<" kbps");
          NS_LOG_UNCOND("client send interval :"<<m_sendInterval << " seconds");
          NS_LOG_UNCOND("client Packet size histgram          : ");
          NS_LOG_UNCOND("client reception average jitter : "<< m_jitterAccumulator / m_packetsRecieved << " seconds" );
          m_RecievedPacketsSizeHistogram.Print(std::cout);
          NS_LOG_UNCOND("client sent Packet size histgram     : ");
          m_sentPacketsSizeHistogram.Print(std::cout);
          NS_LOG_UNCOND("client last packet receive time : " << m_lastPacketReceiveTime<< " seconds"<<"\n");
        }
         /**
         *   This method "SendPacket" is used to send a packet to the server. It takes a packet size as an input 
         *  and creates a packet with the specified size. The packet is then sent to the server using the socket created
         *   in the "StartApplication" method and also schedules the next packet transmission.
         */
        void TcpEchoClient::SendPacket(void)
        {
          NS_LOG_UNCOND_ON_OFF("TcpEchoClient::SendPacket");
          if (m_packetsSent < m_nPackets)
          {
            Ptr<Packet> packet = Create<Packet>(m_packetSize);
            PacketCreationTimeTag creationTimeTag;
            creationTimeTag.SetSimpleValue(Simulator::Now().GetSeconds());
            packet->AddPacketTag(creationTimeTag);
            m_packetsSent++;
            m_average_send_time += Simulator::Now().GetSeconds();
            m_bytesSent += packet->GetSize();
            if ( this->m_firstPacketSendTime == 0.0d )
            {
              this->m_firstPacketSendTime = Simulator::Now().GetSeconds();
            }
            this->m_lastPacketSendTime = Simulator::Now().GetSeconds();
            m_socket->Send(packet);
            m_sentPacketsSizeHistogram.AddOne(packet->GetSize());
            ScheduleTx();
          }
          else
          {
            NS_LOG_UNCOND("Client is done sending packets , will close");
            
            NS_LOG_UNCOND("client close time : "<<Simulator::Now().GetSeconds() << " seconds"	);
            
            m_running = false;
          if (m_sendEvent.IsRunning())
          {
            Simulator::Cancel(m_sendEvent);
          }
          if (m_socket)
          {
            m_socket->Close();
          }
            m_running = false;
          }
        }
        /**
         * This method "ConnectionSucceeded" is triggered when the server socket successfully establishes a connection
         * with the client socket and starts recivieng  packets from the client.        
        */
        void TcpEchoClient::ConnectionSucceeded(Ptr<Socket> socket)
        {
          NS_LOG_UNCOND("TcpEchoClient::ConnectionSucceeded  AT : " << ((double)Simulator::Now().GetSeconds()) << " seconds");
          
          Time tNext(Seconds( std::max(  0.0d   , this->m_sendTime - ((double)Simulator::Now().GetSeconds()))));
          // schedual next send for tsend
          NS_LOG_UNCOND("First client send at : " << tNext.GetSeconds() << " seconds");
          m_sendEvent = Simulator::Schedule(tNext, &TcpEchoClient::SendPacket, this);
        }
        /**
        * This method "ConnectionFailed"  is triggered when the socket fails to connect to the server.
        *  It logs an error message and stops the simulation.      
        */
        void TcpEchoClient::ConnectionFailed(Ptr<Socket> socket)
        {
          NS_LOG_UNCOND_ON_OFF("TcpEchoClient::ConnectionFailed ");
          exit(-1);
        }
        /**
        *  This method "ScheduleTx"  is used to schedule the transmission of packets to the server.
        *  It sets up the packet with the appropriate size and payload, and sends it using the socket's Send method.
        *  Here is how the ScheduleTx method works:
        *  It first checks if the number of packets that have been sent so far is less than the total number of packets to be sent (CLIENT_PACKETS_COUNT). 
        *  If all the packets have already been sent, the method returns without doing anything.
        *  It creates a new packet with the specified size (CLIENT_PACKET_SIZE).
        *  It attaches a tag to the packet that contains the current time. This tag is used by the server to calculate the RTT for each packet.
        *  It schedules the transmission of the packet to the server at a fixed rate specified by the CLIENT_SEND_TIME parameter. This is done using the Simulator::Schedule method.
        *  It increments the counter for the number of packets sent so far.
        *  It calls itself again using Simulator::Schedule, with a delay specified by the CLIENT_SEND_TIME parameter. This causes the method to be called repeatedly, sending packets to the server at a fixed rate.
        *  The ScheduleTx method is called by the StartApplication method, which is called when the client starts sending packets to the server. This causes the client to send a specified number of packets 
        *  to the server at a fixed rate until the StopApplication method is called, which stops the client from sending any more packets.
        */
        void TcpEchoClient::ScheduleTx(void)
        {
          if (m_running)
          {
            Time tNext(Seconds(m_sendInterval));
            // NS_LOG_UNCOND("Next client scheduled send at : " << tNext.GetSeconds() << " second");
            m_sendEvent = Simulator::Schedule(tNext, &TcpEchoClient::SendPacket, this);
          }
          else
          {
            NS_LOG_UNCOND_ON_OFF("Client is not runnig , will not schedual");
          }
        }
        /**
        *  This method "HandleClose" is called when the client receives all packets that are expected to be echoed from the server side 
        */
        void TcpEchoClient::HandleClose(Ptr<Socket> s1)
        {
          NS_LOG_UNCOND("TcpEchoClient::HandleClose");
          NS_LOG_UNCOND("Simulation close time now : "<<Simulator::Now().GetSeconds() << " seconds");
        }
        /**
        * When the client receives the echoed packet, it calls the "HandleRead" method to handle the incoming packet. 
        * This method extracts the data from the packet and compares it to the data that was originally sent to the server.
        * If the data matches, it increments a counter to keep track of the number of successful echo replies received.
        */
        void TcpEchoClient::HandleRead(Ptr<Socket> socket)
        {
          NS_LOG_UNCOND_ON_OFF("TcpEchoClient::HandleRead");
          Ptr<Packet> packet;
          Address from;
          while ((packet = socket->RecvFrom(from)))
          {
            if (InetSocketAddress::IsMatchingType(from))
            {
              NS_LOG_UNCOND_ON_OFF("At time " << Simulator::Now().As(Time::S) << " client received " << packet->GetSize() << " bytes from " << InetSocketAddress::ConvertFrom(from).GetIpv4() << " port " << InetSocketAddress::ConvertFrom(from).GetPort());
            }
            else if (Inet6SocketAddress::IsMatchingType(from))
            {
              NS_LOG_UNCOND_ON_OFF("At time " << Simulator::Now().As(Time::S) << " client received " << packet->GetSize() << " bytes from " << Inet6SocketAddress::ConvertFrom(from).GetIpv6() << " port " << Inet6SocketAddress::ConvertFrom(from).GetPort());
            }
            m_packetsRecieved++;
            m_average_receive_time += Simulator::Now().GetSeconds(); 
            m_bytesRecieved += packet->GetSize();
            m_RecievedPacketsSizeHistogram.AddOne(packet->GetSize());
            if (packet->GetSize() > m_maxRecievedPacketSize)
              m_maxRecievedPacketSize = packet->GetSize();
            if (packet->GetSize() < m_minRecievedPacketSize)
              m_minRecievedPacketSize = packet->GetSize();
            // extract the time in which the packet was created
            PacketCreationTimeTag creationTimeTag;
            packet->PeekPacketTag(creationTimeTag);
            // time packet sent and time packet received
            double now = Simulator::Now().GetSeconds() ;
            double packetSendTime  = creationTimeTag.GetSimpleValue();
            // delay
            double packetDelay = now - packetSendTime;
            this->m_packetsTransmissionTime += packetDelay;
            // calculate jitter
            double delayDiffrance = 0.0; // diffrence between past delay and current delay
            if (m_PreviousPacketDelay == 0.0) // if, this is our first time receiving a packet and we have no previous delay
            {
              delayDiffrance = 0.0;         // first packet => we set delay diffrance to zero because there is not previous delay
            }else { /// this is not our first packet  , and we have a previous packet , we should calculate using current and previous delay
              delayDiffrance = std::abs( packetDelay - m_PreviousPacketDelay ); // delay diffrence = abs (delay of this packet - delay of last packet)
            }
            this->m_jitterAccumulator += delayDiffrance; // jitter accumulator takes the sum of all diffrences in succesive packets delays
            // jitter accumulator will at the end be devided by the total number of received packet to get the final jitter
            // this->m_jitterAccumulator = m_PreviousPacketDelay == 0.0 ? 0.0 : std::abs( packetDelay - m_PreviousPacketDelay  );
            m_PreviousPacketDelay = packetDelay; // we save the current packet delay to be used for next time to calculate delay diffrence like on the top
            // end of jitter
            this->m_lastPacketReceiveTime = Simulator::Now().GetSeconds();
          }
        }
         /**
         *  Like the the the "TcpEchoClient" class, the "TcpEchoServer" is a class for defining the server logic in the network,
         *  which will be installed on the target host machine
         *  The class "TcpEchoServer" , is responsible for receiving packets from the client and sending responses back to the client. 
         *  It has similar member functions and variables as the client class.
         *  It Listens on a given port until a client connects, then establishes a TCP connection with the client.  Every time the server received a data packet,
         *  it either ignores it or sends an echo depending on "echoFactor" diffrent than zero or not. the echo can be of the same size as the received packet or can be of N times greater , with N = echo factor,
         *   if the echo factor is zero no echoing occurs.
         *  The  class "TcpEchoServer" , is responsible for receiving packets from the client and sending responses back to 
         *  the client. 
         *  "TcpEchoServer" ==> https://github.com/samueljero/snake/blob/master/ns-3-dev/src/applications/model/tcp-echo-server.cc
         */
      class TcpEchoServer : public Application
      {
              public:
                    TcpEchoServer();
                    virtual ~TcpEchoServer();
                 /**
                 * ns3 classes use "GetTypeId" to provide access to type "reflection".
                 * ns3::TypeId Class is a unique identifier for an interface. This class records a lot of meta-information about a subclass of the Object base class.
                 * http://www.cs.sjsu.edu/~pearce/modules/lectures/oop/types/reflection/ReflectionCpp.htm
                 * https://www.nsnam.org/docs/release/3.15/doxygen/classns3_1_1_type_id.html#details
                 * https://www.nsnam.org/docs/release/3.15/doxygen/type-id_8cc_source.html
                 * https://www.nsnam.org/docs/release/3.24/doxygen/classns3_1_1_type_id.html
                 */
                static TypeId GetTypeId(void);
                /**
                * This method is called at network setup 
                * It sets up the Application by assining the attributes to the given values
                * the callbacks of the socket object are set here 
                * @param address local Ipv4 address + listening port
                * @param delay the time delay after which to emit an echo when a packet is received ( in seconds )
                * @param echoFactor sizeof(echo packet) = sizeof (received packet) * echofACTOR
                */
                void Setup(InetSocketAddress address, 
                          uint32_t delay,
                          uint16_t echoFactor = 1);
                 /**
                 * This method is called after the simulation stops and before it is destroyed it logs all the statistics of the application layer 
                 * of the client side.
                 */
                void ShowStats();

                private:  
                         /***
                         * This method is called typically at the beginning of the simulation. The application's start time is set
                         * when building the network, here TcpEchoServer start listening for incoming client connection.
                         */
                          virtual void StartApplication(void);
                          /**
                          * This method is called when the time comes to stop the application. The application's stop time is set when building the network.
                          */
                          virtual void StopApplication(void);
                          /**
                          * This method is called when the server socket receives a packet from the client. 
                          * This method echoes the packet back to the client, according to the SERVER_ECHO_FACTOR and SERVER_ECHO_DELAY defines.
                          */
                          void HandleRead(Ptr<Socket> socket);
                          /**
                          * This method is called when the server's socket receives a new incoming connection request from a client. 
                          * It creates a new socket and accepts the connection, allowing data to be exchanged between the client and server.
                          */
                          void HandleAccept(Ptr<Socket> socket, const Address &from);
                          /**
                          * This method is called  when TCP connection of the client side is closed, if a connection is closed 
                          * that means the server is closed. 
                          */
                          void HandleClose(Ptr<Socket> socket);
                          /**
                          * This method is called when the server socket successfully establishes a connection with the client socket.
                          * It does nothing but logging the event to the console.
                          */
                          void ConnectionSucceeded(Ptr<Socket> socket);
                          /**
                          * This method is called  when TCP connection fail.             
                          */
                          void ConnectionFailed(Ptr<Socket> socket);
                          /**
                          * This method is called or scheduled by "HandleRead" 
                          * it sends a packet and updates the statistics.
                          */
                          void SendEchoPacket(Ptr<Socket> socket, Ptr<Packet> packet, Address to);

                          /**
                          *  listening port of the server
                          */
                          uint16_t m_port;
                          /**
                          *  listening socket
                          */
                          Ptr<Socket> m_socket;
                          Ipv4Address m_local;
                          /**
                          *  echo timedelay in seconds
                          */
                          uint32_t m_sendInterval;
                          /**
                          *  number of packets send
                          */
                          uint32_t m_packetsSent;
                          /**
                          *  number of echo packets received
                          */
                          uint32_t m_packetsRecieved;
                          /**
                          *  the number of bytes sent
                          */
                          uint32_t m_bytesSent;
                          /**
                          *  the number of bytes received
                          */
                          uint32_t m_bytesRecieved;
                          /**
                          *  an accumilator used to compute average  received packet delay 
                          */
                          double m_packetsTransmissionTime;
                          /**
                          *  used to store the size of the biggest received packet
                          */
                          uint32_t m_maxRecievedPacketSize;
                          /**
                          *  used to store the size of the smallest received packet
                          */
                          uint32_t m_minRecievedPacketSize;
                          /**
                          *  histogram for the size of received packets
                          */
                          SimpleHistogram<uint32_t> m_RecievedPacketsSizeHistogram;
                          /**
                          *  histogram for the size of sent packets
                          */
                          SimpleHistogram<uint32_t> m_sentPacketsSizeHistogram;
                          uint16_t m_echoFactor = 0;                                       // sizeof(echo packet) = sizeof (received packet) * echofACTOR
                          double m_firstPacketSendTime = 0.0d ,m_lastPacketSendTime = 0.0d; // recording when the traffic started and finished to compute throughout
                          double m_average_send_time = 0.0;
                          double m_average_receive_time = 0.0;


                          double m_PreviousPacketDelay  = 0.0f;                                // last received packer delay
                          // Jitter = Sum( Abs( Delay( Packet_(m) ) - Delay(  Packet_(m-1) ) ) ) / Number of received packets
                          double m_jitterAccumulator = 0.0f;                                // sum of all packet delays that is later devided over the number of received packets to get the jitter
                        };
              NS_LOG_COMPONENT_DEFINE("TcpEchoServerApplication");
              NS_OBJECT_ENSURE_REGISTERED(TcpEchoServer);
               /* static */
              TypeId TcpEchoServer::GetTypeId(void)
              {
                static TypeId tid = TypeId("ns3::TcpEchoServer")
                                        .SetParent<Application>()
                                        .AddConstructor<TcpEchoServer>()
                                        .AddAttribute("Local", "The Address on which to Bind the rx socket.",
                                                      Ipv4AddressValue(),
                                                      MakeIpv4AddressAccessor(&TcpEchoServer::m_local),
                                                      MakeIpv4AddressChecker())
                                        .AddAttribute("Port", "Port on which we listen for incoming packets.",
                                                      UintegerValue(9),
                                                      MakeUintegerAccessor(&TcpEchoServer::m_port),
                                                      MakeUintegerChecker<uint16_t>());
                return tid;
              }

              TcpEchoServer::TcpEchoServer() : m_packetsSent(0),
                                              m_packetsRecieved(0),
                                              m_bytesSent(0),
                                              m_bytesRecieved(0)
              {
                NS_LOG_FUNCTION_NOARGS();
              }

        /**
        * This method  "TcpEchoServer::Setup" is used to configure the server's parameters such as Socket Address
        *  the delay and  echoFactor .
        */        
      void TcpEchoServer::Setup(InetSocketAddress address,
                                uint32_t delay,
                                uint16_t echoFactor)
      {
        NS_LOG_UNCOND("Setting up server ...");
        m_local = InetSocketAddress::ConvertFrom(address).GetIpv4();
        NS_LOG_UNCOND("server address : " << m_local);
        m_port = InetSocketAddress::ConvertFrom(address).GetPort();
        m_sendInterval = delay;
        m_echoFactor = echoFactor;
        m_maxRecievedPacketSize = 0;
        m_minRecievedPacketSize = 99999;
        m_packetsTransmissionTime = 0;
      }

      TcpEchoServer::~TcpEchoServer()
      {
        NS_LOG_FUNCTION_NOARGS();
        m_socket = 0;
      }
        /**
        * This method "StartApplication" is called when the server application is started, typically at the beginning of the simulation. 
        * It creates a socket and binds it to the server's IP address and port number.
        */
      void TcpEchoServer::StartApplication(void)
      {
        NS_LOG_FUNCTION_NOARGS();
        if (m_socket == 0)
        {
          TypeId tid = TypeId::LookupByName("ns3::TcpSocketFactory");
          m_socket = Socket::CreateSocket(GetNode(), tid);
          InetSocketAddress local = InetSocketAddress(m_local, m_port);
    #if not defined DISABLE_LOG
          int res = m_socket->Bind(local);
    #else
          m_socket->Bind(local);
    #endif
          m_socket->Listen();
          NS_LOG_UNCOND_ON_OFF("Echo Server local address:  " << m_local << " port: " << m_port << " bind: " << (!res ? "Success" : "Failed"));
        }
        m_socket->SetRecvCallback(MakeCallback(&TcpEchoServer::HandleRead, this));
        m_socket->SetAcceptCallback(
            MakeNullCallback<bool, Ptr<Socket>, const Address &>(),
            MakeCallback(&TcpEchoServer::HandleAccept, this));
        m_socket->SetCloseCallbacks(MakeCallback(&TcpEchoServer::HandleClose, this), MakeCallback(&TcpEchoServer::HandleClose, this));
      }
      void TcpEchoServer::HandleClose(Ptr<Socket> s1)
      {
        NS_LOG_UNCOND("tcp echo server will close because of closed connection");
        NS_LOG_UNCOND("Simulation close time now : "<<Simulator::Now().GetSeconds() 	);
        // close app and socket connection
        s1->Close();
        NS_LOG_UNCOND(" SERVER PEER CLOSE ");
      }

      void TcpEchoServer::HandleAccept(Ptr<Socket> s, const Address &from)
      {
        NS_LOG_FUNCTION(this << s << from);
        NS_LOG_UNCOND("ACCEPT IN ECHO SERVER from " << InetSocketAddress::ConvertFrom(from).GetIpv4());
        NS_LOG_UNCOND("Accept at : "<<Simulator::Now().GetSeconds()<< " seconds");
        s->SetRecvCallback(MakeCallback(&TcpEchoServer::HandleRead, this));
      }

      void TcpEchoServer::StopApplication()
      {
        NS_LOG_UNCOND("TcpEchoServer::StopApplication at : "<<Simulator::Now().GetSeconds());
        NS_LOG_FUNCTION_NOARGS();
        
      }
      void TcpEchoServer::ShowStats()
      {
        NS_LOG_UNCOND("----------------   Appllication level stats for server app -------------");
        NS_LOG_UNCOND("server packets sent                  : " << m_packetsSent << " packets");
        NS_LOG_UNCOND("server packets received              : " << m_packetsRecieved<< " packets");
        NS_LOG_UNCOND("server bytes sent                    : " << m_bytesSent<< " bytes");
        NS_LOG_UNCOND("server bytes received                : " << m_bytesRecieved<< " bytes");
        NS_LOG_UNCOND("server average received packet size : " << double(m_bytesRecieved) / double(m_packetsRecieved) << " bytes");
        NS_LOG_UNCOND("server min received packet size     : " << m_minRecievedPacketSize<< " bytes");
        NS_LOG_UNCOND("server max received packet size     : " << m_maxRecievedPacketSize<< " bytes");
        NS_LOG_UNCOND("server packet total transmission time : " << double(m_packetsTransmissionTime)<< " seconds");
        NS_LOG_UNCOND("server average packet reception delay : " << double(m_packetsTransmissionTime) / double(m_packetsRecieved)<< " seconds");
        NS_LOG_UNCOND("server first packet send time : " <<  this->m_firstPacketSendTime<<" seconds");
        NS_LOG_UNCOND("server last packet send time : " <<  this->m_lastPacketSendTime<<" seconds");
        NS_LOG_UNCOND("server average send time : " <<  m_average_send_time / m_packetsSent<<" seconds");
        NS_LOG_UNCOND("server average receive time : " <<  m_average_receive_time / m_packetsRecieved<<" seconds");
        NS_LOG_UNCOND("server average throughput : " << ( (double(m_bytesSent) / 125  )/ (this->m_lastPacketSendTime - this->m_firstPacketSendTime))<<" kbps");
        NS_LOG_UNCOND("server Packet size histgram          : ");
        NS_LOG_UNCOND("server reception average jitter : "<< m_jitterAccumulator / m_packetsRecieved << " seconds");
        m_RecievedPacketsSizeHistogram.Print(std::cout);
        NS_LOG_UNCOND("server SENT Packet size histgram     : ");
        m_sentPacketsSizeHistogram.Print(std::cout);
      }
      void TcpEchoServer::ConnectionSucceeded(Ptr<Socket> socket)
      {
        NS_LOG_UNCOND_ON_OFF("TcpEchoServer::ConnectionSucceeded ");
      }

      void TcpEchoServer::ConnectionFailed(Ptr<Socket> socket)
      {
        NS_LOG_UNCOND_ON_OFF("TcpEchoServer::ConnectionFailed ");
      }

      void TcpEchoServer::SendEchoPacket(Ptr<Socket> socket, Ptr<Packet> packet, Address to)
      {
        NS_LOG_UNCOND_ON_OFF("time to send packet expired will send now : "
                            << "Packet size :" << packet->GetSize());
        // update send statistics
        m_packetsSent++;
        m_average_send_time += Simulator::Now().GetSeconds();
        m_bytesSent += packet->GetSize();
        if ( this->m_firstPacketSendTime == 0.0d ) // never sent a packet before ( this is the first )
        {
          this->m_firstPacketSendTime = Simulator::Now().GetSeconds();
        }
        // we always take the current time as the last send time
        this->m_lastPacketSendTime = Simulator::Now().GetSeconds(); 
        socket->SendTo(packet, 0, to);
        m_sentPacketsSizeHistogram.AddOne(packet->GetSize());
      }

      void TcpEchoServer::HandleRead(Ptr<Socket> socket)
      {
        NS_LOG_UNCOND_ON_OFF("TcpEchoServer::HandleRead");
        NS_LOG_FUNCTION(this << socket);

        Ptr<Packet> packet;
        Address from;
        Ptr<Packet> echoPacket;

        while ((packet = socket->RecvFrom(from)))
        {
          // update receive stats
          if (packet->GetSize() > m_maxRecievedPacketSize)
            m_maxRecievedPacketSize = packet->GetSize();
          if (packet->GetSize() < m_minRecievedPacketSize)
            m_minRecievedPacketSize = packet->GetSize();
          m_RecievedPacketsSizeHistogram.AddOne(packet->GetSize());
          m_packetsRecieved++;
          m_average_receive_time += Simulator::Now().GetSeconds();
          m_bytesRecieved += packet->GetSize();
          PacketCreationTimeTag recievedCreationTimeTag;
          packet->PeekPacketTag(recievedCreationTimeTag);
          double packetDelay = Simulator::Now().GetSeconds() - recievedCreationTimeTag.GetSimpleValue();;
          this->m_packetsTransmissionTime += packetDelay;


        // calculate jitter
        double delayDiffrance = 0.0; // diffrence between past delay and current delay
        if (m_PreviousPacketDelay == 0.0) // if, this is our first time receiving a packet and we have no previous delay
        {
          delayDiffrance = 0.0;         // first packet => we set delay diffrance to zero because there is not previous delay
        }else { /// this is not our first packet  , and we have a previous packet , we should calculate using current and previous delay
          delayDiffrance = std::abs( packetDelay - m_PreviousPacketDelay ); // delay diffrence = abs (delay of this packet - delay of last packet)
        }
        this->m_jitterAccumulator += delayDiffrance; // jitter accumulator takes the sum of all diffrences in succesive packets delays
        // jitter accumulator will at the end be devided by the total number of received packet to get the final jitter
        
        
        // this->m_jitterAccumulator = m_PreviousPacketDelay == 0.0 ? 0.0 : std::abs( packetDelay - m_PreviousPacketDelay  );
        
        
        m_PreviousPacketDelay = packetDelay; // we save the current packet delay to be used for next time to calculate delay diffrence like on the top
        // end of jitter

          // optional logging
          if (InetSocketAddress::IsMatchingType(from))
          {
            NS_LOG_UNCOND_ON_OFF("At time " << Simulator::Now().As(Time::S) << " server received " << packet->GetSize() << " bytes from " << InetSocketAddress::ConvertFrom(from).GetIpv4() << " port " << InetSocketAddress::ConvertFrom(from).GetPort());
          }
          else if (Inet6SocketAddress::IsMatchingType(from))
          {
            NS_LOG_UNCOND_ON_OFF("At time " << Simulator::Now().As(Time::S) << " server received " << packet->GetSize() << " bytes from " << Inet6SocketAddress::ConvertFrom(from).GetIpv6() << " port " << Inet6SocketAddress::ConvertFrom(from).GetPort());
          }
            // echo logic
          if (m_echoFactor)
          {
            // client message to read
            uint8_t *msg =  new uint8_t[packet->GetSize()];
            // create packet to use for echo
            echoPacket = Create<Packet>(msg, packet->GetSize() * m_echoFactor);
            // read client message 
            packet->CopyData(msg, packet->GetSize());
            // put the creation time into the echo packet
            PacketCreationTimeTag creationTimeTag;
            creationTimeTag.SetSimpleValue(Simulator::Now().GetSeconds());
            echoPacket->AddPacketTag(creationTimeTag);

            if (InetSocketAddress::IsMatchingType(from))
            {
              NS_LOG_UNCOND_ON_OFF("At time " << Simulator::Now().As(Time::S) << "seconds, server sent " << packet->GetSize() << " bytes to " << InetSocketAddress::ConvertFrom(from).GetIpv4() << " port " << InetSocketAddress::ConvertFrom(from).GetPort());
            }
            else if (Inet6SocketAddress::IsMatchingType(from))
            {
              NS_LOG_UNCOND_ON_OFF("At time " << Simulator::Now().As(Time::S) << " server sent " << packet->GetSize() << " bytes to " << Inet6SocketAddress::ConvertFrom(from).GetIpv6() << " port " << Inet6SocketAddress::ConvertFrom(from).GetPort());
            }
            if (m_sendInterval == 0)
            {
              NS_LOG_UNCOND_ON_OFF("Echo without delay ...");
              Address destination = from;
              SendEchoPacket(socket, echoPacket, destination); 
            }
            else
            {
              Time tNext(MilliSeconds(m_sendInterval));
              NS_LOG_UNCOND_ON_OFF("Server scheduled an echo after : " << tNext.GetSeconds() << " seconds "
                                                                      << " , " << m_sendInterval << " milliseconds");
              Simulator::Schedule(tNext, &TcpEchoServer::SendEchoPacket, this, socket, echoPacket, from);
            }
          }
          else
          {
            NS_LOG_UNCOND_ON_OFF("Echo disabled .");
          }
        }
  }
}
using namespace ns3;

NS_LOG_COMPONENT_DEFINE("WiredTcpClientServer");



// A list of callback function used to monitor packet drop
/**
* Callback used to listen for packet drop at Mac layer for any packet being sent
*/
static void ServerMacTxDrop(ns3::Ptr<ns3::Packet const>)
{
 NS_LOG_UNCOND("ServerMacTxDrop at " << Simulator::Now().GetSeconds());
}

/**
* Callback used to listen for packet drop at physical layer for any packet being sent
*/
static void ServerPhyTxDrop(ns3::Ptr<ns3::Packet const>)
{
 NS_LOG_UNCOND("ServerPhyTxDrop at " << Simulator::Now().GetSeconds());
}

/**
* Callback used to listen for packet drop at physical layer for any packet being received
*/
static void ServerPhyRxDrop(ns3::Ptr<ns3::Packet const>)
{
  NS_LOG_UNCOND("ServerPhyRxDrop at " << Simulator::Now().GetSeconds());
}

/**
* Callback used to listen for packet drop at mac layer for any packet being sent
*/
static void ClientMacTxDrop(ns3::Ptr<ns3::Packet const>)
{
  NS_LOG_UNCOND("ClientMacTxDrop at " << Simulator::Now().GetSeconds());
}

/**
* Callback used to listen for packet drop at physical layer for any packet being sent
*/
static void ClientPhyTxDrop(ns3::Ptr<ns3::Packet const>)
{
  NS_LOG_UNCOND("ClientPhyTxDrop at " << Simulator::Now().GetSeconds());
}

/**
* Callback used to listen for packet drop at physical layer for any received packet
*/
static void ClientPhyRxDrop(ns3::Ptr<ns3::Packet const>)
{
  NS_LOG_UNCOND("ClientPhyRxDrop at " << Simulator::Now().GetSeconds());
}


/**
* Callback used to listen for packet drop for any received packet
*/
static void SocketRxDrop(Ptr<const Packet> p)
{
  NS_LOG_UNCOND("RxDrop at " << Simulator::Now().GetSeconds());
}

/**
* Callback used to listen for packet drop at IpV4 layer
*/
void IpV4L3DropPkt(const Ipv4Header &header, Ptr<const Packet> packet, Ipv4L3Protocol::DropReason reason, Ptr<Ipv4> ipv4, uint32_t interface)
{
  switch (reason)
  {
  case Ipv4L3Protocol::DROP_TTL_EXPIRED:
    NS_LOG_UNCOND("DROP_TTL_EXPIRED");
    break;
  case Ipv4L3Protocol::DROP_NO_ROUTE:
    NS_LOG_UNCOND("DROP_TTL_EXPIRED");
    break;
  case Ipv4L3Protocol::DROP_BAD_CHECKSUM:
    NS_LOG_UNCOND("DROP_TTL_EXPIRED");
    break;
  case Ipv4L3Protocol::DROP_INTERFACE_DOWN:
    NS_LOG_UNCOND("DROP_TTL_EXPIRED");
    break;
  case Ipv4L3Protocol::DROP_ROUTE_ERROR:
    NS_LOG_UNCOND("DROP_TTL_EXPIRED");
    break;
  case Ipv4L3Protocol::DROP_FRAGMENT_TIMEOUT:
    NS_LOG_UNCOND("DROP_TTL_EXPIRED");
    break;
  case Ipv4L3Protocol::DROP_DUPLICATE:
    NS_LOG_UNCOND("DROP_DUPLICATE");
    break;
  default:
    NS_LOG_UNCOND("DROP FOR UNKNOWN REASON");
  };
}

#include <functional>
template <typename T>
size_t getAddress(std::function<void(T &)> f)
{
  typedef void(fnType)(T &);
  fnType **fnPointer = f.template target<fnType *>();
  return (size_t)*fnPointer;
}
int
    ClientIpV4L3SendOutGoingCount = 0,
    ClientIpV4L3STxCount = 0,
    ServerIpV4L3SendOutGoingCount = 0, ServerIpV4L3STxCount = 0;
void ClientIpV4L3SendOutgoingCallback()
{
  ClientIpV4L3SendOutGoingCount++;
}

void ClientIpV4L3TX()
{

  ClientIpV4L3STxCount++;
}

void ServerIpV4L3SendOutgoingCallback()
{
  ServerIpV4L3SendOutGoingCount++;
}

void ServerIpV4L3TX()
{
  ServerIpV4L3STxCount++;
}
int simulate(
    double error_rate,
    std::string channel_data_rate,
    std::string channel_delay,
    std::string point_to_point_queue_size,
    int server_echo_factor,
    int server_echo_delay,
    std::string client_data_rate,
    int client_packets_count,
    int client_packet_size,
    double client_start_time,
    double client_send_time,
    double server_start_time,
    double client_stop_time,
    double server_stop_time,
    double simulation_length,
    int use_csma,
    int new_reno_enabled)
{
  NS_LOG_UNCOND_ON_OFF("App start...");
  uint32_t SentPackets = 0;
  uint32_t ReceivedPackets = 0;
  uint32_t LostPackets = 0;

  if (new_reno_enabled)
  {
    Config::SetDefault("ns3::TcpL4Protocol::SocketType", StringValue("ns3::TcpNewReno"));
    Config::SetDefault("ns3::TcpSocket::InitialCwnd", UintegerValue(1));
    Config::SetDefault("ns3::TcpL4Protocol::RecoveryType", TypeIdValue(TypeId::LookupByName("ns3::TcpClassicRecovery")));
    Config::SetDefault("ns3::TcpSocket::TcpNoDelay", BooleanValue(true));
  }
// start network setup
  NodeContainer nodes;
  nodes.Create(2);

  Names::Add("Client", nodes.Get(CLIENT_MACHINE_NUM));
  Names::Add("Server", nodes.Get(SERVER_MACHINE_NUM));

  PcapHelperForDevice *pcap_device_helper;

  if (use_csma) // if csma is enabled
  {
    CsmaHelper *csma = new CsmaHelper(); // use CsmaHelper
    pcap_device_helper = csma;          // store it for later 
    // set the data rate of the channel
    csma->SetChannelAttribute("DataRate", StringValue(channel_data_rate));
   // csma->SetDeviceAttribute("DataRate", StringValue(channel_data_rate));
    // set the propagation delay of the channel 
    csma->SetChannelAttribute("Delay", StringValue(channel_delay));
    // set the queue type and size of the network device 
    csma->SetQueue("ns3::DropTailQueue", "MaxSize", StringValue(point_to_point_queue_size));
  }
  else
  {
    PointToPointHelper *p2p = new PointToPointHelper(); // use PointToPointHelper
    pcap_device_helper = p2p;         // store it for later
    // set the propagation delay of the channel 
    p2p->SetChannelAttribute("Delay", StringValue(channel_delay));
    // set the data rate of the channel
    p2p->SetDeviceAttribute("DataRate", StringValue(channel_data_rate));
    // set the queue type and size of the network device 
    p2p->SetQueue("ns3::DropTailQueue", "MaxSize", StringValue(point_to_point_queue_size));
  }

  NetDeviceContainer devices;
  if (use_csma)
  {
    devices = dynamic_cast<CsmaHelper *>(pcap_device_helper)->Install(nodes);
  }
  else
  {
    devices = dynamic_cast<PointToPointHelper *>(pcap_device_helper)->Install(nodes);
  }

  Ptr<RateErrorModel> em = CreateObject<RateErrorModel>();
  em->SetAttribute("ErrorRate", DoubleValue(error_rate));
  devices.Get(SERVER_MACHINE_NUM)->SetAttribute("ReceiveErrorModel", PointerValue(em));
  devices.Get(CLIENT_MACHINE_NUM)->SetAttribute("ReceiveErrorModel", PointerValue(em));

  InternetStackHelper stack;
  stack.Install(nodes);

  Ipv4AddressHelper address;
  address.SetBase("10.1.1.0", "255.255.255.252");
  Ipv4InterfaceContainer interfaces = address.Assign(devices);
// ==== Application layer
  uint16_t serverPort = 8080;
  uint16_t clientPort = 1212;

  InetSocketAddress socketServerAddress = InetSocketAddress(interfaces.GetAddress(SERVER_MACHINE_NUM), serverPort);
  Address serverAddress(socketServerAddress);

  Ptr<TcpEchoServer> serverApp = CreateObject<TcpEchoServer>();
  serverApp->Setup(InetSocketAddress(interfaces.GetAddress(SERVER_MACHINE_NUM), serverPort), server_echo_delay, server_echo_factor);

  nodes.Get(SERVER_MACHINE_NUM)->AddApplication(serverApp);
  serverApp->SetStartTime(Seconds(server_start_time));
  serverApp->SetStopTime(Seconds(server_stop_time));

  Ptr<Socket> clientApplicationSocket = Socket::CreateSocket(nodes.Get(CLIENT_MACHINE_NUM), TcpSocketFactory::GetTypeId());
  clientApplicationSocket->TraceConnectWithoutContext("Drop", MakeCallback(&SocketRxDrop));

  Config::Set("/NodeList/*/$ns3::TcpL4Protocol/SocketList/*/MaxSegLifetime", DoubleValue(0.0));

  Ptr<TcpEchoClient> clientApp = CreateObject<TcpEchoClient>();
  // uncomment this line to print default buffer size, the buffer will overflow in higher datarates
  //NS_LOG_UNCOND("TX buffer size : "<<DynamicCast<ns3::TcpSocketBase>(clientApplicationSocket)->GetTxBuffer()->MaxBufferSize());
  
  
  clientApp->Setup(clientApplicationSocket, InetSocketAddress(interfaces.GetAddress(CLIENT_MACHINE_NUM), clientPort), socketServerAddress, client_packet_size, client_packets_count, DataRate(client_data_rate) ,client_send_time);
  nodes.Get(CLIENT_MACHINE_NUM)->AddApplication(clientApp);
  clientApp->SetStartTime(Seconds(client_start_time));
  clientApp->SetStopTime(Seconds(client_stop_time));


// end network setup
  devices.Get(SERVER_MACHINE_NUM)->TraceConnectWithoutContext("MacTxDrop", MakeCallback(&ServerMacTxDrop));
  devices.Get(SERVER_MACHINE_NUM)->TraceConnectWithoutContext("PhyTxDrop", MakeCallback(&ServerPhyTxDrop));
  devices.Get(SERVER_MACHINE_NUM)->TraceConnectWithoutContext("PhyRxDrop", MakeCallback(&ServerPhyRxDrop));
  
  devices.Get(CLIENT_MACHINE_NUM)->TraceConnectWithoutContext("MacTxDrop", MakeCallback(&ClientMacTxDrop));
  devices.Get(CLIENT_MACHINE_NUM)->TraceConnectWithoutContext("PhyTxDrop", MakeCallback(&ClientPhyTxDrop));
  devices.Get(CLIENT_MACHINE_NUM)->TraceConnectWithoutContext("PhyRxDrop", MakeCallback(&ClientPhyRxDrop));

  AsciiTraceHelper ascii;
  pcap_device_helper->EnablePcapAll("lsr");
  Simulator::Stop(Seconds(simulation_length));
  FlowMonitorHelper flowmonHelper;
  Ptr<FlowMonitor> monitor = flowmonHelper.InstallAll();

  Config::ConnectWithoutContext("/NodeList/*/$ns3::Ipv4L3Protocol/Drop",
                                MakeCallback(&IpV4L3DropPkt));

  Config::ConnectWithoutContext("/NodeList/" STRINGIZE( CLIENT_MACHINE_NUM) "/$ns3::Ipv4L3Protocol/SendOutgoing",
                                                        MakeCallback((ns3::Ipv4L3Protocol::SentTracedCallback)(&ClientIpV4L3SendOutgoingCallback)));

  Config::ConnectWithoutContext("/NodeList/" STRINGIZE( CLIENT_MACHINE_NUM) "/$ns3::Ipv4L3Protocol/Tx",
                                                        MakeCallback((ns3::Ipv4L3Protocol::TxRxTracedCallback)(&ClientIpV4L3TX)));

  Config::ConnectWithoutContext("/NodeList/" STRINGIZE( SERVER_MACHINE_NUM) "/$ns3::Ipv4L3Protocol/SendOutgoing",
                                                        MakeCallback((ns3::Ipv4L3Protocol::SentTracedCallback)(&ServerIpV4L3SendOutgoingCallback)));

  Config::ConnectWithoutContext("/NodeList/" STRINGIZE( SERVER_MACHINE_NUM) "/$ns3::Ipv4L3Protocol/Tx",
                                                        MakeCallback((ns3::Ipv4L3Protocol::TxRxTracedCallback)(&ServerIpV4L3TX))); 
  if (use_csma)
  {
     Config::Connect("/NodeList/" STRINGIZE( SERVER_MACHINE_NUM)  "/DeviceList/*/$ns3::CsmaNetDevice/MacTxBackoff", MakeCallback((&ServerMacTxBackoffOccur)));
    Config::Connect("/NodeList/" STRINGIZE( CLIENT_MACHINE_NUM)  "/DeviceList/*/$ns3::CsmaNetDevice/MacTxBackoff", MakeCallback((&ClientMacTxBackoffOccur)));

  }
  Simulator::Run();

  // client lost packets due to buffer overflow : 
  NS_LOG_UNCOND("client lost packets : "<<DynamicCast<ns3::TcpSocketBase>(clientApplicationSocket)->GetTxBuffer()->GetLost());

  clientApp->ShowStats();
  serverApp->ShowStats();
  
  NS_LOG_UNCOND("Number of events : "<<Simulator::GetEventCount 	( ) 	);
  int j = 0;
  float AvgThroughput = 0;
  Time Jitter;
  Time Delay;

  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flowmonHelper.GetClassifier());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats();

  NS_LOG_UNCOND("------- Phsysical layer stats ----------" << std::endl);
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator iter = stats.begin(); iter != stats.end(); ++iter)
  {
    Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(iter->first);
    NS_LOG_UNCOND("----Flow ID:" << iter->first);
    NS_LOG_UNCOND("Src Addr " << t.sourceAddress << " Dst Addr " << t.destinationAddress);
    NS_LOG_UNCOND("Sent Packets= " << iter->second.txPackets);
    NS_LOG_UNCOND("Received Packets =" << iter->second.rxPackets);
    NS_LOG_UNCOND("Send bytes by "<< t.sourceAddress<<" : "<< iter->second.txBytes);
    NS_LOG_UNCOND("Received bytes by "<< t.destinationAddress<<" : "<< iter->second.rxBytes);
    NS_LOG_UNCOND("Lost Packets =" << iter->second.txPackets - iter->second.rxPackets);
    NS_LOG_UNCOND("Packet delivery ratio =" << iter->second.rxPackets * 100.0f / iter->second.txPackets << "%");
    NS_LOG_UNCOND("Packet loss ratio =" << double(iter->second.txPackets - iter->second.rxPackets) * 100.0f / iter->second.txPackets << "%");
    NS_LOG_UNCOND("Delay =" << iter->second.delaySum.GetSeconds()<< " seconds");
    NS_LOG_UNCOND("Jitter =" << iter->second.jitterSum.GetSeconds() << " seconds");
    
    NS_LOG_UNCOND("Throughput out of " << t.sourceAddress<<" : "<<(iter->second.txBytes  / 125) / (iter->second.timeLastTxPacket.GetSeconds() - iter->second.timeFirstTxPacket.GetSeconds()) << " Kbps");
    
    NS_LOG_UNCOND( "first time send by "<<t.sourceAddress <<"  : "<<iter->second.timeFirstTxPacket.GetSeconds() << " seconds");
    NS_LOG_UNCOND( "last time send by "<<t.sourceAddress<< "  : "<<iter->second.timeLastTxPacket.GetSeconds()<< " seconds" );
    NS_LOG_UNCOND( "first time received by "<<t.destinationAddress <<"  : "<<iter->second.timeFirstRxPacket.GetSeconds()<< " seconds" );
    NS_LOG_UNCOND( "last time received by "<<t.destinationAddress<< "  : "<<iter->second.timeLastRxPacket.GetSeconds() << " seconds");
    
    SentPackets = SentPackets + (iter->second.txPackets);
    ReceivedPackets = ReceivedPackets + (iter->second.rxPackets);
    LostPackets = LostPackets + (iter->second.txPackets - iter->second.rxPackets);
    AvgThroughput = AvgThroughput + ( (iter->second.txBytes / 125)  / (iter->second.timeLastTxPacket.GetSeconds() - iter->second.timeFirstTxPacket.GetSeconds()) );
    Delay = Delay + (iter->second.delaySum);
    Jitter = Jitter + (iter->second.jitterSum);
    j = j + 1;
  }

  AvgThroughput = AvgThroughput / j;
  NS_LOG_UNCOND("--------Total Results of the simulation physical layer----------" << std::endl);
  NS_LOG_UNCOND("Total sent packets  =" << SentPackets<< " packets");
  NS_LOG_UNCOND("Total Received Packets =" << ReceivedPackets<< " packets");
  NS_LOG_UNCOND("Total Lost Packets =" << LostPackets<< " packets");
  NS_LOG_UNCOND("Packet Loss ratio =" << ((LostPackets * 100.0f) / SentPackets) << "%");
  NS_LOG_UNCOND("Packet delivery ratio =" << ((ReceivedPackets * 100.0f) / SentPackets) << "%");
  NS_LOG_UNCOND("Average Throughput =" << AvgThroughput << "Kbps");
  NS_LOG_UNCOND("End to End Delay =" << Delay.GetSeconds()<< " seconds");
  NS_LOG_UNCOND("End to End Jitter =" << Jitter.GetSeconds()<< " seconds");
  NS_LOG_UNCOND("Server Number of collisions : "<<ServerMacTxBackoffOccurCount<< " collisions");
  NS_LOG_UNCOND("Client Number of collisions : "<<ClientMacTxBackoffOccurCount<< " collisions");
  NS_LOG_UNCOND("Total Flod id " << j);
  return 0;
}

int main(int argc, char *argv[])
{
  CommandLine cmd;
  double error_rate = ERROR_RATE;
  std::string channel_data_rate = CHANNEL_DATA_RATE;
  std::string channel_delay = CHANNEL_DELAY;
  std::string point_to_point_queue_size = POINT_TO_POINT_QUEUE_SIZE;
  int server_echo_factor = SERVER_ECHO_FACTOR;
  int server_echo_delay = SERVER_ECHO_DELAY;
  std::string client_data_rate = CLIENT_DATA_RATE;
  int client_packets_count = CLIENT_PACKETS_COUNT;
  int client_packet_size = CLIENT_PACKET_SIZE;
  double client_start_time = CLIENT_START_TIME;
  double client_send_time = CLIENT_SEND_TIME;
  double server_start_time = SERVER_START_TIME;
  double client_stop_time = CLIENT_STOP_TIME;
  double server_stop_time = SERVER_STOP_TIME;
  double simulation_length = SIMULATION_LENGTH;
  int new_reno_enabled = NEW_RENO_ENABLED;
  int use_csma = USE_CSMA;

  cmd.AddValue("error_rate", "error rate for netdevice error model, this can be in the range [0,0 .. 1.0]", error_rate);
  cmd.AddValue("channel_data_rate", "the datarate of the channel, example 100Mbps", channel_data_rate);
  cmd.AddValue("channel_delay", "how long does the packet take to traverse the channel,example : 0000004s", channel_delay);
  cmd.AddValue("point_to_point_queue_size", "the queue size in packets in case of ppp , example 100p", point_to_point_queue_size);
  cmd.AddValue("server_echo_factor", "how many packets should the sever send back for each packet it receives", server_echo_factor);
  cmd.AddValue("server_echo_delay", "after how long should the server perform the echo", server_echo_delay);
  cmd.AddValue("client_data_rate", "the datarate in which the client should be sending packets", client_data_rate);
  cmd.AddValue("client_packets_count", "the total number of packets that the client should send", client_packets_count);
  cmd.AddValue("client_packet_size", "the client's packets size in bytes, example 512", client_packet_size);
  cmd.AddValue("client_start_time", "when does the client application start in simulation time, example 0", client_start_time);
  cmd.AddValue("client_send_time", "when does the client application start sending packets in simulation time, example 0", client_send_time);
  cmd.AddValue("server_start_time", "when does the server application start in simulation time in seconds, example 0", server_start_time);
  cmd.AddValue("client_stop_time",  "when does the client application stop in simulation time in seconds, example 500", client_stop_time);
  cmd.AddValue("server_stop_time",  "when does the server application stop in simulation time in seconds, example 500", server_stop_time);
  cmd.AddValue("simulation_length", "for how long does the simulation continue to run, in seconds", simulation_length);
  cmd.AddValue("use_csma", "when set to true we use half duplex channel, when false we use ppp", use_csma);
  cmd.AddValue("new_reno_enabled", "enable or disaable reno protocol", new_reno_enabled);
  cmd.Parse(argc, argv);


  DEBUG_VAR(error_rate);
  DEBUG_VAR(use_csma);
  if (use_csma)
  {
    DEBUG_VAR(channel_data_rate);
  }
  DEBUG_VAR(channel_delay);
  DEBUG_VAR(point_to_point_queue_size);
  DEBUG_VAR(server_echo_factor);
  DEBUG_VAR(server_echo_delay);
  DEBUG_VAR(client_data_rate);
  DEBUG_VAR(client_packets_count);
  DEBUG_VAR(client_packet_size);
  DEBUG_VAR(client_start_time);
  DEBUG_VAR(client_send_time);
  DEBUG_VAR(server_start_time);
  DEBUG_VAR(client_stop_time);
  DEBUG_VAR(server_stop_time);
  DEBUG_VAR(simulation_length);
  DEBUG_VAR(new_reno_enabled);

  return simulate(
      error_rate,
      channel_data_rate,
      channel_delay,
      point_to_point_queue_size,
      server_echo_factor,
      server_echo_delay,
      client_data_rate,
      client_packets_count,
      client_packet_size,
      client_start_time,
      client_send_time,
      server_start_time,
      client_stop_time,
      server_stop_time,
      simulation_length,
      use_csma,
      new_reno_enabled);
}