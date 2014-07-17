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

#include <CustomWorldUtility.h>

CustomWorldUtility::CustomWorldUtility()
{
    // TODO Auto-generated constructor stub

}

void CustomWorldUtility::setTemperature()
{
    this->temperatureArray = readXML("xmlTemperature");
}

int* CustomWorldUtility::readXML(char* fileName)
{
    // get the xml from the parameter, return type cXMLElement
    cXMLElement *rootE = par(fileName).xmlValue();

    // get a vector (of type cXMLElement) with all childs of the root-tag
    cXMLElementList nList = rootE->getChildren();

    int length = nList.size();

    int temperature[length];

    for (int i = 0; i < length; i++) {
        // access the data from a child
        //EV << nList[i]->getNodeValue() << endl;

        temperature[i] = atoi(nList[i]->getNodeValue());

    }

    return temperature;

}
