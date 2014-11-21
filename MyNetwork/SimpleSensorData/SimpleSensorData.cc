/*
 * SimpleSensorData.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: rutho
 */

#include <SimpleSensorData/SimpleSensorData.h>

SimpleSensorData::SimpleSensorData() {
    sensorData = 0;
}

SimpleSensorData::~SimpleSensorData()
{
}


SimpleSensorData::SimpleSensorData(const char *name, int sensorData, bool namepooling) : cNamedObject(name, namepooling)
{
    this->sensorData = sensorData;
}

