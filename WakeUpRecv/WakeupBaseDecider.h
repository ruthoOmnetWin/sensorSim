/*
 * BaseDecider.h
 *
 *  Created on: 24.02.2009
 *      Author: karl
 */

#ifndef WAKEUPBASEDECIDER_H_
#define WAKEUPBASEDECIDER_H_

#include "MiXiMDefs.h"
#include "Decider.h"
#include "Decider802154Narrow.h"

class WakeupBaseDecider: public Decider802154Narrow {

protected:

	virtual simtime_t processSignalEnd(airframe_ptr_t frame);

public:

	WakeupBaseDecider( DeciderToPhyInterface* phy
	                       , double                 sensitivity
	                       , int                    myIndex
	                       , bool                   debug )
	        : Decider802154Narrow(phy, sensitivity, myIndex, debug)
	    {
	        //snirDropped.setName("snirDropped");
	        //snirReceived.setName("snirReceived");
	        //berlog.setName("berlog");
	        //snrlog.setName("snrlog");
	    }

};

#endif /* WAKEUPBASEDECIDER_H_ */
