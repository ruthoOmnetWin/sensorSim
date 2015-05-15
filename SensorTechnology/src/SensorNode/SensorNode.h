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

#ifndef ABSTRACTSENSORNODE_H_
#define ABSTRACTSENSORNODE_H_

#include <omnetpp.h>
#include <FindModule.h>

/**
 * this module contains the generic part of the initialization of the
 * sensor node
 *
 * for every existing sensor processor gates will be created, which can only
 * be done before finalizing the object and therefore it must be generated here
 *
 * these will then be connected to to the sensor
 *
 * the connection between memory and processor is also created here but
 * the gates, defined inside the ned code are used
 */

class SensorNode : public cModule {
public:
    bool noisy;
public:
    cDatarateChannel* getControlChannel();
    cDatarateChannel* getDataChannel();
    void say(const char *);
protected:
    void initialize(int);
    void finish();
    void handleMessage(cMessage *msg);
    void setNumGates();
    void createProcessor();
    void connectProcessorAndMemory();
    void connectProcessorAndSensor(cModule&, std::string);
};

Define_Module(SensorNode);

#endif /* ABSTRACTSENSORNODE_H_ */
