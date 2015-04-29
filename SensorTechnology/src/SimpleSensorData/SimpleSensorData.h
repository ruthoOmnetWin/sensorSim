/*
 * SimpleSensorData.h
 *
 *  Created on: Nov 13, 2014
 *      Author: rutho
 */

#ifndef SIMPLESENSORDATA_H_
#define SIMPLESENSORDATA_H_

#include <omnetpp.h>

/**
 * a small class which can be used to transfer an integer value via messages
 * the parameters list inside messages need a cNamedObject and this class inherit from
 * it
 *
 * just set sensorData to the value you want to transfer and add the object to a message
 */
class SimpleSensorData : public cNamedObject
{
public:
    virtual SimpleSensorData *dup() const {return new SimpleSensorData(*this);}
public:
    int sensorData;
    SimpleSensorData();
    virtual ~SimpleSensorData();
    explicit SimpleSensorData(const char *name, int sensorData, bool namepooling=true);
};


#endif /* SIMPLESENSORDATA_H_ */
