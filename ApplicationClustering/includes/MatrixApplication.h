#ifndef MATRIX_APPLICATION_H
#define MATRIX_APPLICATION_H

#include <vector>
#include <omnetpp.h>

#include "MiXiMDefs.h"
#include "BaseModule.h"
#include "SimpleAddress.h"
#include "ce-packetstructs.h"

#include "ce-clusterApplication.h"

#define MIXIM_INET







class MIXIM_API MatrixApplication : public BaseModule {
private:
	/** @brief Copy constructor is not allowed.
	 */
    MatrixApplication(const MatrixApplication&);
	/** @brief Assignment operator is not allowed.
	 */
    MatrixApplication& operator=(const MatrixApplication&);


public:
    MatrixApplication()
		: BaseModule()
		, dataOut(-1)
		, dataIn(-1)
		, ctrlOut(-1)
		, ctrlIn(-1)
		, nodeAddr()
	{}

	virtual ~MatrixApplication();

	virtual void initialize(int stage);
	virtual void matrixEvent(void);
	virtual void handleMessage(cMessage* msg);
    virtual void finish();
    virtual void matrixApplicationMain(void);
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
        //int nbPackets;
        //int remainingPackets;
        int headerLength;
        LAddress::L3Type nodeAddr;
        //LAddress::L3Type dstAddr;
        LAddress::L3Type coordinatorNodeAddr;
        //double trafficParam;
        bool debug, stats, trace;
        //bool flood;
        //bool isTransmitting;

        // constants
        int INITIAL_DELAY;
        int PAYLOAD_SIZE;

        // state variables
        //int nbPacketsReceived;
        //std::vector < cStdDev > latencies;
        //cOutVector latenciesRaw;
        //cStdDev testStat;

};

#endif // TEST_APPLICATION_H

