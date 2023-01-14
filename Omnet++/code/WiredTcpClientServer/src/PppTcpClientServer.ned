package customtcpclientserver;
import inet.common.misc.NetAnimTrace;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.StandardHost;
import ned.DatarateChannel;
import inet.common.misc.ThruputMeteringChannel;

network pppTcpClientServer
{
    types:
        channel C extends ThruputMeteringChannel
        {
			datarate = 100Mbps;
            delay = 0.0000004s;
            thruputDisplayFormat = "b B U";
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
	        client.pppg++ <--> C <--> server.pppg++;
}