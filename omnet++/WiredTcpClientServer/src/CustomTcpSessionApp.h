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
    /**
     * A flag to tell if the application is active or not, it is used by INET
     */
    bool activeOpen = false;
    /**
     * The time in which to open the application
     */
    simtime_t tOpen;
    /**
     * The time in which to start sending the packets
     */
    simtime_t tSend;
    /**
     * The time in which to close the application
     */
    simtime_t tClose;
    /**
     * The total number of packets to be sent by the client
     * This value is read from the ".ini" file
     */
	int packetsCount;
	/**
	 * The client datarate. the datarate in which the client will be sending packets
	 */
	double dataRate = 0;
	/**
	 * Send interval is calculated through the datarate
	 * It is the time interval to wait between sending packets
	 */
	double sendInterval = 0;
	/**
	 * The size of client packets in bytes
	 * This value is read from ".ini" file
	 */
	int numBytes = 0;
	/**
	 * A dummy variable that existed in the previous implementation of INET and now we don't use it
	 */
    int commandIndex = -1;
    cMessage *timeoutMsg = nullptr;

    /**
     * Average delay calculated at finish() method at the end of simulation
     */
    double avrgDelay = 0;
    /**
     * A counter used to calculate avrgDelay
     */
    unsigned int avrgDelayCounter = 0;
    /**
     * The time in which the first packet is sent
     */
    simtime_t firstSentPacketTime ;
    /**
     * The time in which the last packet is sent
     */
    simtime_t lastSentPacketTime;
    /**
     * The time in which the first echo packet is received
     */
    simtime_t firstRcvdPacketTime;
    /**
     * The time in which the last echo packet is received
     */
    simtime_t lastRcvdPacketTime;
    /**
     * Previous packet delay used to calculate jitter
     */
    double m_PreviousPacketDelay  = 0.0f;

    /**
     * The client received echo packets from the server
     * each time a packet is received the delay is calculated
     * but we also want to calculate the jiiter
     * we use an accumulator for that, such that for each received packet we do the following:
     * jitterAccumulator = jitterACCUMULATOR + ( delay of this packet - delay of previous packet)
     * and at the end we devide that accumulator by the number of received packet to be the average jitter
     * Jitter = Sum of difference in delay of each two successive packets
     * Jitter = Sum( Abs( Delay( this packet ) - Delay( previous packet ) ) ) / Number of received packets
     * m_jitterAccumulator is the sum of all packet delays that is in finish method divided over the number of received packets to get the jitter
     */
    double m_jitterAccumulator = 0.0f;

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
