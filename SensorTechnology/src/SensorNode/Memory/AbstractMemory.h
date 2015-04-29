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

#ifndef ABSTRACTMEMORY_H_
#define ABSTRACTMEMORY_H_

#include <omnetpp.h>
#include <string.h>
#include "AbstractBatteryAccess.h"
#include "SimpleSensorData.h"

/**
 * this is a small implementation of a memory
 *
 * it has the 4 functions of the CRUD model and a simple key-value store with the
 * size storageSize
 */
class AbstractMemory : public AbstractBatteryAccess {
protected:
    std::string* storageType;
    int* storageValue;
    const static int storageSize = 4;
public:
    AbstractMemory();
    virtual ~AbstractMemory();
    void initialize(int stage);
    void handleMessage(cMessage *msg);
    //crud - to access the storage
    void createEntry(std::string, int);
    int readEntry(std::string);
    void updateEntry(std::string, int);
    void deleteEntry(std::string);
    int getIdByType(std::string);
};

Define_Module(AbstractMemory);

#endif /* ABSTRACTMEMORY_H_ */
