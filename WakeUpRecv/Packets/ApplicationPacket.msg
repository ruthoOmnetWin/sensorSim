//**************************************************************************
// * file:        ApplicationPacket.msg
// *
// * author:      Mirko Lippmann
// *
// * copyright:   (C) 2013 TUC
// *
// *              This program is free software; you can redistribute it 
// *              and/or modify it under the terms of the GNU General Public 
// *              License as published by the Free Software Foundation; either
// *              version 2 of the License, or (at your option) any later 
// *              version.
// *              For further information see file COPYING 
// *              in the top level directory
// **************************************************************************
// * part of:     
// * description: 
// **************************************************************************/

cplusplus {{
    #include "SimpleAddress.h"
}}

class LAddress::L3Type extends void;

// Basic application packet definition
//
// subclass if you want to create your own application layer packet
// class
//
// @author Daniel Willkomm
packet ApplicationPacket
{
    LAddress::L3Type destAddr = LAddress::L3BROADCAST; // destination address
    LAddress::L3Type srcAddr  = LAddress::L3BROADCAST; // source address
}
