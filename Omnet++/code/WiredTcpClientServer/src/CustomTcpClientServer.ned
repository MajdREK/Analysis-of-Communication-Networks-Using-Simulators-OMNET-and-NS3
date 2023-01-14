//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

package customtcpclientserver;

import inet.common.misc.NetAnimTrace;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
//import inet.networklayer.configurator.ipv4.Ipv4NodeConfigurator;
import inet.node.inet.StandardHost;
import ned.DatarateChannel;
import inet.common.misc.ThruputMeteringChannel;

network customClientServer
{
    types:
        channel C extends ThruputMeteringChannel
        {
            @signal[channelBusy](type=long);
            @signal[messageSent](type=omnetpp::cMessage);
            @signal[messageDiscarded](type=omnetpp::cMessage);
            @statistic[busy](source=channelBusy; record=vector?; interpolationmode=sample-hold);
            @statistic[utilization](source="timeavg(channelBusy)"; record=stats?);
            @statistic[packets](source="constant1(messageSent)"; record=count?; interpolationmode=none);
            @statistic[packetBytes](source="packetBytes(messageSent)"; record=sum?; unit=B; interpolationmode=none);
            @statistic[packetsDiscarded](source="constant1(messageDiscarded)"; record=count?; interpolationmode=none);
            @statistic[throughput](source="sumPerDuration(packetBytes(messageSent)/100000000)"; record=stats?; unit=Bps);   
			datarate = 100Mbps;
            delay = 0.0000004s;
        }
    submodules:
        client: StandardHost {
            parameters:
                @display("p=186,150;i=device/pc3");
			//	eth[*].typename="EthernetInterface";        
            //    eth[*].csmacdSupport = true;
             //   eth[*].mac.duplexMode = false;
        	//	tcp.advertisedWindow = 10240;
            //    tcp.nagleEnabled = false;
        	}
        server: StandardHost {
            parameters:
                @display("p=741,150;i=device/pc2");
			//	eth[*].typename="EthernetInterface";        
           //     eth[*].csmacdSupport = true;
            //    eth[*].mac.duplexMode = false;
        	//	tcp.advertisedWindow = 10240;
            //    tcp.nagleEnabled = false;
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=100,100;is=s");
        }
        netAnimTrace: NetAnimTrace {
            @display("p=100,200;is=s");
        }
    connections:
	        client.ethg++ <--> C <--> server.ethg++;
}