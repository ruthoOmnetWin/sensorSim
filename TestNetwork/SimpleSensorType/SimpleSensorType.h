/*
 * SimpleSensorType.h
 *
 *  Created on: Nov 14, 2014
 *      Author: rutho
 */

#ifndef SIMPLESENSORTYPE_H_
#define SIMPLESENSORTYPE_H_

#include <omnetpp.h>

struct SensorType {
    bool temperature;
    bool pressure;
    bool light;
    bool humidity;
};

class SimpleSensorType : public cNamedObject
{
public:
    virtual SimpleSensorType *dup() const {return new SimpleSensorType(*this);}
public:
    SensorType* sensorType;
    SimpleSensorType();
    virtual ~SimpleSensorType();
    explicit SimpleSensorType(const char *name, SensorType *sensorType, bool namepooling=true);
};

#endif /* SIMPLESENSORTYPE_H_ */
