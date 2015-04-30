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

AbstractSensingUnit::AbstractSensingUnit() {
    // TODO Auto-generated constructor stub

}

AbstractSensingUnit::~AbstractSensingUnit() {
    // TODO Auto-generated destructor stub
}

void AbstractSensingUnit::initialize(int stage) {
    BatteryAccess::initialize(stage);
    if (stage == 0) {
        CustomWorldUtility *World = FindModule<CustomWorldUtility*>::findGlobalModule();

        BasePhyLayer* phy = FindModule<BasePhyLayer*>::findGlobalModule();
        pMobType = phy->getMobilityModule();
        //save world and provide data inside world
        this->world = World;
        EV << "CustomWorldUtility found" << endl;
    } else if (stage == 1) {
        readAndForward();
    }
}

void AbstractSensingUnit::readAndForward()
{
    int value = readData();
    EV << "Read data " << value << endl;
    cModule* Sensor = getParentModule();
    std::string name = Sensor->par("type");
    ExtendedMessage *newmsg = generateMessage(name.c_str());
    SimpleSensorData* data = new SimpleSensorData(name.c_str(), value);
    newmsg->getParList().add(data);
    draw();
    send(newmsg, "toSignalConditioner");
}

Coord* AbstractSensingUnit::getLocation()
{
    Coord* back;
    BasePhyLayer* phy = FindModule<BasePhyLayer*>::findSubModule(this->getParentModule()->getParentModule());
    ChannelMobilityPtrType pMobType = phy->getMobilityModule();
    if(pMobType != NULL){
        back = new Coord(pMobType->getCurrentPosition());
        return back;
    }
    return new Coord();
}

int AbstractSensingUnit::readData()
{
    draw();
    Coord *position = getLocation();
    //TODO check for the type
    cModule* Sensor = getParentModule();
    std::string type = Sensor->par("type");
    int data = world->getValueByPosition(type, position);
    delete position;
    return data;
}

ExtendedMessage* AbstractSensingUnit::generateMessage(const char* msgname)
{
    int src = getIndex();
    int dest = getParentModule()->getSubmodule("SignalConditioner")->getIndex();
    ExtendedMessage *msg = new ExtendedMessage(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

void AbstractSensingUnit::handleMessage(cMessage *msg)
{
    draw();
    std::string name = msg->getName();
    if (name == "startMeasuring") {
        readAndForward();
    }
    delete(msg);
}
