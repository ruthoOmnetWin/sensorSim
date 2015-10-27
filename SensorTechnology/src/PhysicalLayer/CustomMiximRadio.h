#ifndef CUSTOMMIXIMRADIO_H_
#define CUSTOMMIXIMRADIO_H_

#include <PhyUtils.h>
#include <omnetpp.h>
#include "MiXiMDefs.h"

class MIXIM_API CustomMiximRadio : public MiximRadio {
public:
    /**
    * @brief The state of the radio of the nic.
    */
    enum RadioState {
        /** @brief receiving state*/
        RX = 0,
        /** @brief transmitting state*/
        TX,
        /** @brief sleeping*/
        SLEEP,
        /** @brief switching between two states*/
        SWITCHING,

        //WAKEUP,
        POWERDOWN,
        //OFF1,

        /**
         * @brief No real radio state just a counter constant for the amount of states.
         *
         * Sub-classing Radios which want to add more states can add their own
         * states in their own enum beginning at the value of NUM_RADIO_STATES.
         * They should also remember to update the "numRadioStates" member accordingly.
         *
         * @see RadioUWBIR for an example.
         */
        NUM_RADIO_STATES,

    };

    Argument::mapped_type_cref mapStateToAtt(int state)
    {
        if ((state == RX) || (state == SLEEP)) {
            return minAtt;
        }
        else {
            return maxAtt;
        }
    }

    static CustomMiximRadio* createNewRadio(bool recordStats = false,
                                         int initialState = RX,
                                         Argument::mapped_type_cref minAtt = Argument::MappedOne,
                                         Argument::mapped_type_cref maxAtt = Argument::MappedZero,
                                         int currentChannel=0, int nbChannels=1)
    {
        return new CustomMiximRadio(NUM_RADIO_STATES,
                                 recordStats,
                                 initialState,
                                 minAtt, maxAtt,
                                 currentChannel, nbChannels);
    }

    CustomMiximRadio(int numRadioStates,
                 bool recordStats,
                 int initialState,
                 Argument::mapped_type_cref minAtt, Argument::mapped_type_cref maxAtt,
                 int currentChannel, int nbChannels) : MiximRadio(
                         numRadioStates,
                         recordStats,
                         initialState,
                         minAtt, maxAtt,
                         currentChannel, nbChannels
                     ) {
        int i;
        i = 0;
    };
};

//Register_Class(CustomMiximRadio);

#endif /*CUSTOMMIXIMRADIO_H_*/
