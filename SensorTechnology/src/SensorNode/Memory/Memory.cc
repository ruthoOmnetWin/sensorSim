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
    storageDataSets = 0;
    //empty = emptyStorage;
}

Memory::~Memory() {
    delete[] measureDataStorage;
    measureDataStorage = NULL;
}

void Memory::initialize(int stage)
{
    BatteryAccess::initialize(stage);

    storageSize = par("storageSize");

    const storage emptyStorage = {"", error, emptyTime};
    measureDataStorage = new storage[storageSize];
    for (int i = 0; i < storageSize; i++) {
        measureDataStorage[i] = empty;
    }
}

void Memory::handleMessage(cMessage *msg)
{
    say("<Memory>");
    const char* name = msg->getName();
    std::string nameString = name;
    if (nameString == "readAllAndClear") {

        say("Clearing Storage");
        say("storage before clearing:");
        printStorage();
        cMessage* returnMessage = new cMessage("storageContent");
        int count = storageDataSets;
        storage* returnData = readAllAndClear();
        for (int i = 0; i < count; i++) {
            SimpleSensorData* data = new SimpleSensorData(
                    returnData[i].type.c_str(),
                    returnData[i].value,
                    returnData[i].timeCreated
                    );
            returnMessage->getParList().add(data);
        }
        send(returnMessage, "connectToProcessor$o");

        say("Cleaning done");
        say("storage after clearing:");
        printStorage();

    } else {

        SimpleSensorData* data = (SimpleSensorData*) msg->getParList().remove(name);
        int value = data->sensorData;

        std::stringstream ss; ss << "Memory: Got type: " << name << " with value:" << value << endl;
        say(ss.str());
        if (readEntry(nameString).value == error) {
            createEntry(nameString, value);
            say("New storage entry created.");
        } else if (storageDataSets < storageSize) {
            createEntry(nameString, value);
            say("New storage entry created.");
        } else {
            updateEntry(nameString, value);
            say("Storage entry updated.");
        }
        printStorage();
    }
    delete(msg);
    draw();
    say("</Memory>");
}

/**
 * this function returns the entire data stored inside
 * the memory and formats it afterwards
 */
storage* Memory::readAllAndClear()
{
    storage *returnDataSet = new storage[storageDataSets];
    int counter = 0;
    int pos = 0;
    for (int i = 0; (i < storageSize && storageDataSets > 0); i++) {
        if (measureDataStorage[i].value != error) {
            returnDataSet[counter] = measureDataStorage[i];
            counter++;
            deleteEntry(i);
        }
    }
    return returnDataSet;
}

/**
 * CRUD:
 * create function
 */
void Memory::createEntry(std::string type, int value)
{
    int emptyId = -1;
    for (int i = 0; i < storageSize; i++) {
        if (measureDataStorage[i].type == "") {
            emptyId = i;
            break;
        }
    }
    if (emptyId == -1) {
        return;
    }
    measureDataStorage[emptyId].type = type;
    measureDataStorage[emptyId].value = value;
    measureDataStorage[emptyId].timeCreated = simTime();

    storageDataSets++;
}

/**
 * CRUD:
 * read by name function
 */
storage Memory::readEntry(std::string type)
{
    int id = getIdByType(type);
    if (id == -1) {
        return empty;
    }
    return measureDataStorage[id];
}

/**
 * CRUD:
 * read by id function
 */
storage Memory::readEntry(int id)
{
    return measureDataStorage[id];
}

/**
 * CRUD:
 * update function
 */
void Memory::updateEntry(std::string type, int value)
{
    int id = getIdByType(type);
    if (id == -1) {
        return createEntry(type, value);
    }
    measureDataStorage[id].value = value;
    measureDataStorage[id].timeCreated = simTime();
}

/**
 * CRUD:
 * delete by name function
 */
void Memory::deleteEntry(std::string type)
{
    int id = getIdByType(type);
    if (id < storageSize && id >= 0) {
        measureDataStorage[id] = {"", error, emptyTime};
        storageDataSets--;
    }
}

/**
 * CRUD:
 * delete by id function
 */
void Memory::deleteEntry(int id)
{
    if (id < storageSize && id >= 0) {
        measureDataStorage[id] = {"", error, emptyTime};
        storageDataSets--;
    }
}

/**
 * convert type to id function
 */
int Memory::getIdByType(std::string type)
{
    int id = -1;
    for (int i = 0; i < storageSize; i++) {
        if (measureDataStorage[i].type == type) {
            id = i;
            break;
        }
    }
    return id;
}

/**
 * output the storages content
 */
void Memory::printStorage()
{
    for (int i = 0; i < storageSize; i++)
    {
        std::stringstream ss; ss << i << ": " << measureDataStorage[i].type
                << ", " << measureDataStorage[i].value
                << ", " << measureDataStorage[i].timeCreated.str();
        say(ss.str().c_str());
    }
}

int Memory::getDataSizeCount() {
    return storageDataSets;
}
