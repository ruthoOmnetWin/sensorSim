/*
 * StatisticsInterface.h
 *
 *  Created on: Aug 8, 2014
 *      Author: rutho
 */

#ifndef STATISTICSINTERFACE_H_
#define STATISTICSINTERFACE_H_

#include <omnetpp.h>
#include <ExtendedMessage_m.h>

class StatisticsInterface {
protected:
    long numSent;
    long numReceived;
    cLongHistogram hopCountStats;
    cOutVector hopCountVector;
protected:
    virtual ExtendedMessage* generateMessage(const char* msgname) = 0;
    virtual void updateDisplay() = 0;
    virtual void finish() = 0;
};

#endif /* STATISTICSINTERFACE_H_ */
