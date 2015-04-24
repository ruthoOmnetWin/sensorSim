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

#include <AbstractMemory.h>

#define amountSensors 4
#define error -9999

AbstractMemory::AbstractMemory() {
    storageType = new std::string[amountSensors];
    storageValue = new int[amountSensors];
    for (int i = 0; i < amountSensors; i++) {
        storageType[i] = "";
        storageValue[i] = error;
    }
}

AbstractMemory::~AbstractMemory() {
    delete[] storageType;
    storageType = NULL;
    delete[] storageValue;
    storageValue = NULL;
}

void AbstractMemory::initialize(int stage)
{
    AbstractBatteryAccess::initialize(stage);
}

void AbstractMemory::handleMessage(cMessage *msg)
{
    draw();
    const char* name = msg->getName();
    SimpleSensorData* data = (SimpleSensorData*) msg->getParList().remove(name);
    int value = data->sensorData;
    std::string nameString = name;

    EV << "Got type: " << name << " with value:" << value << endl;

    if (readEntry(nameString) == error) {
        createEntry(nameString, value);
        EV << "New storage entry created." << endl;
    } else {
        updateEntry(nameString, value);
        EV << "Storage entry updated." << endl;
    }

    delete(msg);
}

void AbstractMemory::createEntry(std::string type, int value)
{
    int emptyId = -1;
    for (int i = 0; i < amountSensors; i++) {
        if (storageType[i] == "") {
            emptyId = i;
            break;
        }
    }
    if (emptyId == -1) {
        return;
    }
    storageType[emptyId] = type;
    storageValue[emptyId] = value;
}

int AbstractMemory::readEntry(std::string type)
{
    int id = getIdByType(type);
    if (id == -1) {
        return error;
    }
    return storageValue[id];
}

void AbstractMemory::updateEntry(std::string type, int value)
{
    int id = getIdByType(type);
    if (id == -1) {
        return createEntry(type, value);
    }
    storageValue[id] = value;
}

void AbstractMemory::deleteEntry(std::string type)
{
    int id = getIdByType(type);
    if (id == -1) {
        return;
    }
    storageValue[id] = error;
    storageType[id] = "";
}

int AbstractMemory::getIdByType(std::string type)
{
    int id = -1;
    for (int i = 0; i < amountSensors; i++) {
        if (storageType[i] == type) {
            id = i;
            break;
        }
    }
    return id;
}
