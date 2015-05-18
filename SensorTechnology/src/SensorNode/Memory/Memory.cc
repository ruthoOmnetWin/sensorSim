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
#define emptyTime -1

Memory::Memory() : empty({"", error, emptyTime}) {
    const storage emptyStorage = {"", error, emptyTime};
    //empty = emptyStorage;
}

Memory::~Memory() {
    delete[] keyValueStore;
    keyValueStore = NULL;
}

void Memory::initialize(int stage)
{
    BatteryAccess::initialize(stage);

    storageSize = par("storageSize");

    const storage emptyStorage = {"", error, emptyTime};
    keyValueStore = new storage[storageSize];
    for (int i = 0; i < storageSize; i++) {
        keyValueStore[i] = empty;
    }
}

void Memory::handleMessage(cMessage *msg)
{
    const char* name = msg->getName();
    SimpleSensorData* data = (SimpleSensorData*) msg->getParList().remove(name);
    int value = data->sensorData;
    std::string nameString = name;

    std::stringstream ss; ss << "Got type: " << name << " with value:" << value << endl;
    say(ss.str());

    if (readEntry(nameString) == error) {
        createEntry(nameString, value);
        EV << "New storage entry created." << endl;
    } else if (storageDataSets < storageSize) {
        createEntry(nameString, value);
        EV << "New storage entry created." << endl;
    } else {
        updateEntry(nameString, value);
        EV << "Storage entry updated." << endl;
    }

    printStorage();

    delete(msg);
    draw();
}

void Memory::createEntry(std::string type, int value)
{
    int emptyId = -1;
    for (int i = 0; i < storageSize; i++) {
        if (keyValueStore[i].type == "") {
            emptyId = i;
            break;
        }
    }
    if (emptyId == -1) {
        return;
    }
    keyValueStore[emptyId].type = type;
    keyValueStore[emptyId].value = value;
    keyValueStore[emptyId].timeCreated = simTime();

    storageDataSets++;
}

int Memory::readEntry(std::string type)
{
    int id = getIdByType(type);
    if (id == -1) {
        return error;
    }
    return keyValueStore[id].value;
}

void Memory::updateEntry(std::string type, int value)
{
    int id = getIdByType(type);
    if (id == -1) {
        return createEntry(type, value);
    }
    keyValueStore[id].value = value;
    keyValueStore[id].timeCreated = simTime();
}

void Memory::deleteEntry(std::string type)
{
    int id = getIdByType(type);
    if (id == -1) {
        return;
    }
    keyValueStore[id] = {"", error, emptyTime};

    storageDataSets--;
}

int Memory::getIdByType(std::string type)
{
    int id = -1;
    for (int i = 0; i < storageSize; i++) {
        if (keyValueStore[i].type == type) {
            id = i;
            break;
        }
    }
    return id;
}

void Memory::printStorage()
{
    for (int i = 0; i < storageSize; i++)
    {
        EV << i << ": " << keyValueStore[i].type
                << ", " << keyValueStore[i].value
                << ", " << keyValueStore[i].timeCreated.str()
                << endl;
    }
}
