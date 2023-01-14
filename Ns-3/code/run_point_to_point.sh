rm -f scratch/wired.txt
for dataRate in 0.5Mbps 1Mbps 2Mbps 4Mbps 8Mbps 16Mbps 32Mbps 64Mbps 128Mbps 256Mbps 512Mbps
do
./waf -v --run "scratch/tcpClientServer.cc 
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
 
#grep -E "throughput" scratch/wired.txt



