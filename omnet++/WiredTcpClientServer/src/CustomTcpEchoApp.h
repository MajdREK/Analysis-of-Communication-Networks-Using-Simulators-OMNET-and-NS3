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

#ifndef __INET_TCPECHOAPP_H
#define __INET_TCPECHOAPP_H

#include "inet/common/INETDefs.h"

#include "./CustomTcpServerHostApp.h"
#include "inet/common/INETMath.h"
#include "inet/transportlayer/contract/tcp/TcpSocket.h"


using namespace inet;


/**
* Accepts any number of incoming connections, and sends back whatever
* arrives on them.
*
* This module hosts TCP-based server applications. It dynamically creates
* and launches a new "CustomTcpEchoAppThread" object for each incoming connection.
*
*
*/
class INET_API CustomTcpEchoApp : public CustomTcpServerHostApp
{
  protected:
    /**
     * the echo delay that will be received as parameter
     */
    simtime_t delay;
    /**
     * packet echo factor
    */
    double echoFactor = NaN;
    /**
     * total count of received bytes
     */
    long bytesRcvd = 0;

    /**
     * total count of sent bytes
     */
    long bytesSent = 0;

    /**
     * total count of sent packets
     */
    int packetsSent = 0;

    /**
     * total count of received packets
     */
    int packetsRcvd = 0;

    /**
     * the average delay of all packets coming from client
     */
    double avrgDelay = 0;

    /**
     * A number that is incremented in every new incoming packet , we used it in the method finish() to calculate the average of all statistics by dividing on it
     */
    unsigned int avrgDelayCounter = 0;

    /**
     * This always hold the time in which the last packet was sent
     */
    simtime_t firstSentPacketTime;
    /**
     * This always holds the time in which the last packet was eched
     */
    simtime_t lastSentPacketTime;

    /**
     * last received packet delay
     */
    double m_PreviousPacketDelay  = 0.0f;

    /**
     * Jitter = Sum( Abs( Delay( Packet_(m) ) - Delay(  Packet_(m-1) ) ) ) / Number of received packets
     * Actual jitter is calculated at the end in finish()
     */
    double m_jitterAccumulator = 0.0f;                                // sum of all packet delays that is later in the finish() method divided over the number of received packets to get the average jitter

  protected:
    virtual void sendDown(Packet *packet);

    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void finish() override;
    virtual void refreshDisplay() const override;

  public:
    CustomTcpEchoApp();
    ~CustomTcpEchoApp();
  
    friend class CustomTcpEchoAppThread;
};


/**
* This is a server thread class that is instantiated by CustomTcpEchoApp
* for every new incoming connection and is responsible for handling the new client.
* Server threads should be subclassed from the TcpServerThreadBase
* This thread object will receive events
* via a callback interface (methods like established(), dataArrived(),
* peerClosed(), timerExpired()), and can send packets via TcpSocket's send()
* method.
 */
class INET_API CustomTcpEchoAppThread : public TcpServerThreadBase
{
  protected:
    CustomTcpEchoApp *echoAppModule = nullptr;
  public:
    /**
     * Called when connection is established.
     */
    virtual void established() override;
    /**
     * Called when a data packet arrives. To be redefined.
     */
    virtual void dataArrived(Packet *msg, bool urgent) override;
    virtual void handleMessage(cMessage*) override;
    /**
     * Called when a timer (scheduled via scheduleAt()) expires. To be redefined.
     */
    virtual void timerExpired(cMessage *timer) override;

    virtual void init(CustomTcpServerHostApp *hostmodule, TcpSocket *socket) override {
        TcpServerThreadBase::init(hostmodule, socket);
        echoAppModule = check_and_cast<CustomTcpEchoApp *>(hostmod);
    }
};


#endif // ifndef __INET_TCPECHOAPP_H

