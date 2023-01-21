rm -f scratch/wired.txt
for dataRate in 0.5Mbps 1Mbps 2Mbps 4Mbps 8Mbps 16Mbps 32Mbps 64Mbps 128Mbps 256Mbps 512Mbps
do
./waf -v --run "scratch/WiredTcpClientServer.cc 
--use_csma=1
--channel_data_rate=100Mbps 
--channel_delay=0.0000004s
--client_data_rate=${dataRate}
--error_rate=0 
--point_to_point_queue_size=100p 
--server_echo_factor=1
--server_echo_delay=0 
--client_packets_count=1000
--client_packet_size=512
--client_start_time=0
--server_start_time=0 
--client_stop_time=100
--server_stop_time=100
--simulation_length=100
" | tee -a scratch/wired.txt

done
#to run the project ===> type :  ./scratch/run_point_to_point.sh
################################################# Result Extraction from kali linux terminal ######################################################################### 
#grep -E "TcpEchoClient::StartApplication" scratch/wired.txt
#grep -E "TcpEchoClient::ConnectionSucceeded" scratch/wired.txt
#grep -E "First client send" scratch/wired.txt
#grep -E "Accept at " scratch/wired.txt
#grep -E "client close time " scratch/wired.txt
#grep -E "Simulation close time now " scratch/wired.txt
#grep -E "client lost packets" scratch/wired.txt
#grep -E "m_sendInterval " scratch/wired.txt

                                                
################### Appllication layer stats for client  ########################
#grep -E "client intended packets sent" scratch/wired.txt
#grep -E "client packets sent" scratch/wired.txt
#grep -E "client packets received" scratch/wired.txt
#grep -E "client bytes sent" scratch/wired.txt
#grep -E "client bytes received" scratch/wired.txt
#grep -E "client average received packet size" scratch/wired.txt
#grep -E "client min received packet size " scratch/wired.txt
#grep -E "client max received packet size" scratch/wired.txt
#grep -E "client packet total transmission time" scratch/wired.txt
#grep -E "client average received packet delay " scratch/wired.txt
#grep -E "client first packet send time" scratch/wired.txt
#grep -E "client last packet send time " scratch/wired.txt
#grep -E "client average send time" scratch/wired.txt
#grep -E "client average receive time " scratch/wired.txt
#grep -E "client average throughput " scratch/wired.txt
#grep -E "client send interval " scratch/wired.txt
#grep -E "client reception average jitter " scratch/wired.txt
#grep -E "client sent Packet size histgram " scratch/wired.txt
#grep -E "client last packet receive time" scratch/wired.txt

################### Appllication layer stats for server  ########################
#grep -E "server packets sent" scratch/wired.txt
#grep -E "server packets received " scratch/wired.txt
#grep -E "server bytes sent" scratch/wired.txt
#grep -E "server bytes received" scratch/wired.txt
#grep -E "server average received packet size" scratch/wired.txt
#grep -E "server min received packet size" scratch/wired.txt
#grep -E "server max received packet size " scratch/wired.txt
#grep -E "server packet total transmission time" scratch/wired.txt
#grep -E "server average packet reception delay" scratch/wired.txt
#grep -E "server first packet send time" scratch/wired.txt
#grep -E "server last packet send time" scratch/wired.txt
#grep -E "server average send time" scratch/wired.txt
#grep -E "server average receive time " scratch/wired.txt
#grep -E "server average throughput" scratch/wired.txt
#grep -E "server reception average jitter" scratch/wired.txt
#grep -E "server Packet size histgram " scratch/wired.txt

#grep -E "Number of events" scratch/wired.txt

################### Phsysical layer stats for client  ########################
######## Flow ID:1 ===> Src Addr 10.1.1.1 Dst Addr 10.1.1.2 ######## 
#grep -E "Sent Packets" scratch/wired.txt
#grep -E "Received Packets" scratch/wired.txt
#grep -E "Send bytes by 10.1.1.1" scratch/wired.txt
#grep -E "Received bytes by 10.1.1.2" scratch/wired.txt
#grep -E "Lost Packets" scratch/wired.txt
#grep -E "Packet delivery ratio" scratch/wired.txt
#grep -E "Packet loss ratio" scratch/wired.txt
#grep -E "Delay" scratch/wired.txt
#grep -E "Jitter" scratch/wired.txt
#grep -E "Throughput out of 10.1.1.1" scratch/wired.txt
#grep -E "first time send by 10.1.1.1" scratch/wired.txt
#grep -E "last time send by 10.1.1.1" scratch/wired.txt
#grep -E "first time received by 10.1.1.2" scratch/wired.txt
#grep -E "last time received by 10.1.1.2 " scratch/wired.txt

######## Flow ID:2 ===> Src Addr 10.1.1.2 Dst Addr 10.1.1.1 ######## 
#grep -E "Sent Packets" scratch/wired.txt
#grep -E "Received Packets" scratch/wired.txt
#grep -E "Send bytes by 10.1.1.2" scratch/wired.txt
#grep -E "Received bytes by 10.1.1.1" scratch/wired.txt
#grep -E "Lost Packets" scratch/wired.txt
#grep -E "Packet delivery ratio" scratch/wired.txt
#grep -E "Packet loss ratio" scratch/wired.txt
#grep -E "Delay" scratch/wired.txt
#grep -E "Jitter" scratch/wired.txt
#grep -E "Throughput out of 10.1.1.2" scratch/wired.txt
#grep -E "first time send by 10.1.1.2" scratch/wired.txt
#grep -E "last time send by 10.1.1.2" scratch/wired.txt
#grep -E "first time received by 10.1.1.1" scratch/wired.txt
#grep -E "last time received by 10.1.1.1 " scratch/wired.txt


################### Total Results of the simulation physical layer ########################
#grep -E "Total sent packets " scratch/wired.txt
#grep -E "Total Received Packets" scratch/wired.txt
#grep -E "Total Lost Packets" scratch/wired.txt
#grep -E "Packet Loss ratio" scratch/wired.txt
#grep -E "Packet delivery ratio" scratch/wired.txt
#grep -E "Average Throughput" scratch/wired.txt
#grep -E "End to End Delay" scratch/wired.txt
#grep -E "End to End Jitter delay " scratch/wired.txt
#grep -E "Server Number of collisions " scratch/wired.txt
#grep -E "Client Number of collisions " scratch/wired.txt









