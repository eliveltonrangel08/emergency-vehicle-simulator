//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef EV_SBESC_TRACIVEHICLE11P_H_
#define EV_SBESC_TRACIVEHICLE11P_H_

#include "ev_sbesc/ev_sbesc.h"

#include "veins/veins.h"
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
using namespace veins;

namespace ev_sbesc {

class EV_SBESC_API TraCIEmergencyVehicle11p : public veins::DemoBaseApplLayer {
public:
    void initialize(int stage) override;

protected:

    simtime_t lastDroveAt;
    bool sentMessage;
    int currentSubscribedServiceId;

    bool a2t;                       /* Enable or disable A2T communications */
    simtime_t broadcastInterval;    /* [AMU] Interval between messages broadcast (in seconds) */
    int maxHop;                     /* Maximum number of hops of a message */
    double minForwardDistance;      /* Minimum distance from which a vehicle is selected to forward the message (in meters) */
    int warningDistance;            /* [A2V] Distance before which a vehicle will react when an ambulance approaches (in meters) */
    double laneChangeDuration;      /* [A2V] Duration for which a vehicle changes lanes (in seconds) */
    // ---------------------- Simulation parameters ----------------------

    long lastMessageTreeId;     /* Tree ID of the last message received */
    simtime_t lastBroadcastAt;  /* [AMU] Simulation time of the last message broadcasted */
    int priority;               /* Priority of the vehicle */
    std::string type;           /* Type of the vehicle*/

protected:
    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(DemoServiceAdvertisment* wsa) override;

    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;
};

}   //namespace ev_sbesc

#endif /* EV_SBESC_TRACIVEHICLE11P_H_ */
