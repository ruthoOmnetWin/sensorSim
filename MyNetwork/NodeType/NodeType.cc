/*
 * NodeType.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: rutho
 */

#include <NodeType.h>
#include <MyWirelessNode.h>

NodeType::NodeType(const char *name) : cModuleType(name) {
    // TODO Auto-generated constructor stub

}


NodeType::~NodeType() {
    // TODO Auto-generated destructor stub
}

cProperties* NodeType::getProperties() const
{

}

cProperties* NodeType::getParamProperties(const char*) const
{

}

cProperties *NodeType::getGateProperties(const char *gateName) const
{

}

cProperties *NodeType::getSubmoduleProperties(const char *submoduleName, const char *submoduleType) const
{

}

cProperties *NodeType::getConnectionProperties(int connectionId, const char *channelType) const
{

}

const char *NodeType::getImplementationClassName() const
{

}

cModule *NodeType::createModuleObject()
{
    cModule* node = new MyWirelessNode();
    return node;
}

void NodeType::addParametersAndGatesTo(cModule *mod)
{

}

void NodeType::setupGateVectors(cModule *mod)
{

}

void NodeType::buildInside(cModule *mod)
{

}
