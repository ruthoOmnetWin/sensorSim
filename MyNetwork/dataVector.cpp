/*
 * dataVector.cpp
 *
 *  Created on: Jun 28, 2014
 *      Author: rutho
 */

#include <dataVector.h>

dataVector::dataVector(int dataVectorType) {
    // TODO Auto-generated constructor stub
    this->dataVectorType = dataVectorType;
}

dataVector::~dataVector() {
    // TODO Auto-generated destructor stub
}

Define_Module(dataVector);

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
