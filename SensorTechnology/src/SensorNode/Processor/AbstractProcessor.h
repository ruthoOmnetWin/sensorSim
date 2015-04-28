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
#include "AbstractBatteryAccess.h"

#define sensing 0
#define shiftProcessorMode 1
#define collectStatistics 2

class AbstractProcessor : public AbstractBatteryAccess {
protected:
    int sensingIntervall;
    int shiftProcessorModeIntervall;
    int collectStatisticsIntervall;
    cMessage* selfMessageMeasure;
    cMessage* selfMessageShiftMode;
    cMessage* selfMessageStatistics;

    //consumption for the different modes
    double currentOverTimeNormal;
    double energiePerOperationNormal;

    double currentOverTimePowerSaving;
    double energiePerOperationPowerSaving;

    double currentOverTimeHighPerformance;
    double energiePerOperationHighPerformance;

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

public:
    bool hasTemperatureSensor;
    bool hasHumiditySensor;
    bool hasPressureSensor;
    bool hasLightSensor;

public:
    AbstractProcessor();
    virtual ~AbstractProcessor();
    void initialize(int stage);
    void handleMessage(cMessage *msg);
    void finish();
    void schedulePeriodicSelfMessage(int);
    void schedulePeriodicSelfMessage(cMessage*, int);
    void startSensingUnit();
    void draw();
    void doCollectStatistics();
    virtual void handleHostState(const HostState& state);

    void switchProcessorMode(MODES mode);
    void switchProcessorMode(int mode);
    void switchProcessorMode();
    MODES getProcessorMode();
};

Define_Module(AbstractProcessor);

#endif /* ABSTRACTPROCESSOR_H_ */
