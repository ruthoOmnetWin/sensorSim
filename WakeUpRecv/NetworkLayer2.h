/***************************************************************************
 * file:        NetworkLayer2.h
 *
 * author:      Jerome Rousselot
 *
 * copyright:   (C) 2009 CSEM SA, Neuchatel, Switzerland.
 *
 * description: Placeholder module that simply "translates" netwControlInfo to macControlInfo
 *
 **************************************************************************/

#ifndef NETWORKLAYER2_H
#define NETWORKLAYER2_H

#define MIXIM_INET

#include <omnetpp.h>

#include "MiXiMDefs.h"
#include "BaseNetwLayer.h"

class NetwPkt;
/**
 * @brief Placeholder module that simply "translates" netwControlInfo to macControlInfo
 *
 * @ingroup netwLayer
 * @author Jerome Rousselot
 **/

class NetworkLayer2 : public BaseNetwLayer
{
public:
	NetworkLayer2()
		: BaseNetwLayer()
		, stats(false)
		, trace(false)
		, networkID(-1)
        , ip(-1)
	{}

    /** @brief Initialization of the module and some variables*/
    virtual void initialize(int);
    virtual void finish();

protected:

    bool stats, trace;

    int networkID;  // the network to which we belong
    int ip;  // the network to which we belong

    /** @brief Handle messages from upper layer */
    virtual void handleUpperMsg(cMessage* msg);

    /** @brief Handle messages from lower layer */
    virtual void handleLowerMsg(cMessage* msg);

    /** @brief Handle self messages */
    virtual void handleSelfMsg(cMessage* /*msg*/) { };

    /** @brief Handle control messages from lower layer */
    virtual void handleLowerControl(cMessage* msg);

    virtual void handleUpperControl(cMessage* msg);

    virtual netwpkt_ptr_t encapsMsg(cPacket *appPkt);

    /** @brief Decapsulate a message */
    virtual cPacket* decapsMsg(netwpkt_ptr_t msg);

};

#endif
