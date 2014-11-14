/*
 * SimpleSensorType.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: rutho
 */

#include <SimpleSensorType/SimpleSensorType.h>

SimpleSensorType::SimpleSensorType() {
    // TODO Auto-generated constructor stub

}

SimpleSensorType::~SimpleSensorType() {
    // TODO Auto-generated destructor stub
}

SimpleSensorType::SimpleSensorType(const char *name, SensorType* sensorType, bool namepooling) : cNamedObject(name, namepooling)
{
    this->sensorType = sensorType;
}
