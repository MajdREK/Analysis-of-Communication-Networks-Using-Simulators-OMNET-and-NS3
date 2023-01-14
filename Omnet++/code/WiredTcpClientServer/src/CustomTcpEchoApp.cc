//
// Copyright (C) 2004 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/applications/common/SocketTag_m.h"
#include "./CustomTcpEchoApp.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/packet/Packet_m.h"
#include "inet/transportlayer/contract/tcp/TcpCommand_m.h"


#include "inet/applications/sctpapp/SctpPeer.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/sctp/SctpCommand_m.h"
#include "inet/transportlayer/contract/sctp/SctpSocket.h"
#include "inet/transportlayer/sctp/SctpAssociation.h"


Define_Module(CustomTcpEchoApp);

Define_Module(CustomTcpEchoAppThread);

CustomTcpEchoApp::CustomTcpEchoApp()
{
}

CustomTcpEchoApp::~CustomTcpEchoApp()
{
}

void CustomTcpEchoApp::initialize(int stage)
{
    CustomTcpServerHostApp::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        delay = par("echoDelay");
        echoFactor = par("echoFactor");
        bytesRcvd = bytesSent = 0;
        WATCH(bytesRcvd);
        WATCH(bytesSent);
        WATCH(packetsSent);
        WATCH(packetsRcvd);

    }
}




void CustomTcpEchoApp::sendDown(Packet *msg)
{
    EV << "\n" <<"CustomTcpEchoApp::sendDown"<<omnetpp::endl;;
    Enter_Method_Silent();
    if (msg->isPacket()) {
        Packet *pk = static_cast<Packet *>(msg);
        bytesSent += pk->getByteLength();
        packetsSent ++;
        emit(packetSentSignal, pk);
    }
	take(msg);
    msg->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::tcp);
    if (firstSentPacketTime.isZero())
     {
       firstSentPacketTime = simTime();
     }
    lastSentPacketTime = simTime();
    send(msg, "socketOut");
}





void CustomTcpEchoApp::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();
    char buf[160];
    sprintf(buf, "threads: %d\nrcvd: %ld bytes\nsent: %ld bytes", socketMap.size(), bytesRcvd, bytesSent);
    getDisplayString().setTagArg("t", 0, buf);
}


void CustomTcpEchoApp::finish()
{
    EV << "\n" <<("CustomTcpEchoApp::finish")<<omnetpp::endl;;
    CustomTcpServerHostApp::finish();
    EV << getFullPath() << ": received " << bytesRcvd << " bytes in " << packetsRcvd << " packets\n";
    EV << getFullPath() << ": sent " << bytesSent << " bytes in " << packetsSent << " packets\n";
    EV << getFullPath() << ": throughput " << (double(bytesSent)/125.0f) / (lastSentPacketTime-firstSentPacketTime) << "  kbps\n";
    EV << getFullPath() << ": lastSentPacketTime " << lastSentPacketTime << "  seconds\n";
    EV << getFullPath() << ": firstSentPacketTime " << firstSentPacketTime << "  seconds\n";
    EV << getFullPath() << ": delay  " <<( avrgDelay / avrgDelayCounter ) << "s  \n";
    EV << getFullPath() << ": avrgDelayCounter  " <<(  avrgDelayCounter ) << " \n";
    EV << getFullPath() << ": server reception average jitter : "<< m_jitterAccumulator / packetsRcvd << " seconds" << "  \n";;
    EV << getFullPath() <<"Simmulation time : "<< simTime() <<"\n";

    // recordScalar("bytesRcvd", bytesRcvd);
   // recordScalar("bytesSent", bytesSent);

    /*
    cModule * mod = getModuleByPath("customClientServer.client.pppg$o[0].channel");
    cDatarateChannel* channel = dynamic_cast<cDatarateChannel*>(mod);
    channel->getre
    */
}

void CustomTcpEchoAppThread::established()
{
    EV << "\n" <<("CustomTcpEchoAppThread::established")<<omnetpp::endl;
}

void CustomTcpEchoAppThread::dataArrived(Packet *rcvdPkt, bool urgent)
{

    EV << "\n" <<("CustomTcpEchoAppThread::dataArrived\n")<<omnetpp::endl;;
	Enter_Method_Silent("");
	
    echoAppModule->emit(packetReceivedSignal, rcvdPkt);
    

	int64_t rcvdBytes = rcvdPkt->getByteLength();
    echoAppModule->bytesRcvd += rcvdBytes;
    echoAppModule->packetsRcvd++;



    if (rcvdPkt)
    {
        auto data = rcvdPkt->peekData();
        if (data){
            auto regions = data->getAllTags<CreationTimeTag>(); // get all tag regions
            for (auto& region : regions) { // for each region do
                auto tag = region.getTag();
                if (tag)
                {
                    auto creationTime = tag->getCreationTime(); // original time
                    auto delay = simTime() - creationTime; // compute delay
                    echoAppModule->avrgDelay += delay.dbl();



                    // calculate jitter
                     double delayDiffrance = 0.0; // diffrence between past delay and current delay
                     if (echoAppModule->m_PreviousPacketDelay == 0.0) // if, this is our first time receiving a packet and we have no previous delay
                     {
                       delayDiffrance = 0.0;         // first packet => we set delay diffrance to zero because there is not previous delay
                     }else { /// this is not our first packet  , and we have a previous packet , we should calculate using current and previous delay
                       delayDiffrance = std::abs(  delay.dbl() - echoAppModule->m_PreviousPacketDelay ); // delay diffrence = abs (delay of this packet - delay of last packet)
                     }
                     echoAppModule->m_jitterAccumulator += delayDiffrance; // jitter accumulator takes the sum of all diffrences in succesive packets delays
                     // jitter accumulator will at the end be devided by the total number of received packet to get the final jitter
                     // this->m_jitterAccumulator = m_PreviousPacketDelay == 0.0 ? 0.0 : std::abs( packetDelay - m_PreviousPacketDelay  );
                     echoAppModule->m_PreviousPacketDelay =  delay.dbl(); // we save the current packet delay to be used for next time to calculate delay diffrence like on the top
                     // end of jitter






                    recordScalar("ServerToClientAppDelay", delay.dbl() *1000.0f,"ms" );
                    echoAppModule->avrgDelayCounter ++;
                    EV<<"delta = " << delay<<omnetpp::endl; // use data
                }
            }
        }
    }


    if (echoAppModule->echoFactor > 0 && sock->getState() == TcpSocket::CONNECTED) {
        Packet *outPkt = new Packet(rcvdPkt->getName(), TCP_C_SEND);
        // reverse direction, modify length, and send it back
        int socketId = rcvdPkt->getTag<SocketInd>()->getSocketId();
        outPkt->addTag<SocketReq>()->setSocketId(socketId);
        long outByteLen = rcvdBytes * echoAppModule->echoFactor;
        if (outByteLen < 1)
            outByteLen = 1;
        int64_t len = 0;
        /*for ( ; len + rcvdBytes <= outByteLen; len += rcvdBytes) {
            outPkt->insertAtBack(rcvdPkt->peekDataAt(B(0), B(rcvdBytes)));
        }
        if (len < outByteLen)
            outPkt->insertAtBack(rcvdPkt->peekDataAt(B(0), B(outByteLen - len)));
        ASSERT(outPkt->getByteLength() == outByteLen);
        */
        Ptr<Chunk> payload;
        payload = makeShared<ByteCountChunk>(B(outByteLen));
        payload->addTag<CreationTimeTag>()->setCreationTime(simTime());
        outPkt->insertAtBack(payload);
        if (echoAppModule->delay == 0)
        {
            EV<<"Will send down"<<omnetpp::endl;
            echoAppModule->sendDown(outPkt);
        } else{
            EV<<"Will schedual"<<omnetpp::endl;
            scheduleAt(simTime() + echoAppModule->delay, outPkt); // send after a delay
        }
    }
    delete rcvdPkt;
}

  /*
   * Called when a timer (scheduled via scheduleAt()) expires. To be redefined.
   */
void CustomTcpEchoAppThread::timerExpired(cMessage *timer)
{
    EV << "\n" <<("CustomTcpEchoAppThread::timerExpired")<<omnetpp::endl;
	Enter_Method_Silent();
    Packet *pkt = check_and_cast<Packet *>(timer);
    if (pkt)
    {
        echoAppModule->sendDown(pkt);
    }else{
        EV << "\n" <<("Not a packet")<<omnetpp::endl;;
    }
}

void CustomTcpEchoAppThread::handleMessage(cMessage*msg)
{
	EV << "\n" <<("CustomTcpEchoAppThread::handleMessage")<<omnetpp::endl;
    if (msg->isSelfMessage())
    {
    if (msg->isPacket()) {
           Packet *pk = static_cast<Packet *>(msg);
           echoAppModule->sendDown(pk);
       }
    }
    else {
        if (msg->isPacket()) {
               Packet *pk = static_cast<Packet *>(msg);
               dataArrived(pk,true);
           }
    }
}




