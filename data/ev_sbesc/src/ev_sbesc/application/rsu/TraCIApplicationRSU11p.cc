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

#include "TraCIApplicationRSU11p.h"
#include "ev_sbesc/Message11p_m.h"

using namespace ev_sbesc;

Define_Module(ev_sbesc::TraCIApplicationRSU11p);

void TraCIApplicationRSU11p::initialize(int stage) {
   DemoBaseApplLayer::initialize(stage);

   if (stage == 0) {
       // ---------------------- Simulation parameters ----------------------
       /**
        * <!> These parameters are set in the omnetpp.ini file <!>
        */
       reinitializationDelay = par("reinitializationDelay");
       tlDistance = par("tlDistance");
//       associatedTlId = par("associatedTl");
       // ---------------------- Simulation parameters ----------------------

       initialized = false;
       lastMessageTreeId = 0;
       lastUpdate = simTime();
       highestPriority = 0;

   }

//   std::cout << "RSU: " << getSimulation()->getContextModule() << endl;
}

void TraCIApplicationRSU11p::onWSA(DemoServiceAdvertisment* wsa) {

    std::cout << "WSA MESSAGE: " << wsa->getPsid() << endl;
    // if this RSU receives a WSA for service 42, it will tune to the chan
    if (wsa->getPsid() == 5) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
    }
}

void TraCIApplicationRSU11p::onWSM(BaseFrame1609_4* frame) {
    Message11p* wsm = check_and_cast<Message11p*>(frame);

    if (!initialized) {
        setTraCI();
        associateTrafficlight();
        initialized = true;
    }

//    std::cout << "RSU Message: " << frame->getId() << " treeId: " << frame->getTreeId() << " atID: " << associatedTlId << " evId: " << wsm->getEvId() << endl;

    if (!associatedTlId.empty()) {
            TraCICommandInterface::Trafficlight associatedTl = traci->trafficlight(associatedTlId);

            long messageTreeId = wsm->getTreeId();

//            std::cout << "RSU ID: " << getParentModule()->getIndex() << " EV ID: " << wsm->getEvId() << " roadId: " << wsm->getEvLaneId() << " tl ID: " << associatedTlId << endl;

            if (lastMessageTreeId != messageTreeId) { // The message has not been processed yet
                lastMessageTreeId = messageTreeId;

                EV << "Traffic light state:" << endl;
                EV << "  - Cooldown: " << simTime()-lastUpdate << endl;
                EV << "  - Highest priority: " << highestPriority << endl;
                EV << "  - Last emergency vehicle ID: " << memorizedEvId << endl;
                EV << "  - Last update: " << lastUpdate << endl;

                if (simTime()-lastUpdate >= reinitializationDelay) {
                    lastUpdate = simTime();
                    memorizedEvId = "none";
                    highestPriority = 0;
                    associatedTl.reinitialize(); // Check if the traffic light has to be set back to its normal state
                }

                if (wsm->getIsFromEv()) {

                    std::string evLaneId = wsm->getEvLaneId();
                    std::string evRoadId = traci->lane(evLaneId).getRoadId();

                    if (associatedTl.isControlling(evRoadId)) {
                        int wsmPriority = wsm->getPriority();
                        std::string wsmEvId = wsm->getEvId();

                        std::cout << "RSU: " << getParentModule()->getIndex() <<  " | TL: " << associatedTlId << " | EV: " << wsm->getEvId() << endl;

                        if (wsmPriority == highestPriority) {
                            if (wsmEvId == memorizedEvId || memorizedEvId == "none") {
                                associatedTl.prioritizeRoad(evRoadId);
                                update(wsmEvId, wsmPriority);
                            }
                        }
                        else if (wsmPriority > highestPriority) {
                            associatedTl.prioritizeRoad(evRoadId);
                            update(wsmEvId, wsmPriority);
                        }
                    }
                }
            }
            else EV << "<!> This message has already been processed." << endl;
        }

    // this rsu repeats the received traffic update in 2 seconds plus some random delay
//    sendDelayedDown(wsm->dup(), 2 + uniform(0.01, 0.2));
}

void TraCIApplicationRSU11p::setTraCI()
{
    veins::TraCIScenarioManager* manager = veins::TraCIScenarioManagerAccess().get();
    traci = manager->getCommandInterface();
}

void TraCIApplicationRSU11p::associateTrafficlight()
{
    for (std::string junctionId: traci->getJunctionIds()) {
        TraCICommandInterface::Junction junction = traci->junction(junctionId);
        double distanceFromJunction = traci->getDistance(curPosition, junction.getPosition(), false);

//        std::cout << junctionId << ", " << distanceFromJunction << endl;

        if (distanceFromJunction < tlDistance) {
            for (std::string tlId: traci->getTrafficlightIds()) {
//                std::cout << "TL ID: " << tlId <<distanceFromJunction << endl;
                if (tlId.find(junctionId) != string::npos) associatedTlId = tlId;
            }

        }
    }

}

void TraCIApplicationRSU11p::update(std::string memorizedAmuId, int highestPriority)
{
    this->memorizedEvId = memorizedEvId;
    this->highestPriority = highestPriority;
    lastUpdate = simTime();
}

