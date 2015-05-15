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

#include <BatteryAccess.h>
#include <SimpleBattery.h>

BatteryAccess::BatteryAccess() {
    currentOverTime = 0.0;
    energiePerOperation = 0.0;
}

BatteryAccess::~BatteryAccess() {
    currentOverTime = 0.0;
    energiePerOperation = 0.0;
}

void BatteryAccess::initialize(int stage) {
    MiximBatteryAccess::initialize(stage);
    if (stage == 0) {
        const char * name = this->getFullName();
        std::string stringName = std::string(name);
        registerWithBattery(stringName, 1);
        EV << "Registered with Battery" << endl;
        currentOverTime = par("currentConsumption").doubleValue();
        energiePerOperation = par("energyConsumption").doubleValue();
        drawCurrent(currentOverTime, 0);
        //HostState::States state = battery->getState();
    } else {
        consumption.setName("Energy Consumptions");
        consumption.record(energiePerOperation);
        overTime.setName("Current use over time");
        overTime.record(currentOverTime);
    }
}

void BatteryAccess::handleHostState(const HostState &state)
{
    HostState::States hostState = state.get();

    if (hostState == HostState::FAILED) {
        EV << "failed" << endl;
    } else if (hostState == HostState::BROKEN) {
        EV << "broken" << endl;
    } else if (hostState == HostState::SLEEP) {
        EV << "sleep" << endl;
    } else if (hostState == HostState::OFF) {
        EV << "off" << endl;
    }
}

SensorNode* BatteryAccess::getSensorNode()
{
    std::string fullname = getParentModule()->getFullName();
    if (
        fullname == "TemperatureSensor" ||
        fullname == "HumiditySensor" ||
        fullname == "PressureSensor" ||
        fullname == "LightSensor"
    ) {
        return (SensorNode*) getParentModule()->getParentModule();
    }
    return (SensorNode*) getParentModule();
}

void BatteryAccess::say(const char * say)
{
    getSensorNode()->say(say);
}

void BatteryAccess::say(std::string s)
{
    say(s.c_str());
}

void BatteryAccess::draw()
{
    consumption.record(energiePerOperation);
    this->drawEnergy(energiePerOperation, 0);
}

void BatteryAccess::changeDrawCurrent(double cur, int acc)
{
    overTime.record(cur);
    this->drawCurrent(cur, acc);
}

void BatteryAccess::changeEnergyConsumption(float energy)
{
    energiePerOperation = energy;
}

void BatteryAccess::finish() {
    //EV << "Battery emptied at " << batteryEmptied.str() << endl;
}
