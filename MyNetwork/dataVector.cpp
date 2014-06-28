/*
 * dataVector.cpp
 *
 *  Created on: Jun 28, 2014
 *      Author: rutho
 */

#define STRAIGTH 1
#define EXPONENTIALLY 2

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

class dataVector : cSimpleModule
{
private:
    int dataVectorType;
public:
    dataVector(int);
    virtual ~dataVector();
    int straight(int, int);
    int exponentially(int, int);
    void setDataVectorType(int);
    int getDataVectorType();
protected:
    void initialize();
};

//Define_Module(dataVector(int));

dataVector::dataVector(int dataVectorType) {
    // TODO Auto-generated constructor stub
    this->dataVectorType = dataVectorType;
}

dataVector::~dataVector() {
    // TODO Auto-generated destructor stub
}



void dataVector::initialize()
{
    if (this->getDataVectorType() == STRAIGTH) {

    } else if (this->getDataVectorType() == EXPONENTIALLY) {

    }
}

void dataVector::setDataVectorType(int dataVectorType)
{
    this->dataVectorType = dataVectorType;
}

int dataVector::getDataVectorType()
{
    return dataVectorType;
}

//---------------------------------------------------------------------------
//----------------------FUNCTIONS TO PROVIDE DATA----------------------------
//---------------------------------------------------------------------------
int dataVector::straight(int posX, int posY)
{
    return 1;
}

int dataVector::exponentially(int posX, int posY)
{
    return (int)(posX * posX + posY * posY);
}
