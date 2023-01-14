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
#ifndef __INET_TCPSESSIONAPP_H
#define __INET_TCPSESSIONAPP_H

#include <vector>

#include "inet/common/INETDefs.h"
#include "inet/applications/tcpapp/TcpAppBase.h"
#include "inet/common/lifecycle/LifecycleOperation.h"
#include "inet/common/lifecycle/NodeStatus.h"

using namespace inet;
/**
 * Single-connection TCP application.
 */
class   CustomTcpSessionApp : public TcpAppBase
{
  protected:


    bool activeOpen = false;
    simtime_t tOpen;
    simtime_t tSend;
    simtime_t tClose;
	int packetsCount;
	double dataRate = 0;
	double sendInterval = 0;
    int numBytes = 0;
    // state
    int commandIndex = -1;
    cMessage *timeoutMsg = nullptr;


    double avrgDelay = 0;
    unsigned int avrgDelayCounter = 0;
    simtime_t firstSentPacketTime , lastSentPacketTime;
    simtime_t firstRcvdPacketTime , lastRcvdPacketTime;

    double m_PreviousPacketDelay  = 0.0f;                                // last received packer delay
    // Jitter = Sum( Abs( Delay( Packet_(m) ) - Delay(  Packet_(m-1) ) ) ) / Number of received packets
    double m_jitterAccumulator = 0.0f;                                // sum of all packet delays that is later devided over the number of received packets to get the jitter


  protected:
    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void finish() override;
    virtual void refreshDisplay() const override;


    virtual Packet *createDataPacket(long sendBytes);
    virtual void sendData();

    virtual void handleTimer(cMessage *msg) override;
    virtual void socketEstablished(TcpSocket *socket) override;
    virtual void socketDataArrived(TcpSocket *socket, Packet *msg, bool urgent) override;
    virtual void socketClosed(TcpSocket *socket) override;
    virtual void socketFailure(TcpSocket *socket, int code) override;

  public:
    CustomTcpSessionApp() {}
    virtual ~CustomTcpSessionApp();
};


#endif // ifndef __INET_TCPSESSIONAPP_H

