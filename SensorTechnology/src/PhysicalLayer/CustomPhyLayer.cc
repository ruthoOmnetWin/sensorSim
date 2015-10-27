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

#include <PhysicalLayer/CustomPhyLayer.h>
#include <CustomMiximRadio.h>

MiximRadio* CustomPhyLayer::initializeRadio() const {
    int    initialRadioState   = par("initialRadioState").longValue();
    double radioMinAtt         = par("radioMinAtt").doubleValue();
    double radioMaxAtt         = par("radioMaxAtt").doubleValue();
    int    nbRadioChannels     = readPar("nbRadioChannels",     1);
    int    initialRadioChannel = readPar("initialRadioChannel", 0);

    CustomMiximRadio* radio = CustomMiximRadio::createNewRadio(recordStats, initialRadioState,
                                         radioMinAtt, radioMaxAtt,
                                         initialRadioChannel, nbRadioChannels);

    //  - switch times to TX
    //if no RX to TX defined asume same time as sleep to TX
    radio->setSwitchTime(CustomMiximRadio::RX, CustomMiximRadio::TX, (hasPar("timeRXToTX") ? par("timeRXToTX") : par("timeSleepToTX")).doubleValue());
    //if no sleep to TX defined asume same time as RX to TX
    radio->setSwitchTime(CustomMiximRadio::SLEEP, CustomMiximRadio::TX, (hasPar("timeSleepToTX") ? par("timeSleepToTX") : par("timeRXToTX")).doubleValue());

    //  - switch times to RX
    //if no TX to RX defined asume same time as sleep to RX
    radio->setSwitchTime(CustomMiximRadio::TX, CustomMiximRadio::RX, (hasPar("timeTXToRX") ? par("timeTXToRX") : par("timeSleepToRX")).doubleValue());
    //if no sleep to RX defined asume same time as TX to RX
    radio->setSwitchTime(CustomMiximRadio::SLEEP, CustomMiximRadio::RX, (hasPar("timeSleepToRX") ? par("timeSleepToRX") : par("timeTXToRX")).doubleValue());

    //  - switch times to sleep
    //if no TX to sleep defined asume same time as RX to sleep
    radio->setSwitchTime(CustomMiximRadio::TX, CustomMiximRadio::SLEEP, (hasPar("timeTXToSleep") ? par("timeTXToSleep") : par("timeRXToSleep")).doubleValue());
    //if no RX to sleep defined asume same time as TX to sleep
    radio->setSwitchTime(CustomMiximRadio::RX, CustomMiximRadio::SLEEP, (hasPar("timeRXToSleep") ? par("timeRXToSleep") : par("timeTXToSleep")).doubleValue());

    return radio;
}
