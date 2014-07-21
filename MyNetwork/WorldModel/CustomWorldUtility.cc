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
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

#define xmlPressure 1
#define xmlTemperature 2

CustomWorldUtility::CustomWorldUtility()
{
    // TODO Auto-generated constructor stub
}

CustomWorldUtility::~CustomWorldUtility()
{
    delete temperatureArray;
    delete pressureArray;
}

void CustomWorldUtility::setTemperature()
{
    int* data = readXML(xmlTemperature);
    this->temperatureArray = new int[tempLength];
    for (int i = 0; i < tempLength; i++) {
        this->temperatureArray[i] = data[i];
    }
    delete data;
}

void CustomWorldUtility::setPressure()
{
    int* data = readXML(xmlPressure);
    this->pressureArray = new int[pressLength];
    for (int i = 0; i < pressLength; i++) {
        this->pressureArray[i] = data[i];
    }
    delete data;
}

int* CustomWorldUtility::readXML(int fileName)
{
    // get the xml from the parameter, return type cXMLElement
    cXMLElement *rootE;
    if (fileName == xmlPressure) {
        rootE = par("xmlPressure").xmlValue();
    } else if (fileName == xmlTemperature) {
        rootE = par("xmlTemperature").xmlValue();
    }

    // get a vector (of type cXMLElement) with all childs of the root-tag
    cXMLElementList nList = rootE->getChildren();

    int length = nList.size();

    int* data = new int[length];
    if (fileName == xmlTemperature) {
        tempLength = length;
    } else if (fileName == xmlPressure) {
        pressLength = length;
    }

    for (int i = 0; i < length; i++) {
        // access the data from a child
        //EV << nList[i]->getNodeValue() << endl;
        data[i] = atoi(nList[i]->getNodeValue());
    }

    return data;
}

void CustomWorldUtility::initialize(int stage)
{
    EV << "Initializing World Model" << endl;

    if (par("createData")) {
        EV << "Generating New Environment Data" << endl;
        this->generateEnvironmentData();
    }

    this->setTemperature();
    this->setPressure();

}

void CustomWorldUtility::handleMessage(cMessage *msg)
{
    send(msg, "out");
}

void CustomWorldUtility::generateEnvironmentData()
{
    string filenames[2] = {"pressure", "temperature"};

    int numberOfFiles = sizeof(filenames);

    int numNodes = 100;
    if (numNodes == 0) {

        cout << "Didn't create any file" << endl;
    } else {

        cout << "Starting to create files" << endl;

        for (int files = 0; files < numberOfFiles; files++) {

            ofstream myfile;

            string filename = "data/";
            filename += filenames[files];
            filename += ".xml";
            char * filenameChar = new char[filename.length()];
            strcpy(filenameChar,filename.c_str());

            myfile.open (filenameChar);
            cout << "Creating " << filenameChar << endl;
            delete filenameChar;
            myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl << "<" << filenames[files] << ">" << endl;

            for (int i = 0; i < numNodes; i++) {
                myfile << "<pos" << i << ">" << (rand() % 100)/3 << "</pos" << i << ">" << endl;
            }

            myfile << "</" << filenames[files] << ">";
            myfile.close();

        }

        cout << "Done creating" << endl;
    }

}
