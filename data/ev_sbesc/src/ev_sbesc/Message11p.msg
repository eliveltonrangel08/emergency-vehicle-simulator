//
// Copyright (C) 2011 David Eckhoff <eckhoff@cs.fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

cplusplus {{
#include "veins/base/utils/Coord.h"
#include "veins/modules/messages/BaseFrame1609_4_m.h"
#include "veins/base/utils/SimpleAddress.h"
}}

namespace ev_sbesc;

class veins::BaseFrame1609_4;
class noncobject veins::Coord;
class veins::LAddress::L2Type extends void;

packet Message11p extends BaseFrame1609_4 {
    string demoData;
    veins::LAddress::L2Type senderAddress = -1;
    int serial = 0;
    
    // -------------------------- A2T --------------------------
	bool isFromEv;	// Is the message sent by an ambulance ?
	string evId;			// ID of the ambulance
	int priority; 			// Priority of the message
	string evLaneId; 		// Lane ID of the ambulance
	double evX;			// x position of the ambulance
	double evY;			// y position of the ambulance
	double senderX;			// x position of the sender
	double senderY;			// y position of the sender
	int maxHop;				// Maximum number of hops of the message (lifespan)
	int hopCount; 			// Number of hops of the message
	// -------------------------- A2T --------------------------
}
