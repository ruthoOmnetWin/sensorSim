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

#ifndef DATAVECTOR_H_
#define DATAVECTOR_H_

#define STRAIGTH 0
#define EXPONENTIALLY 1

#include <omnetpp.h>

class DataVector : public cSimpleModule
{
protected:
    void initialize();
    void handleMessage(cMessage *msg);
    void activity();
    void finish();

private:
    int dataVectorType;
protected:
    int straight(int, int);
    int exponentially(int, int);
public:
    //DataVector(int);
    //virtual ~DataVector();
    void setDataVectorType(int);
    int getDataVectorType();
};

//Register_Class(DataVector);
Define_Module(DataVector);

#endif /* DATAVECTOR_H_ */
