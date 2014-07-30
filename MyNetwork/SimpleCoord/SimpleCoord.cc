/*
 * SimpleCoord.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: rutho
 */

#include <SimpleCoord/SimpleCoord.h>


SimpleCoord::SimpleCoord() {
    // TODO Auto-generated constructor stub

}

SimpleCoord::~SimpleCoord() {
    // TODO Auto-generated destructor stub
}

SimpleCoord::SimpleCoord(const char *name, Coord *coord, bool namepooling) : cNamedObject(name, namepooling)
{
    x = coord->x;
    y = coord->y;
    z = coord->z;

    //defaultowner->doInsert(this);

    // statistics
    //total_objs++;
    //live_objs++;
    /*
#ifdef DEVELOPER_DEBUG
    objectlist.insert(this);
#endif*/
}

