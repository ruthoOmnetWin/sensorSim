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

#ifndef CUSTOMDICEAPPLICATION_H_
#define CUSTOMDICEAPPLICATION_H_

#include <DiceApplication.h>
#include <WakeUpPacket_m.h>
#include <NetwControlInfo.h>

class CustomDiceApplication : public DiceApplication
{
    bool active;
public:
    void handleMessage(cMessage * msg);

    void handleHostState(const HostState& state);
};

#endif /* CUSTOMDICEAPPLICATION_H_ */
