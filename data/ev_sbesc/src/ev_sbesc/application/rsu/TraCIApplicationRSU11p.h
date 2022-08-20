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

#ifndef EV_SBESC_TRACIAPPLICATIONRSU11P_H_
#define EV_SBESC_TRACIAPPLICATIONRSU11P_H_

#pragma once

#include "ev_sbesc/ev_sbesc.h"
#include "veins/veins.h"
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

using namespace veins;
using namespace omnetpp;
using namespace std;

namespace ev_sbesc {
class EV_SBESC_API TraCIApplicationRSU11p : public veins::DemoBaseApplLayer {
public:
    void initialize(int stage) override;

protected:
    // ---------------------- Simulation parameters ----------------------
    /**
     * <!> These parameters are set in the omnetpp.ini file <!>
     */
    simtime_t reinitializationDelay; /* Time after which the RSU resets if it has not been updated (in seconds) */
    // ---------------------- Simulation parameters ----------------------

    bool initialized;           /* Initialization state of the RSU */
//    ::omnetpp::opp_string associatedTlId; /* ID of the traffic light associated to the RSU */
    string associatedTlId; /* ID of the traffic light associated to the RSU */
    long lastMessageTreeId;     /* Tree ID of the last message received */
    simtime_t lastUpdate;       /* Time of the last update */
    string memorizedEvId; /* Ambulance ID memorized by the RSU */
    int highestPriority;        /* Highest priority recorded */


    int tlDistance;              /* Distance of the traffic light to the related RSU */

protected:
    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(DemoServiceAdvertisment* wsa) override;

private:
    /**
     * Set up the TraCI interface
     */
    void setTraCI();

    /**
     * Associate a close traffic light with the RSU
     */
    void associateTrafficlight();

    /**
     * Update the RSU information
     * @param memorizedAmuId Ambulance ID memorized
     * @param highestPriority Highest priority recorded
     */
    void update(std::string memorizedAmuId, int highestPriority);
};
}   //namespace ev_sbesc

#endif /* EV_SBESC_TRACIAPPLICATIONRSU11P_H_ */
