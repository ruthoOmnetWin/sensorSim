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

#include <AbstractSensingUnit.h>
#include <CustomWorldUtility.h>
#include <FindModule.h>

AbstractSensingUnit::AbstractSensingUnit() {
    // TODO Auto-generated constructor stub

}

AbstractSensingUnit::~AbstractSensingUnit() {
    // TODO Auto-generated destructor stub
}

void AbstractSensingUnit::initialize(int stage) {
    if (stage == 0) {
        CustomWorldUtility *World = FindModule<CustomWorldUtility*>::findGlobalModule();
        //save world and provide data inside world
        this->world = World;
        EV << "CustomWorldUtility found" << endl;
    } else if (stage == 1) {

    }
}

float AbstractSensingUnit::readData() {
    Coord *position = new Coord;
    return world->getValueByPosition("Temperature", position);
}
