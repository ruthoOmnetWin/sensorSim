//
// Generated file, do not edit! Created by opp_msgc 4.5 from Packets/WakeUpPacket.msg.
//

#ifndef _WAKEUPPACKET_M_H_
#define _WAKEUPPACKET_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0405
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "SimpleAddress.h"
// }}



/**
 * Class generated from <tt>Packets/WakeUpPacket.msg</tt> by opp_msgc.
 * <pre>
 * packet WakeUpPacket
 * {
 *     LAddress::L3Type destAddr = LAddress::L3BROADCAST; 
 *     LAddress::L3Type srcAddr  = LAddress::L3BROADCAST; 
 * }
 * </pre>
 */
class WakeUpPacket : public ::cPacket
{
  protected:
    LAddress::L3Type destAddr_var;
    LAddress::L3Type srcAddr_var;

  private:
    void copy(const WakeUpPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const WakeUpPacket&);

  public:
    WakeUpPacket(const char *name=NULL, int kind=0);
    WakeUpPacket(const WakeUpPacket& other);
    virtual ~WakeUpPacket();
    WakeUpPacket& operator=(const WakeUpPacket& other);
    virtual WakeUpPacket *dup() const {return new WakeUpPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual LAddress::L3Type& getDestAddr();
    virtual const LAddress::L3Type& getDestAddr() const {return const_cast<WakeUpPacket*>(this)->getDestAddr();}
    virtual void setDestAddr(const LAddress::L3Type& destAddr);
    virtual LAddress::L3Type& getSrcAddr();
    virtual const LAddress::L3Type& getSrcAddr() const {return const_cast<WakeUpPacket*>(this)->getSrcAddr();}
    virtual void setSrcAddr(const LAddress::L3Type& srcAddr);
};

inline void doPacking(cCommBuffer *b, WakeUpPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, WakeUpPacket& obj) {obj.parsimUnpack(b);}


#endif // _WAKEUPPACKET_M_H_
