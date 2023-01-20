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
import inet.node.inet.StandardHost;
import ned.DatarateChannel;

network ethernetTcpClientServer
{
    types:
        channel C extends DatarateChannel
        {
			datarate = 100Mbps;
            delay = 0.0000004s;
        }
    submodules:
        client: StandardHost {
            parameters:
                @display("p=186,150;i=device/pc3");
        	}
        server: StandardHost {
            parameters:
                @display("p=741,150;i=device/pc2");
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