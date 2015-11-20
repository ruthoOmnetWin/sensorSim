#ifndef WAKEUPPHYUTILS_H_
#define WAKEUPPHYUTILS_H_

#include <cassert>
#include <list>
#include <omnetpp.h>

#include "MiXiMDefs.h"
#include "AnalogueModel.h"
#include "Mapping.h"
#include "PhyUtils.h"


/**
 * @brief The class that represents the Radio as a state machine.
 *
 * The Radio creates and updates its corresponding RadioStateAnalogueModel, that
 * is a filter representing the radios attenuation to a Signal depending on the
 * RadioState over time.
 *
 * For this basic version we assume a minimal attenuation when the Radio is in
 * state RX, and a maximum attenuation otherwise.
 *
 * A state-machine-diagram for Radio, RadioStateAnalogueModel and ChannelInfo showing
 * how they work together under control of BasePhyLayer as well as some documentation
 * on how RadioStateAnalogueModel works is available in @ref phyLayer.
 *
 * @ingroup phyLayer
 */
class WakeupMiximRadio
{
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
		//WAKEUP,
		/** @brief sleep with wakeup receiver*/
		SWITCHING,
		POWERDOWN,
//		OFF1,

		/**
		 * @brief No real radio state just a counter constant for the amount of states.
		 *
		 * Sub-classing Radios which want to add more states can add their own
		 * states in their own enum beginning at the value of NUM_RADIO_STATES.
		 * They should also remember to update the "numRadioStates" member accordingly.
		 *
		 * @see RadioUWBIR for an example.
		 */
		NUM_RADIO_STATES
	};

protected:

	/** @brief Output vector for radio states.*/
	cOutVector radioStates;
	/** @brief Output vector for radio channels.*/
	cOutVector radioChannels;

	/** @brief The current state the radio is in.*/
	int state;
	/** @brief The state the radio is currently switching to.*/
	int nextState;

	/** @brief The number of radio states this Radio can be in.*/
	const int numRadioStates;
	/** @brief Array for storing switch-times between states.*/
	simtime_t** swTimes;

	/** @brief Constant to store the minimum attenuation for a Radio instance.*/
	const Argument::mapped_type minAtt;
	/** @brief Constant to store the maximum attenuation for a Radio instance.*/
	const Argument::mapped_type maxAtt;

	/**
	 * @brief The corresponding RadioStateAnalogueModel.
	 *
	 * Depends on the characteristics of the radio
	 */
	RadioStateAnalogueModel rsam;

	/** @brief Currently selected channel (varies between 0 and nbChannels-1).*/
	int currentChannel;

	/** @brief Number of available channels. */
	int nbChannels;

private:
	/** @brief Copy constructor is not allowed.
	 */
	WakeupMiximRadio(const WakeupMiximRadio&);
	/** @brief Assignment operator is not allowed.
	 */
	WakeupMiximRadio& operator=(const WakeupMiximRadio&);

public:

	/**
	 * @brief Creates a new instance of this class.
	 *
	 * Since Radio hasn't a public constructor this is the only
	 * way to create an instance of this class.
	 *
	 * This method assures that the radio is initialized with the
	 * correct number of radio states. Sub classing Radios should also
	 * define a factory method like this instead of an public constructor.
	 */
	static WakeupMiximRadio* createNewRadio(bool recordStats = false,
                                     int initialState = RX,
                                     Argument::mapped_type_cref minAtt = Argument::MappedOne,
                                     Argument::mapped_type_cref maxAtt = Argument::MappedZero,
                                     int currentChannel=0, int nbChannels=1)
	{
		return new WakeupMiximRadio(NUM_RADIO_STATES,
                                 recordStats,
                                 initialState,
                                 minAtt, maxAtt,
                                 currentChannel, nbChannels);
	}

	/**
	 * @brief Destructor for the Radio class
	 */
	virtual ~WakeupMiximRadio();

	/**
	 * @brief A function called by the Physical Layer to start the switching process to a new RadioState
	 *
	 * @return	-1: Error code if the Radio is currently switching
	 * 			else: switching time from the current RadioState to the new RadioState
	 *
	 *
	 * The actual simtime must be passed, to create properly RSAMEntry
	 */
	virtual simtime_t switchTo(int newState, simtime_t_cref now);

	/**
	 * @brief function called by PhyLayer in order to make an entry in the switch times matrix,
	 * i.e. set the time for switching from one state to another
	 *
	 */
	virtual void setSwitchTime(int from, int to, simtime_t_cref time);

	/**
	 * @brief Returns the state the Radio is currently in
	 */
	virtual int getCurrentState() const {
		return state;
	}

	/**
	 * @brief called by PhyLayer when duration-time for the
	 * current switching process is up
	 *
	 * Radio checks whether it is in switching state (pre-condition)
	 * and switches to the target state
	 *
	 * The actual simtime must be passed, to create properly RSAMEntry
	 */
	virtual void endSwitch(simtime_t_cref now);

	/**
	 * @brief Returns a pointer to the RadioStateAnalogueModel
	 *
	 * This method is intended to be used by the PhyLayer to obtain a pointer
	 * to the corresponding RSAM to this Radio
	 */
	virtual RadioStateAnalogueModel* getAnalogueModel() {
		return (&rsam);
	}

	/**
	 * @brief discards information in the RadioStateAnalogueModel before given time-point
	 *
	 */
	virtual void cleanAnalogueModelUntil(simtime_t_cref t) {
		rsam.cleanUpUntil(t);
	}

	/**
	 * @brief sets tracking mode
	 */
	void setTrackingModeTo(bool b) {
		rsam.setTrackingModeTo(b);
	}

	/**
	 * @brief Changes the current channel of the radio.
	 *
	 * @param newChannel The new channel to switch to, between 0 and
	 * 					 nbChannels-1
	 */
	void setCurrentChannel(int newChannel) {
		assert(newChannel > -1);
		assert(newChannel < nbChannels);
		currentChannel = newChannel;
		radioChannels.record(currentChannel);
	}

	/**
	 * @brief Returns the channel the radio is currently set to.
	 * @return The current channel of the radio, between 0 and nbChannels-1.
	 */
	int getCurrentChannel() const {
		return currentChannel;
	}

	/**
	 * @brief Returns the number of channels.
	 * @return The number of channels.
	 */
	int getNbChannels() const {
		return nbChannels;
	}

protected:
	/**
	 * @brief Intern constructor to initialize the radio.
	 *
	 * By defining no default constructor we assure that sub classing radios
	 * have to explicitly call this constructor which assures they pass
	 * the correct number of radio states.
	 *
	 * The protected constructor + factory method solution assures that
	 * while sub-classing Radios HAVE to explicitly pass their correct amount
	 * of radio states to this constructor, the user (creator) of the Radio
	 * doesn't has to pass it or even know about it (which wouldn't be possible
	 * with a public constructor).
	 * Therefore sub classing Radios which could be sub-classed further should
	 * also do it this way.
	 */
	WakeupMiximRadio(int numRadioStates,
		  bool recordStats,
		  int initialState = RX,
		  Argument::mapped_type_cref minAtt = Argument::MappedOne, Argument::mapped_type_cref maxAtt = Argument::MappedZero,
		  int currentChannel = 0, int nbChannels = 1);

	/**
	 * @brief responsible for making entries to the RSAM
	 */
	virtual void makeRSAMEntry(simtime_t_cref time, int state)
	{
		rsam.writeRecvEntry(time, mapStateToAtt(state));
	}

	/**
	 * @brief maps RadioState to attenuation, the Radios receiving characteristic
	 *
	 */
	virtual Argument::mapped_type_cref mapStateToAtt(int state)
	{
		if ((state == RX) || (state == SLEEP)) {
			return minAtt;
		}
		else {
			return maxAtt;
		}
	}
};
// end class MiximRadio

#endif /*WAKEUPPHYUTILS_H_*/
