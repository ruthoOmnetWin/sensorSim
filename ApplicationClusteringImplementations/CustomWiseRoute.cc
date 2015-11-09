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

#include <CustomWiseRoute.h>

#include <limits>
#include <algorithm>
#include <cassert>

#include "NetwControlInfo.h"
#include "MacToNetwControlInfo.h"
#include "ArpInterface.h"
#include "FindModule.h"
#include "WiseRoutePkt_m.h"
#include "SimTracer.h"

using std::make_pair;

Define_Module(CustomWiseRoute);

CustomWiseRoute::~CustomWiseRoute() {
    // TODO Auto-generated destructor stub
}

CustomWiseRoute::CustomWiseRoute() {
    // TODO Auto-generated constructor stub

}

