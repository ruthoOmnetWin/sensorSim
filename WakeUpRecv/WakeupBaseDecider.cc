/*
 * BaseDecider.cc
 *
 *  Created on: 24.02.2009
 *      Author: karl
 */

#include "WakeupBaseDecider.h"
#include "WakeUpPacket_m.h"

#include <cassert>

#include "MiXiMAirFrame.h"
#include "PhyToMacControlInfo.h"
#include "FWMath.h"

// This function was changed for receiving packets in sleep mode.
// limir@tuc

simtime_t WakeupBaseDecider::processSignalEnd(airframe_ptr_t frame) {
    if (frame != currentSignal.first)
        return notAgain; // it is not the frame which we are processing

	DeciderResult* pResult = createResult(frame);

    if (!phy->isRadioInRX())
    {

        if (pResult != NULL && pResult->isSignalCorrect() && !frame->hasBitError())
        {
//            int s = frame->getByteLength();
//            airframe_ptr_t frame_cpy= new AirFrame();
//            memcpy(&frame_cpy,frame,sieof(airframe_ptr_t));
            airframe_ptr_t pAfDup = frame->dup();
            cPacket* pMacPacket = pAfDup->decapsulate();
            if (pMacPacket!=0)
            {
                cPacket* pDummyPacket = pMacPacket->decapsulate();
                if (pDummyPacket!=0)
                {
                    cPacket* pWakeup = pDummyPacket->decapsulate();

                    //->decapsulate()->decapsulate();
                    //cPacket* pMacPacket = frame->decapsulate();
                    WakeUpPacket* pkt = dynamic_cast<WakeUpPacket*>(pWakeup);
                    if (pkt == 0)
                    {
                        cPacket* pMacPacket = frame->decapsulate();
                        pMacPacket->setName("PHY-ERROR");
                        pMacPacket->setKind(PACKET_DROPPED);
                        phy->sendControlMsgToMac(pMacPacket);
                    }
                    else
                    {
                        phy->sendUp(frame, pResult);
                    }
                }
            }
        }

    }

	else if (pResult != NULL && pResult->isSignalCorrect() && !frame->hasBitError()) {
        deciderEV << "AirFrame was received correctly, it is now handed to upper layer..." << endl;
        // go on with processing this AirFrame, send it to the Mac-Layer
        if (currentSignal.getInterferenceCnt() > 0) {
            ++nbFramesWithInterference;
        }
        else {
            ++nbFramesWithoutInterference;
        }
        phy->sendUp(frame, pResult);
    }
	else {
        deciderEV << "AirFrame was not received correctly, sending it as control message to upper layer" << endl;
        cPacket* pMacPacket = frame->decapsulate();
        if (currentSignal.getInterferenceCnt() > 0) {
            ++nbFramesWithInterferenceDropped;
        }
        else {
            ++nbFramesWithoutInterferenceDropped;
        }
        if (pMacPacket) {
            pMacPacket->setName("ERROR");
            pMacPacket->setKind(PACKET_DROPPED);
            if (pResult) {
                PhyToMacControlInfo::setControlInfo(pMacPacket, pResult);
            }
            phy->sendControlMsgToMac(pMacPacket);
        }
    }
    currentSignal.finishProcessing();

	return getNextSignalHandleTime(frame);
}
