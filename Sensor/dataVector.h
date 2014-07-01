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

class DataVector
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

#endif /* DATAVECTOR_H_ */