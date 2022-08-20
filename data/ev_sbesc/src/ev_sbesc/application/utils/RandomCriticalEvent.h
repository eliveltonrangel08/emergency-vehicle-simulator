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

#ifndef RANDOMCRITICALEVENT_H_
#define RANDOMCRITICALEVENT_H_

#pragma once

#include <time.h>

namespace ev_sbesc {
class EV_SBESC_API RandomCriticalEvent {
public:
    RandomCriticalEvent();
    virtual ~RandomCriticalEvent();
    int getRandomEvent();

protected:
    int randomSeed;
};
}

#endif /* RANDOMCRITICALEVENT_H_ */
