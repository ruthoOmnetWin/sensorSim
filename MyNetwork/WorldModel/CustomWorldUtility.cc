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
#include <Coord.h>
#include <SimpleCoord.h>
using namespace std;

#define xmlHumidity 0
#define xmlPressure 1
#define xmlTemperature 2
#define xmlLight 3

CustomWorldUtility::CustomWorldUtility()
{
    tempLength = 0;
    pressLength = 0;
    temperatureArray = 0;
    pressureArray = 0;
}

CustomWorldUtility::~CustomWorldUtility()
{
    delete[] temperatureArray;
    delete[] pressureArray;
}

void CustomWorldUtility::initialize(int stage)
{
    BaseWorldUtility::initialize(stage);
    ev << "Initializing World Model" << endl;

    if (par("createData")) {
        EV << "Generating New Environment Data" << endl;
        this->generateEnvironmentData();
    } else {
        bool filesExist = true;
        ifstream ifile("WorldModel/data/temperature.xml");
        if (!ifile) {
            filesExist = false;
        }
        ifile.close();
        if (filesExist) {
            ifstream ifile("WorldModel/data/pressure.xml");
            if (!ifile) {
                filesExist = false;
            }
            ifile.close();
        }
        if (filesExist) {
            ifstream ifile("WorldModel/data/humidity.xml");
            if (!ifile) {
                filesExist = false;
            }
            ifile.close();
        }
        if (filesExist) {
            ifstream ifile("WorldModel/data/light.xml");
            if (!ifile) {
                filesExist = false;
            }
            ifile.close();
        }
        if (!filesExist) {
            EV << "Generating New Environment Data due to missing files" << endl;
            this->generateEnvironmentData();
        }
    }

    //this->setTemperature();
    //this->setPressure();

    //object = new cObject();
    int amountNodes = par("numGates");
    for (int i = 0; i < amountNodes; i++) {
        //generate a message
        //simtime_t time = simTime();
        ExtendedMessage *msg = generateMessage("world init");
        send(msg, "worldDataGate$o", i);
    }
    amountNodes = par("numSensorNodes");
    for (int i = 0; i < amountNodes; i++) {
        ExtendedMessage *newmsg = generateMessage("update pos");
        send(newmsg, "toNode$o", i);
    }
}

void CustomWorldUtility::handleMessage(cMessage *msg)
{
    //Coord* par = (Coord*) msg->getParList().get(0);
    SimpleCoord *array = (SimpleCoord*) msg->getParList().remove("pos");
    //array->remove("pos");
    //double x = par->x;
    //double y = par->y;
    string name = msg->getName();
    delete msg;
    delete array;
    //msg->getParList().remove(msg->getParList().get(0));
    //delete msg;
    string requestType = name.substr(0,3);
    if (requestType == "GET") {
        int* data;
        string sensorType = name.substr(4);
        if (sensorType == "temperature") {
            data = this->temperatureArray;
        } else if (sensorType == "pressure") {
            data = this->pressureArray;
        } else if (sensorType == "humidity") {

        }
        //cMessage *newmsg  = new cMessage(SIMTIME_STR(simTime()));
        //send(newmsg , "worldDataGate$o", 1);
    }
}

void CustomWorldUtility::setTemperature()
{
    int* data = readXML(xmlTemperature);
    this->temperatureArray = new int[tempLength];
    for (int i = 0; i < tempLength; i++) {
        this->temperatureArray[i] = data[i];
    }
    delete[] data;
}

void CustomWorldUtility::setPressure()
{
    int* data = readXML(xmlPressure);
    this->pressureArray = new int[pressLength];
    for (int i = 0; i < pressLength; i++) {
        this->pressureArray[i] = data[i];
    }
    delete[] data;
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

void CustomWorldUtility::generateEnvironmentData()
{
    double playgroundSizeX = par("playgroundSizeX");
    double playgroundSizeY = par("playgroundSizeY");

    int sizeA = (int)playgroundSizeX;
    int sizeB = (int)playgroundSizeY;
    int size = sizeA * sizeB;
    string filenames[4] = {"humidity", "pressure", "temperature", "light"};

    int numberOfFiles = sizeof(filenames)/sizeof(filenames[0]);
    EV << "Starting to create files" << endl;

    for (int files = 0; files < numberOfFiles; files++) {

        ofstream myfile;

        string filename = "WorldModel/data/";
        stringstream data;
        filename += filenames[files];
        filename += ".xml";
        char * filenameChar = new char[filename.length()];
        strcpy(filenameChar,filename.c_str());

        EV << "Creating " << filenameChar << endl;

        data << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl << "<" << filenames[files] << ">" << endl;
        int* newData;

        // Data Creation here
        if (files == xmlHumidity) {
            newData = generateHumidity(size);
        } else if (files == xmlPressure) {
            newData = generatePressure(size);
        } else if (files == xmlTemperature) {
            newData = generateTemperature(size);
        } else if (files == xmlLight) {
            newData = generateLight(size);
        }

        for (int i = 0; i < sizeA; i++) {
            data << "<pos" << i << ">";
            for (int j = 0; j < sizeB; j++) {
                data << "<pos" << j << ">" << newData[((i+1)*(j+1))-1] << "</pos" << j << ">";
            }
            data << "</pos" << i << ">" << endl;
        }
        delete[] newData;

        myfile.open (filenameChar);
        data << "</" << filenames[files] << ">";
        myfile << data.str();
        myfile.close();
        delete[] filenameChar;

    }

    cout << "Done creating" << endl;

}

/**
 * generates values for the temperature on the playground
 * values will be between 10 and 30
 * unit: °C
 */
int* CustomWorldUtility::generateTemperature(int size)
{
    int* data = new int[size];
    for (int i = 0; i < size; i++) {
        //10 - 30
        data[i] = (int)((rand() % 100)/5) + 10;
    }
    return data;
}

/**
 * generates values for the pressure on the playground
 * values will be between 995 and 1005
 * unit: hPa
 */
int* CustomWorldUtility::generatePressure(int size)
{
    int* data = new int[size];
    for (int i = 0; i < size; i++) {
        //995 - 1005
        data[i] = (int)((rand() % 100)/10) + 995;
    }
    return data;
}

/**
 * generates values for the humidity on the playground
 * values will be between 70 and 75
 * unit: %
 */
int* CustomWorldUtility::generateHumidity(int size)
{
    int* data = new int[size];
    for (int i = 0; i < size; i++) {
        //70 - 75
        data[i] = (int)((rand() % 100)/20 + 70);
    }
    return data;
}

/**
 * generates values for the light intensity on the playground
 * values will be between 10'000 and 100'000
 * unit: lx
 */
int* CustomWorldUtility::generateLight(int size)
{
    int* data = new int[size];
    for (int i = 0; i < size; i++) {
        //70 - 75
        data[i] = (int)((rand() % 100)*1000);
    }
    return data;
}

ExtendedMessage* CustomWorldUtility::generateMessage(const char* msgname)
{
    // Produce source and destination addresses.
    int src = getIndex();   // our module index
    int n = size();      // module vector size
    int dest = intuniform(0,n-2);
    if (dest>=src) dest++;

    // Create message object and set source and destination field.
    ExtendedMessage *msg = new ExtendedMessage(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

void CustomWorldUtility::updateDisplay()
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t",0,buf);
}

void CustomWorldUtility::finish()
{
    EV << "Sent:     " << numSent << endl;
    EV << "Received: " << numReceived << endl;
    EV << "Hop count, min:    " << hopCountStats.getMin() << endl;
    EV << "Hop count, max:    " << hopCountStats.getMax() << endl;
    EV << "Hop count, mean:   " << hopCountStats.getMean() << endl;
    EV << "Hop count, stddev: " << hopCountStats.getStddev() << endl;

    recordScalar("#sent", numSent);
    recordScalar("#received", numReceived);

    hopCountStats.recordAs("hop count");
}
