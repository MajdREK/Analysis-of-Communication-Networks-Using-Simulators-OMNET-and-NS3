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

#include "./CustomTcpSessionApp.h"
#include "inet/applications/base/ApplicationPacket_m.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/common/packet/chunk/BytesChunk.h"
#include "inet/networklayer/common/L3AddressResolver.h"


using namespace inet;


Define_Module(CustomTcpSessionApp);


#define MSGKIND_CONNECT    1
#define MSGKIND_SEND       2
#define MSGKIND_CLOSE      3


CustomTcpSessionApp::~CustomTcpSessionApp()
{
    cancelAndDelete(timeoutMsg);
}

void CustomTcpSessionApp::initialize(int stage)
{
    TcpAppBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        activeOpen = par("active");
        tOpen = par("tOpen");
        tSend = par("tSend");
        packetsCount = par("packetsCount");
        dataRate = par("dataRate");
        numBytes = par("numBytes");
        sendInterval = (numBytes * 8) / dataRate;
        EV << getFullPath() <<  " dataRate : " << dataRate<< " bits per second" << omnetpp::endl;
        EV << getFullPath() <<  "sendInterval :" << sendInterval<< " s" << omnetpp::endl;
		timeoutMsg = new cMessage("timer");
    }
}

void CustomTcpSessionApp::handleStartOperation(LifecycleOperation *operation)
{
    if (simTime() <= tOpen) {
        timeoutMsg->setKind(MSGKIND_CONNECT);
        scheduleAt(tOpen, timeoutMsg);
    }
}

void CustomTcpSessionApp::handleStopOperation(LifecycleOperation *operation)
{
    cancelEvent(timeoutMsg);
    if (socket.isOpen())
        close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void CustomTcpSessionApp::handleCrashOperation(LifecycleOperation *operation)
{
    cancelEvent(timeoutMsg);
    if (operation->getRootModule() != getContainingNode(this))
        socket.destroy();
}

void CustomTcpSessionApp::handleTimer(cMessage *msg)
{
    switch (msg->getKind()) {
        case MSGKIND_CONNECT:
            if (activeOpen)
                connect(); // sending will be scheduled from socketEstablished()
            else
                throw cRuntimeError("TODO");
            break;

        case MSGKIND_SEND:
            sendData();
            break;
        case MSGKIND_CLOSE:
            close();
            break;

        default:
            throw cRuntimeError("Invalid timer msg: kind=%d", msg->getKind());
    }
}

void CustomTcpSessionApp::sendData()
{
    sendPacket(createDataPacket(numBytes));
    if (firstSentPacketTime.isZero())
    {
       firstSentPacketTime = simTime();
    }

    lastSentPacketTime = simTime();
    if (--packetsCount) {
        scheduleAt( simTime() + sendInterval, timeoutMsg);
    } else {
        EV <<"will close"<<"\n";
        timeoutMsg->setKind(MSGKIND_CLOSE);
        scheduleAt(std::max(tClose, simTime()), timeoutMsg);
    }
}

Packet *CustomTcpSessionApp::createDataPacket(long sendBytes)
{
	EV << "CustomTcpSessionApp::createDataPacket" << omnetpp::endl;
	Ptr<Chunk> payload;
	payload = makeShared<ByteCountChunk>(B(sendBytes));
    payload->addTag<CreationTimeTag>()->setCreationTime(simTime());
	Packet* packet = new Packet("data1");
	packet->insertAtBack(payload);
	return packet;
}

void CustomTcpSessionApp::socketEstablished(TcpSocket *socket)
{
    TcpAppBase::socketEstablished(socket);
    timeoutMsg->setKind(MSGKIND_SEND);	
    scheduleAt(simTime() , timeoutMsg);
}

void CustomTcpSessionApp::socketDataArrived(TcpSocket *socket, Packet *msg, bool urgent)
{
    EV << "\n" <<"CustomTcpSessionApp::socketDataArrived"<<omnetpp::endl;

    if (msg)
    {
        auto data = msg->peekData();
        if (data){
            auto regions = data->getAllTags<CreationTimeTag>(); // get all tag regions
            for (auto& region : regions) { // for each region do
                auto tag = region.getTag();
                if (tag)
                {
                    auto creationTime = tag->getCreationTime(); // original time
                    auto delay = simTime() - creationTime; // compute delay
                    // calculate jitter
                     double delayDiffrance = 0.0; // Difference between past delay and current delay
                     if (m_PreviousPacketDelay == 0.0) // if, this is our first time receiving a packet and we have no previous delay
                     {
                       delayDiffrance = 0.0;         // first packet => we set delay diffrance to zero because there is not previous delay
                     }else { /// this is not our first packet  , and we have a previous packet , we should calculate using current and previous delay
                       delayDiffrance = std::abs(  delay.dbl() - m_PreviousPacketDelay ); // delay diffrence = abs (delay of this packet - delay of last packet)
                     }
                     this->m_jitterAccumulator += delayDiffrance; // jitter accumulator takes the sum of all diffrences in succesive packets delays
                     // jitter accumulator will at the end be devided by the total number of received packet to get the final jitter
                     this->m_PreviousPacketDelay =  delay.dbl(); // we save the current packet delay to be used for next time to calculate delay diffrence like on the top
                     // end of jitter
                    this->avrgDelay += delay.dbl();
                    this->avrgDelayCounter ++;
                    EV<<"delta = " << delay<<omnetpp::endl; // use data
                }
            }
        }
    }

        lastRcvdPacketTime = simTime();
        TcpAppBase::socketDataArrived(socket, msg, urgent);
}

void CustomTcpSessionApp::socketClosed(TcpSocket *socket)
{
    TcpAppBase::socketClosed(socket);
    cancelEvent(timeoutMsg);
    if (operationalState == State::STOPPING_OPERATION && !this->socket.isOpen())
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void CustomTcpSessionApp::socketFailure(TcpSocket *socket, int code)
{
    TcpAppBase::socketFailure(socket, code);
    cancelEvent(timeoutMsg);
}


void CustomTcpSessionApp::finish()
{
    EV << getFullPath() << ": received " << bytesRcvd << " bytes in " << packetsRcvd << " packets\n";
    EV << getFullPath() << ": sent " << bytesSent << " bytes in " << packetsSent << " packets\n";
    EV << getFullPath() << ": throughput " << (double(bytesSent)/125.0f) / (lastSentPacketTime-firstSentPacketTime) << "  kbps\n";
    EV << getFullPath() << ": lastSentPacketTime " << lastSentPacketTime << "  seconds\n";
    EV << getFullPath() << ": firstSentPacketTime " << firstSentPacketTime << "  seconds\n";
    EV << getFullPath() << ": lastRcvdPacketTime " << lastRcvdPacketTime << "  seconds\n";
    EV << getFullPath() << ": delay  " <<( avrgDelay / avrgDelayCounter ) << "s  \n";
    EV << getFullPath() << ": avrgDelayCounter  " <<(  avrgDelayCounter ) << "  \n";
    EV << getFullPath() << ": avrgDelayAcc  " <<(  avrgDelay ) << " \n";
    EV << getFullPath() << ": client reception average jitter : "<< m_jitterAccumulator / packetsRcvd << " seconds" << "  \n";
    EV << getFullPath() <<"Simmulation time : "<< simTime() <<"\n";
    recordScalar("bytesRcvd", bytesRcvd);
    recordScalar("bytesSent", bytesSent);
}

void CustomTcpSessionApp::refreshDisplay() const
{
    TcpAppBase::refreshDisplay();
    std::ostringstream os;
    os << TcpSocket::stateName(socket.getState()) << "\nsent: " << bytesSent << " bytes\nrcvd: " << bytesRcvd << " bytes";
    getDisplayString().setTagArg("t", 0, os.str().c_str());
}
