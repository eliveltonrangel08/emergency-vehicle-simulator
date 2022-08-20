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
#include "TraCIVehicle11p.h"
#include "ev_sbesc/Message11p_m.h"
#include "ev_sbesc/application/utils/RandomCriticalEvent.h"

using namespace ev_sbesc;

Define_Module(ev_sbesc::TraCIVehicle11p);

void TraCIVehicle11p::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
    }

    RandomCriticalEvent rce;

//    std::cout << "RANDOM: " << rce.getRandomEvent() << endl;
}

//void TraCIVehicle11p::onWSA(DemoServiceAdvertisment* wsa)
//{
//    if (currentSubscribedServiceId == -1) {
//        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
//        currentSubscribedServiceId = wsa->getPsid();
//        if (currentOfferedServiceId != wsa->getPsid()) {
//            stopService();
//            startService(static_cast<Channel>(wsa->getTargetChannel()), wsa->getPsid(), "Mirrored Traffic Service");
//        }
//    }
//}

//void TraCIVehicle11p::onWSM(BaseFrame1609_4* frame) {
//    Message11p* wsm = check_and_cast<Message11p*>(frame);
//
//    long messageTreeId = frame->getTreeId();

//    findHost()->getDisplayString().setTagArg("i", 1, "green");
//
//    if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(wsm->getDemoData(), 9999);
//    if (!sentMessage) {
//        sentMessage = true;
//        // repeat the received traffic update once in 2 seconds plus some random delay
//        wsm->setSenderAddress(myId);
//        wsm->setSerial(3);
//        scheduleAt(simTime() + 2 + uniform(0.01, 0.2), wsm->dup());
//    }
//}

//void TraCIVehicle11p::handleSelfMsg(cMessage* msg) {
//    if (Message11p* wsm = dynamic_cast<Message11p*>(msg)) {
//        // send this message on the service channel until the counter is 3 or higher.
//        // this code only runs when channel switching is enabled
//        sendDown(wsm->dup());
//        wsm->setSerial(wsm->getSerial() + 1);
//        if (wsm->getSerial() >= 3) {
//            // stop service advertisements
//            stopService();
//            delete (wsm);
//        }
//        else {
//            scheduleAt(simTime() + 1, wsm);
//        }
//    }
//    else {
//        DemoBaseApplLayer::handleSelfMsg(msg);
//    }
//}

//void TraCIVehicle11p::handlePositionUpdate(cObject* obj) {
//    DemoBaseApplLayer::handlePositionUpdate(obj);

//    std::cout << "CAR: " << traciVehicle->getVType() << " | " << traciVehicle->getTypeId() << endl;


    // stopped for for at least 10s?
//    if (mobility->getSpeed() < 1) {
//        if (simTime() - lastDroveAt >= 10 && sentMessage == false) {
//            findHost()->getDisplayString().setTagArg("i", 1, "red");
//            sentMessage = true;
//
//            Message11p* wsm = new Message11p();
//            populateWSM(wsm);
//            wsm->setDemoData(mobility->getRoadId().c_str());
//
//            // host is standing still due to crash
//            if (dataOnSch) {
//                startService(Channel::sch2, 42, "Traffic Information Service");
//                // started service and server advertising, schedule message to self to send later
//                scheduleAt(computeAsynchronousSendingTime(1, ChannelType::service), wsm);
//            }
//            else {
//                // send right away on CCH, because channel switching is disabled
//                sendDown(wsm);
//            }
//        }
//    }
//    else {
//        lastDroveAt = simTime();
//    }
//}
