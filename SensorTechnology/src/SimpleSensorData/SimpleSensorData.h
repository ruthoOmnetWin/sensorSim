/*
 * SimpleSensorData.h
 *
 *  Created on: Nov 13, 2014
 *      Author: rutho
 */

#ifndef SIMPLESENSORDATA_H_
#define SIMPLESENSORDATA_H_

#include <omnetpp.h>

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
