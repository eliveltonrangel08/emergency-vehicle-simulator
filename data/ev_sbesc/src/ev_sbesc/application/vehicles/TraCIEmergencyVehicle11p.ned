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

package org.car2x.veins.subprojects.ev_sbesc.application.vehicles;

//
// TODO auto-generated type
//
import org.car2x.veins.modules.application.ieee80211p.DemoBaseApplLayer;

simple TraCIEmergencyVehicle11p extends DemoBaseApplLayer {
    parameters:
        // ---------------------- Simulation parameters ----------------------
        bool a2t;						// Enable or disable A2T communications
        int broadcastInterval;    		// [AMU] Interval between messages broadcast (in seconds)
        int maxHop;                     // Maximum number of hops of a message
        int warningDistance;            // [A2V] Distance before which a vehicle will react when an ambulance approaches (in meters)
        double minForwardDistance;      // Minimum distance from which a vehicle is selected to forward the message (in meters)
        double laneChangeDuration;      // [A2V] Duration for which a vehicle changes lanes (in seconds)
        // ---------------------- Simulation parameters ----------------------
    	@class(ev_sbesc::TraCIEmergencyVehicle11p);
		@display("i=block/app2");
}
