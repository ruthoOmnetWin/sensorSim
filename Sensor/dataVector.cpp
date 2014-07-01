/*
 * dataVector.cpp
 *
 *  Created on: Jun 28, 2014
 *      Author: rutho
 */

#define STRAIGTH 1
#define EXPONENTIALLY 2

#include <string.h>
#include <omnetpp.h>

class DataVector : public cSimpleModule
{
protected:
    int dataVectorType;
public:
    //DataVector(int);
    //virtual ~DataVector();
    int straight(int, int);
    int exponentially(int, int);
    void setDataVectorType(int);
    int getDataVectorType();
};

Define_Module(DataVector);

void DataVector::setDataVectorType(int dataVectorType)
{
    this->dataVectorType = dataVectorType;
}

int DataVector::getDataVectorType()
{
    return dataVectorType;
}

//---------------------------------------------------------------------------
//----------------------FUNCTIONS TO PROVIDE DATA----------------------------
//---------------------------------------------------------------------------

/**
 * returns at every position the value 1
 *
 * @param integer posX
 * @param integer posY
 * @return integer
 */
int DataVector::straight(int posX, int posY)
{
    return 1;
}

/**
 * returns the result of a 2-dimensional exponential function
 * computed by the 2 position-values and casted to integer
 *
 * @param integer posX
 * @param integer posY
 * @return integer
 */
int DataVector::exponentially(int posX, int posY)
{
    return (int)(posX * posX + posY * posY);
}
