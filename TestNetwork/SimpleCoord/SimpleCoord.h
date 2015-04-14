/*
 * SimpleCoord.h
 *
 *  Created on: Jul 30, 2014
 *      Author: rutho
 */

#ifndef SIMPLECOORD_H_
#define SIMPLECOORD_H_

#include <omnetpp.h>
#include <Coord.h>

class SimpleCoord : public cNamedObject
{
public:
    //virtual const char *getName() const  {return "position";}
    virtual SimpleCoord *dup() const {return new SimpleCoord(*this);}
public:
    double x;
    double y;
    double z;
    SimpleCoord();
    virtual ~SimpleCoord();
    explicit SimpleCoord(const char *name, Coord *coord, bool namepooling=true);
};

#endif /* SIMPLECOORD_H_ */
