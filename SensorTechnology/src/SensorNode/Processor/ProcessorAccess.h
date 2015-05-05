/*
 * ProcessorAccess.h
 *
 *  Created on: May 5, 2015
 *      Author: rutho
 */

#ifndef PROCESSORACCESS_H_
#define PROCESSORACCESS_H_

#include "Processor.h"

class ProcessorAccess  : public BaseModule
{
public:
    ProcessorAccess();
    virtual ~ProcessorAccess();
    Processor* findProcessor();
};

#endif /* PROCESSORACCESS_H_ */
