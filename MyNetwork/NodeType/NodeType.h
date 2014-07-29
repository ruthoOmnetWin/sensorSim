/*
 * NodeType.h
 *
 *  Created on: Jul 29, 2014
 *      Author: rutho
 */

#ifndef NODETYPE_H_
#define NODETYPE_H_

#include <omnetpp.h>

class NodeType : public cModuleType
{
protected:
    cProperties *getProperties() const;
    cProperties *getParamProperties(const char *paramName) const;
    cProperties *getGateProperties(const char *gateName) const;
    cProperties *getSubmoduleProperties(const char *submoduleName, const char *submoduleType) const;
    cProperties *getConnectionProperties(int connectionId, const char *channelType) const;
    const char *getImplementationClassName() const;
protected:
    cModule *createModuleObject();
    void addParametersAndGatesTo(cModule *mod);
    void setupGateVectors(cModule *mod);
    void buildInside(cModule *mod);
public:
    bool isNetwork() const {return false;}
    bool isSimple() const {return true;}
    NodeType(const char *name);
    virtual ~NodeType();
};

#endif /* NODETYPE_H_ */
