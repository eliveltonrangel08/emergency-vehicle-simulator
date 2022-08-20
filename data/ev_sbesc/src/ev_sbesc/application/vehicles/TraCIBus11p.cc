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
#include "TraCIBus11p.h"
#include "ev_sbesc/Message11p_m.h"

using namespace ev_sbesc;

Define_Module(ev_sbesc::TraCIBus11p);

void TraCIBus11p::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
    }
}

void TraCIBus11p::onWSA(DemoServiceAdvertisment* wsa)
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

void TraCIBus11p::onWSM(BaseFrame1609_4* frame)
{
//    Message11p* wsm = check_and_cast<Message11p*>(frame);

    long messageTreeId = frame->getTreeId();

    std::cout << "BUS messageTreeId: " << messageTreeId << endl;
}

void TraCIBus11p::handleSelfMsg(cMessage* msg)
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

void TraCIBus11p::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);

    std::cout << "BUS: " << traciVehicle->getVType() << " | " << traciVehicle->getTypeId() << endl;

    // stopped for for at least 10s?
//    if (mobility->getSpeed() < 1) {
//        if (simTime() - lastDroveAt >= 10 && sentMessage == false) {
//            findHost()->getDisplayString().setTagArg("i", 1, "red");
//            sentMessage = true;
//
//            TraCIDemo11pMessage* wsm = new TraCIDemo11pMessage();
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
}
