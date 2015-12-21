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

#include <LeafClusterAppl.h>
#include <FindModule.h>

Define_Module(LeafClusterAppl);

LeafClusterAppl::LeafClusterAppl() {

}

LeafClusterAppl::~LeafClusterAppl() {
}

void LeafClusterAppl::initialize(int stage) {
    if (stage == 1) {
        battery = FindModule<SimpleBattery*>::findSubModule(findHost());
        processor = FindModule<Processor*>::findSubModule(findHost());
        memory = FindModule<Memory*>::findSubModule(findHost());

        hasTemperatureSensor = processor->hasTemperatureSensor;
        hasHumiditySensor = processor->hasHumiditySensor;
        hasPressureSensor = processor->hasPressureSensor;
        hasLightSensor = processor->hasLightSensor;

//        double volt = battery->getVoltage();
//        double rel = battery->estimateResidualRelative();
//        double abs = battery->estimateResidualAbs();

        //todo get my sensor types
    }
}

void LeafClusterAppl::handleMessage(cMessage* msg) {
    if (msg) {
        //double rel = battery->estimateResidualRelative();
        //processor->startSensingUnit()
    } else {
        CustomMatrixApplication::handleMessage(msg);
    }
}
