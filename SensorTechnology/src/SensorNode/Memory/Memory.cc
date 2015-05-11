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

#include <Memory.h>

#define error -9999

Memory::Memory() {
    storageType = new std::string[storageSize];
    storageValue = new int[storageSize];
    for (int i = 0; i < storageSize; i++) {
        storageType[i] = "";
        storageValue[i] = error;
    }
}

Memory::~Memory() {
    delete[] storageType;
    storageType = NULL;
    delete[] storageValue;
    storageValue = NULL;
}

void Memory::initialize(int stage)
{
    BatteryAccess::initialize(stage);
}

void Memory::handleMessage(cMessage *msg)
{
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
    draw();
}

void Memory::createEntry(std::string type, int value)
{
    int emptyId = -1;
    for (int i = 0; i < storageSize; i++) {
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

int Memory::readEntry(std::string type)
{
    int id = getIdByType(type);
    if (id == -1) {
        return error;
    }
    return storageValue[id];
}

void Memory::updateEntry(std::string type, int value)
{
    int id = getIdByType(type);
    if (id == -1) {
        return createEntry(type, value);
    }
    storageValue[id] = value;
}

void Memory::deleteEntry(std::string type)
{
    int id = getIdByType(type);
    if (id == -1) {
        return;
    }
    storageValue[id] = error;
    storageType[id] = "";
}

int Memory::getIdByType(std::string type)
{
    int id = -1;
    for (int i = 0; i < storageSize; i++) {
        if (storageType[i] == type) {
            id = i;
            break;
        }
    }
    return id;
}
