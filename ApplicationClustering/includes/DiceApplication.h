#ifndef DICE_APPLICATION_H
#define DICE_APPLICATION_H

#include <vector>
#include <omnetpp.h>

#include "MiXiMDefs.h"
#include "BaseModule.h"
#include "SimpleAddress.h"
#include "ce-packetstructs.h"

#include "ce-network.h"

#define MIXIM_INET


//DiceApplication *diceApplication;




class MIXIM_API DiceApplication : public BaseModule {
private:
	/** @brief Copy constructor is not allowed.
	 */
	DiceApplication(const DiceApplication&);
	/** @brief Assignment operator is not allowed.
	 */
	DiceApplication& operator=(const DiceApplication&);


public:
		DiceApplication()
		: BaseModule()
		, dataOut(-1)
		, dataIn(-1)
		, ctrlOut(-1)
		, ctrlIn(-1)
	{}

	virtual ~DiceApplication();

	virtual void initialize(int stage);
	virtual void sendDiceEvent(void);
	virtual void handleMessage(cMessage* msg);
    virtual void finish();
    virtual void sendPacket(void);
    virtual void setPositions(void);
    protected:

        // gates
    	int dataOut;
    	int dataIn;
        int ctrlOut;
        int ctrlIn;

        // timers
        cMessage* delayTimer;
        ClusterApplication* clusterApp;

        // module parameters
//        int nbPackets;
//        int remainingPackets;
        int headerLength;
        LAddress::L3Type nodeAddr;
        unsigned char defDice = 0;
        unsigned char defPos = 0;
        unsigned int nextDice;
        LAddress::L3Type coordinatorNodeAddr;

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

#endif // TEST_APPLICATION_H

