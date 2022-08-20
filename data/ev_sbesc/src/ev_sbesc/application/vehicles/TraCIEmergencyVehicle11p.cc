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

#include "ev_sbesc/ev_sbesc.h"
#include "TraCIEmergencyVehicle11p.h"
#include "ev_sbesc/Message11p_m.h"

using namespace ev_sbesc;

Define_Module(ev_sbesc::TraCIEmergencyVehicle11p);

void TraCIEmergencyVehicle11p::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;

        // ---------------------- Simulation parameters ----------------------
       /**
        * <!> These parameters are set in the omnetpp.ini file <!>
        */
       a2t = par("a2t").boolValue();
       warningDistance = par("warningDistance");
       broadcastInterval = par("broadcastInterval");
       maxHop = par("maxHop");
       minForwardDistance = par("minForwardDistance");
       laneChangeDuration = par("laneChangeDuration");
       // ---------------------- Simulation parameters ----------------------

       lastMessageTreeId = 0;
       lastBroadcastAt = simTime();
       priority = 0;
    }
}

void TraCIEmergencyVehicle11p::onWSA(DemoServiceAdvertisment* wsa)
{
    if (currentSubscribedServiceId == -1) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
        currentSubscribedServiceId = wsa->getPsid();
        if (currentOfferedServiceId != wsa->getPsid()) {
            stopService();
            startService(static_cast<Channel>(wsa->getTargetChannel()), wsa->getPsid(), "Mirrored Traffic Service");
        }
    }
}

void TraCIEmergencyVehicle11p::onWSM(BaseFrame1609_4* frame) {
    Message11p* wsm = check_and_cast<Message11p*>(frame);

//    std::cout << "MESSAGE EV: " << wsm->getEvId() << endl;

    findHost()->getDisplayString().setTagArg("i", 1, "green");

    long messageTreeId = frame->getTreeId();

    if (lastMessageTreeId != messageTreeId) { // The message has not been processed yet
        lastMessageTreeId = messageTreeId;
        int wsmPriority = wsm->getPriority();

        if (wsm->getIsFromEv()) {
            Coord evCoord(wsm->getEvX(), wsm->getEvY());
            double distanceFromEv= traci->getDistance(curPosition, evCoord, false);

            if (distanceFromEv<= warningDistance) {
                std::string evLaneId = wsm->getEvLaneId();
                std::string evRoadId = traci->lane(evLaneId).getRoadId();
                std::string vehicleType = traciVehicle->getTypeId();

                if (vehicleType != "v_emergency" || (vehicleType == "v_emergency" && wsmPriority > priority)) {
                    traciVehicle->changeLane(0, laneChangeDuration);
                    // TODO: This needs to be improved.
                }
            }

            int hopCount = wsm->getHopCount();
            int maxHop = wsm->getMaxHop();

            if (hopCount < maxHop) { // Repeat the message if it has not exceeded its maximum number of hops

                Coord senderCoord(wsm->getSenderX(), wsm->getSenderY());
                double distanceFromSender = traci->getDistance(curPosition, senderCoord, false);

                if (distanceFromSender > minForwardDistance) {
                    wsm->setSenderAddress(myId);
                    wsm->setSenderX(mobility->getPositionAt(simTime()).x);
                    wsm->setSenderY(mobility->getPositionAt(simTime()).y);
                    wsm->setHopCount(++hopCount);
                    wsm->setSerial(3);
                    scheduleAt(simTime() + uniform(0.01,0.1), wsm->dup());
                }
            }
        }
    }
}

void TraCIEmergencyVehicle11p::handleSelfMsg(cMessage* msg)
{
    if (Message11p* wsm = dynamic_cast<Message11p*>(msg)) {
        // send this message on the service channel until the counter is 3 or higher.
        // this code only runs when channel switching is enabled
        sendDown(wsm->dup());
        wsm->setSerial(wsm->getSerial() + 1);
        if (wsm->getSerial() >= 3) {
            // stop service advertisements
            stopService();
            delete (wsm);
        }
        else {
            scheduleAt(simTime() + 1, wsm);
        }
    }
    else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}

void TraCIEmergencyVehicle11p::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);

//    std::cout << "EV: " << traciVehicle->get << " | " << traciVehicle->getTypeId() << endl;


    if (a2t) {
        if (traciVehicle->getTypeId() == "v_emergency") {
            findHost()->getDisplayString().setTagArg("i", 1, "red");

            if (priority == 0) {
                std::string id = mobility->getExternalId();

                // -----------------------------------
//                if      (id == "ev1")  priority = 2;
//                else if (id == "ev3")  priority = 2;
//                else if (id == "ev5")  priority = 2;
            }

            if (simTime()-lastBroadcastAt >= broadcastInterval) {
                double posX = mobility->getPositionAt(simTime()).x;
                double posY = mobility->getPositionAt(simTime()).y;

                Message11p* wsm = new Message11p();
                populateWSM(wsm);

                wsm->setIsFromEv(true);
                wsm->setEvId(mobility->getExternalId().c_str());
                wsm->setEvLaneId(traciVehicle->getLaneId().c_str());
                wsm->setPriority(priority);
                wsm->setSenderX(posX);
                wsm->setSenderY(posX);
                wsm->setEvX(posX);
                wsm->setEvY(posY);
                wsm->setMaxHop(maxHop);
                wsm->setHopCount(1);

                lastBroadcastAt = simTime();
                sendDown(wsm); // Send the message to the lower layer
            }
        }
    }
}
