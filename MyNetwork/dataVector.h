/*
 * dataVector.h
 *
 *  Created on: Jun 28, 2014
 *      Author: rutho
 */

#ifndef DATAVECTOR_H_
#define DATAVECTOR_H_

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
    dataVector();
    virtual ~dataVector();
    int straight(int, int);
    int exponentially(int, int);
    void setDataVectorType(int);
    int getDataVectorType();
protected:
    void initialize();
};

#endif /* DATAVECTOR_H_ */

