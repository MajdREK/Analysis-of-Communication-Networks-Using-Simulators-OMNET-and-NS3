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

#include "./CustomTcpServerHostApp.h"
#include "inet/common/INETUtils.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/networklayer/common/L3AddressResolver.h"


Define_Module(CustomTcpServerHostApp);

void CustomTcpServerHostApp::initialize(int stage)
{
    EV<<("CustomTcpServerHostApp::initialize")<<omnetpp::endl;
    ApplicationBase::initialize(stage);
}

void CustomTcpServerHostApp::handleStartOperation(LifecycleOperation *operation)
{
     EV<<("CustomTcpServerHostApp::handleStartOperation")<<omnetpp::endl;
    const char *localAddress = par("localAddress");
    int localPort = par("localPort");

    serverSocket.setOutputGate(gate("socketOut"));
    serverSocket.setCallback(this);
    serverSocket.bind(localAddress[0] ? L3Address(localAddress) : L3Address(), localPort);
    serverSocket.listen();
}

void CustomTcpServerHostApp::handleStopOperation(LifecycleOperation *operation)
{
     EV<<("CustomTcpServerHostApp::handleStopOperation")<<omnetpp::endl;;
    for (auto thread: threadSet)
        thread->getSocket()->close();
    serverSocket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void CustomTcpServerHostApp::handleCrashOperation(LifecycleOperation *operation)
{
    EV<<("CustomTcpServerHostApp::handleCrashOperation")<<omnetpp::endl;
    // remove and delete threads
    while (!threadSet.empty()) {
        auto thread = *threadSet.begin();
        // TODO: destroy!!!
        thread->getSocket()->close();
        removeThread(thread);
    }
    // TODO: always?
    if (operation->getRootModule() != getContainingNode(this))
        serverSocket.destroy();
}

void CustomTcpServerHostApp::refreshDisplay() const
{
    EV<<("CustomTcpServerHostApp::refreshDisplay")<<omnetpp::endl;
    ApplicationBase::refreshDisplay();
    char buf[32];
    sprintf(buf, "%d threads", socketMap.size());
    getDisplayString().setTagArg("t", 0, buf);
}

void CustomTcpServerHostApp::handleMessageWhenUp(cMessage *msg)
{
    cGate* gate = msg->getArrivalGate();
	
	gate->setDeliverOnReceptionStart(true);
	
	cChannel* c = gate->getChannel();
	if (c)
	    {
            EV << "channel->Calculateduration"<<c->calculateDuration(msg)<<omnetpp::endl;
            EV << "channel->getTransmissionFinishTime"<<c->getTransmissionFinishTime()- msg->getCreationTime() <<omnetpp::endl;
            EV << "channel->getCreationTime"<<simTime()- msg->getCreationTime() <<omnetpp::endl;
	    }else{
	        EV <<"No channel"<<omnetpp::endl;
	    }

    EV << ("CustomTcpServerHostApp::handleMessageWhenUp")<<omnetpp::endl;
    EV << "msg->getArrivalGate()->setDeliverOnReceptionStart(true);"<<omnetpp::endl;

    if (msg->isSelfMessage()) {	
        TcpServerThreadBase *thread = (TcpServerThreadBase *)msg->getContextPointer();
        if (threadSet.find(thread) == threadSet.end())
            throw cRuntimeError("Invalid thread pointer in the timer (msg->contextPointer is invalid)");
        thread->timerExpired(msg);
    }
    else {
        TcpSocket *socket = check_and_cast_nullable<TcpSocket*>(socketMap.findSocketFor(msg));
        if (socket)
        {
            EV << "socket->processMessage(msg);"<<omnetpp::endl ;
            socket->processMessage(msg);
        }
        else if (serverSocket.belongsToSocket(msg))
        {
            EV << " serverSocket.processMessage(msg);"<<omnetpp::endl ;
            serverSocket.processMessage(msg);
        }
        else {
             throw cRuntimeError("Unknown incoming message: '%s'", msg->getName());
            EV_ERROR << "message " << msg->getFullName() << "(" << msg->getClassName() << ") arrived for unknown socket \n";
            delete msg;
        }
    }			
}

void CustomTcpServerHostApp::finish()
{
    EV<<("CustomTcpServerHostApp::finish")<<omnetpp::endl;
    // remove and delete threads
    while (!threadSet.empty())
        removeThread(*threadSet.begin());
}

void CustomTcpServerHostApp::socketAvailable(TcpSocket *socket, TcpAvailableInfo *availableInfo)
{
    EV<<("CustomTcpServerHostApp::socketAvailable")<<omnetpp::endl;
    // new TCP connection -- create new socket object and server process
    TcpSocket *newSocket = new TcpSocket(availableInfo);
    newSocket->setOutputGate(gate("socketOut"));
    const char *serverThreadModuleType = par("serverThreadModuleType");
    cModuleType *moduleType = cModuleType::get(serverThreadModuleType);
    char name[80];
    sprintf(name, "thread_%i", newSocket->getSocketId());
    TcpServerThreadBase *proc = check_and_cast<TcpServerThreadBase *>(moduleType->create(name, this));
    proc->finalizeParameters();
    proc->callInitialize();
    newSocket->setCallback(proc);
    proc->init(this, newSocket);
    socketMap.addSocket(newSocket);
    threadSet.insert(proc);
    socket->accept(availableInfo->getNewSocketId());
}

void CustomTcpServerHostApp::socketClosed(TcpSocket *socket)
{
    EV<<("CustomTcpServerHostApp::socketClosed")<<omnetpp::endl;
    if (operationalState == State::STOPPING_OPERATION && threadSet.empty() && !serverSocket.isOpen())
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void CustomTcpServerHostApp::removeThread(TcpServerThreadBase *thread)
{
    EV<<("CustomTcpServerHostApp::removeThread")<<omnetpp::endl;
    // remove socket
    socketMap.removeSocket(thread->getSocket());
    threadSet.erase(thread);
    // remove thread object
    thread->deleteModule();
}

void CustomTcpServerHostApp::threadClosed(TcpServerThreadBase *thread)
{
    EV<<("CustomTcpServerHostApp::threadClosed")<<omnetpp::endl;
    // remove socket
    socketMap.removeSocket(thread->getSocket());
    threadSet.erase(thread);

    socketClosed(thread->getSocket());

    // remove thread object
    thread->deleteModule();
}

void TcpServerThreadBase::refreshDisplay() const
{
    getDisplayString().setTagArg("t", 0, TcpSocket::stateName(sock->getState()));
}


