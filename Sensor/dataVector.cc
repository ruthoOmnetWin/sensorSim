/*
 * dataVector.cpp
 *
 *  Created on: Jun 28, 2014
 *      Author: rutho
 */

#include <string.h>
#include <omnetpp.h>
#include <dataVector.h>

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
