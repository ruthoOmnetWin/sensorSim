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

#ifndef ABSTRACTPROCESSOR_H_
#define ABSTRACTPROCESSOR_H_

#include <omnetpp.h>
#include <string.h>
#include "BatteryAccess.h"
#include <vector>

#define sensing 0
#define shiftProcessorMode 1
#define collectStatistics 2
#define readAndClearStorage 3

/**
 * the biggest module inside the sensor node with the most functionality
 *
 * the processor can define different parameters like some time intervalls
 * for sensing, shifting its power mode and collecting statistics about the battery
 *
 * it has different power modes to improve the lifetime of the battery and save
 * power at some times
 *
 * it also stores what types of sensors on the node exist
 *
 * the processor is used to control the sensor module, which means it can start
 * it and then get the data and store it inside the memory until it is needed
 */
class Processor : public BatteryAccess {
protected:
    void updateDisplay();

    int sensingIntervall;
    int shiftProcessorModeNormalIntervall;
    int shiftProcessorModeHighPerformanceIntervall;
    int shiftProcessorModePowerSavingIntervall;
    int collectStatisticsIntervall;
    int readAndClearStorageIntervall;
    cMessage* selfMessageMeasure;
    cMessage* selfMessageShiftMode;
    cMessage* selfMessageStatistics;
    cMessage* selfMessageReadAndClear;

    //consumption for the different modes
    double currentOverTimeNormal;
    double energiePerOperationNormal;
    double peripheryNormalRatio;

    double currentOverTimePowerSaving;
    double energiePerOperationPowerSaving;
    double peripheryPowerSavingRatio;

    double currentOverTimeHighPerformance;
    double energiePerOperationHighPerformance;
    double peripheryHighPerformanceRatio;

    int numDevices;
    std::vector<cModule*> periphery;
    void setPeriphery();
    void addSensorModules(cModule*);
    void switchPeripheryEnergyConsumption();

    enum MODES {
        NORMAL = 0,
        POWER_SAVING = 1,
        HIGH_PERFORMANCE = 2,
        OFF
    };

    int activatedMode;

protected:
    //statistics
    double voltage;
    double residualRelative;
    double residualAbs;
    cLongHistogram voltageStats;
    cOutVector voltageVector;
    cLongHistogram residualRelativeStats;
    cOutVector residualRelativeVector;
    cLongHistogram residualAbsStats;
    cOutVector residualAbsVector;
    cOutVector activatedModeVector;
    cOutVector sensorUnitsActive;

public:
    bool hasTemperatureSensor;
    bool hasHumiditySensor;
    bool hasPressureSensor;
    bool hasLightSensor;

public:
    Processor();
    virtual ~Processor();
    void initialize(int stage);
    void handleMessage(cMessage *msg);
    void finish();
    void schedulePeriodicSelfMessage(int);
    void schedulePeriodicSelfMessage(cMessage*, int);
    void startSensingUnit(int type);
    void draw();
    void doCollectStatistics();
    virtual void handleHostState(const HostState& state);

    void switchProcessorMode(MODES mode);
    void switchProcessorMode(int mode);
    void switchProcessorMode();
    MODES getProcessorMode();
};

Define_Module(Processor);

#endif /* ABSTRACTPROCESSOR_H_ */
