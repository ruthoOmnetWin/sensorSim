//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef MYLINEARMOBILITY_H_
#define MYLINEARMOBILITY_H_

#include "LinearMobility.h"

class MyLinearMobility : public LinearMobility
{
protected:
    virtual void initialize(int stage);
    virtual void move();
};

//Register_Class(MyLinearMobility);
Define_Module(MyLinearMobility);

#endif /* MYLINEARMOBILITY_H_ */
