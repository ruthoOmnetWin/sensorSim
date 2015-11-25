#ifndef MY_TEST_APPLICATION_H
#define MY_TEST_APPLICATION_H

#include <vector>
#include <omnetpp.h>

#include "MiXiMDefs.h"
#include "BaseModule.h"
#include "SimpleAddress.h"
#include <SimpleBattery.h>
#include <WakeupPhyLayerBattery.h>

#define MIXIM_INET

class MIXIM_API MyTestApplication : public BaseModule {
private:
	/** @brief Copy constructor is not allowed.
	 */
    MyTestApplication(const MyTestApplication&);
	/** @brief Assignment operator is not allowed.
	 */
    MyTestApplication& operator=(const MyTestApplication&);


public:
    MyTestApplication()
		: BaseModule()
		, dataOut(-1)
		, dataIn(-1)
		, ctrlOut(-1)
		, ctrlIn(-1)
	{}

	virtual ~MyTestApplication();

	virtual void initialize(int stage);
	virtual void handleMessage(cMessage* msg);
    virtual void finish();
    virtual void sendPacket(void);
    protected:

        // gates
    	int dataOut;
    	int dataIn;
        int ctrlOut;
        int ctrlIn;

        // timers
        cMessage* delayTimer;

        SimpleBattery* mySimpleBattery;
        int mySimpleBatteryId;  //id for additional load of energy (sensor application)
        WakeupPhyLayerBattery* myPhyLayerBattery;
        int myNodeId;
        unsigned int sleepState = 0;

        // module parameters
//        int nbPackets;
//        int remainingPackets;
        int headerLength;
        LAddress::L3Type nodeAddr;


        //double trafficParam;
        bool debug, stats, trace;
//        bool flood;
//        bool isTransmitting;

        // constants
        int INITIAL_DELAY;
        int PAYLOAD_SIZE;

        // state variables
//        int nbPacketsReceived;
//        std::vector < cStdDev > latencies;
//        cOutVector latenciesRaw;
//        cStdDev testStat;
};

#endif // MY_TEST_APPLICATION_H

