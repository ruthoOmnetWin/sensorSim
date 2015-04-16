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

#include <AbstractBatteryAccess.h>

AbstractBatteryAccess::AbstractBatteryAccess() {
    // TODO Auto-generated constructor stub

}

AbstractBatteryAccess::~AbstractBatteryAccess() {
    // TODO Auto-generated destructor stub
}

void AbstractBatteryAccess::initialize(int stage) {
    MiximBatteryAccess::initialize(stage);
    if (stage == 0) {
        registerWithBattery("Transducer", 1);
        EV << "Registered with Battery" << endl;
        currentOverTime = par("currentConsumption").doubleValue();
        energiePerOperation = par("energyConsumption").doubleValue();
        drawCurrent(currentOverTime, 0);
        //HostState::States state = battery->getState();
    }
}

void AbstractBatteryAccess::draw() {
    drawEnergy(energiePerOperation, 0);
}
