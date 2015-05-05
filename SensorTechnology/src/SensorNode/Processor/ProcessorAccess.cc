/*
 * ProcessorAccess.cc
 *
 *  Created on: May 5, 2015
 *      Author: rutho
 */

#include <ProcessorAccess.h>
#include <FindModule.h>

ProcessorAccess::ProcessorAccess() {
    // TODO Auto-generated constructor stub

}

ProcessorAccess::~ProcessorAccess() {
    // TODO Auto-generated destructor stub
}

Processor* ProcessorAccess::findProcessor()
{
    Processor* processor = FindModule<Processor*>::findSubModule(findHost());
    return processor;
}
