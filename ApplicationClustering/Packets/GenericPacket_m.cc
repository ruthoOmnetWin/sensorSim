//
// Generated file, do not edit! Created by opp_msgc 4.5 from Packets/GenericPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GenericPacket_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(GenericPacket);

GenericPacket::GenericPacket(const char *name, int kind) : ::cPacket(name,kind)
{
    this->packetType_var = 0;
    this->subType_var = 0;
    this->ttl_var = 0;
    this->payloadsize_var = 0;
    this->srcId_var = 0;
    this->dstId_var = 0;
    for (unsigned int i=0; i<100; i++)
        this->data_var[i] = 0;
}

GenericPacket::GenericPacket(const GenericPacket& other) : ::cPacket(other)
{
    copy(other);
}

GenericPacket::~GenericPacket()
{
}

GenericPacket& GenericPacket::operator=(const GenericPacket& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void GenericPacket::copy(const GenericPacket& other)
{
    this->packetType_var = other.packetType_var;
    this->subType_var = other.subType_var;
    this->ttl_var = other.ttl_var;
    this->payloadsize_var = other.payloadsize_var;
    this->srcId_var = other.srcId_var;
    this->dstId_var = other.dstId_var;
    for (unsigned int i=0; i<100; i++)
        this->data_var[i] = other.data_var[i];
}

void GenericPacket::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->packetType_var);
    doPacking(b,this->subType_var);
    doPacking(b,this->ttl_var);
    doPacking(b,this->payloadsize_var);
    doPacking(b,this->srcId_var);
    doPacking(b,this->dstId_var);
    doPacking(b,this->data_var,100);
}

void GenericPacket::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->packetType_var);
    doUnpacking(b,this->subType_var);
    doUnpacking(b,this->ttl_var);
    doUnpacking(b,this->payloadsize_var);
    doUnpacking(b,this->srcId_var);
    doUnpacking(b,this->dstId_var);
    doUnpacking(b,this->data_var,100);
}

unsigned char GenericPacket::getPacketType() const
{
    return packetType_var;
}

void GenericPacket::setPacketType(unsigned char packetType)
{
    this->packetType_var = packetType;
}

unsigned char GenericPacket::getSubType() const
{
    return subType_var;
}

void GenericPacket::setSubType(unsigned char subType)
{
    this->subType_var = subType;
}

unsigned char GenericPacket::getTtl() const
{
    return ttl_var;
}

void GenericPacket::setTtl(unsigned char ttl)
{
    this->ttl_var = ttl;
}

unsigned char GenericPacket::getPayloadsize() const
{
    return payloadsize_var;
}

void GenericPacket::setPayloadsize(unsigned char payloadsize)
{
    this->payloadsize_var = payloadsize;
}

unsigned short GenericPacket::getSrcId() const
{
    return srcId_var;
}

void GenericPacket::setSrcId(unsigned short srcId)
{
    this->srcId_var = srcId;
}

unsigned short GenericPacket::getDstId() const
{
    return dstId_var;
}

void GenericPacket::setDstId(unsigned short dstId)
{
    this->dstId_var = dstId;
}

unsigned int GenericPacket::getDataArraySize() const
{
    return 100;
}

unsigned char GenericPacket::getData(unsigned int k) const
{
    if (k>=100) throw cRuntimeError("Array of size 100 indexed by %lu", (unsigned long)k);
    return data_var[k];
}

void GenericPacket::setData(unsigned int k, unsigned char data)
{
    if (k>=100) throw cRuntimeError("Array of size 100 indexed by %lu", (unsigned long)k);
    this->data_var[k] = data;
}

class GenericPacketDescriptor : public cClassDescriptor
{
  public:
    GenericPacketDescriptor();
    virtual ~GenericPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(GenericPacketDescriptor);

GenericPacketDescriptor::GenericPacketDescriptor() : cClassDescriptor("GenericPacket", "cPacket")
{
}

GenericPacketDescriptor::~GenericPacketDescriptor()
{
}

bool GenericPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GenericPacket *>(obj)!=NULL;
}

const char *GenericPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GenericPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int GenericPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *GenericPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "packetType",
        "subType",
        "ttl",
        "payloadsize",
        "srcId",
        "dstId",
        "data",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int GenericPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "packetType")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "subType")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "ttl")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "payloadsize")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcId")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "dstId")==0) return base+5;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GenericPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "unsigned char",
        "unsigned char",
        "unsigned char",
        "unsigned short",
        "unsigned short",
        "unsigned char",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *GenericPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int GenericPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GenericPacket *pp = (GenericPacket *)object; (void)pp;
    switch (field) {
        case 6: return 100;
        default: return 0;
    }
}

std::string GenericPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GenericPacket *pp = (GenericPacket *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getPacketType());
        case 1: return ulong2string(pp->getSubType());
        case 2: return ulong2string(pp->getTtl());
        case 3: return ulong2string(pp->getPayloadsize());
        case 4: return ulong2string(pp->getSrcId());
        case 5: return ulong2string(pp->getDstId());
        case 6: return ulong2string(pp->getData(i));
        default: return "";
    }
}

bool GenericPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GenericPacket *pp = (GenericPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setPacketType(string2ulong(value)); return true;
        case 1: pp->setSubType(string2ulong(value)); return true;
        case 2: pp->setTtl(string2ulong(value)); return true;
        case 3: pp->setPayloadsize(string2ulong(value)); return true;
        case 4: pp->setSrcId(string2ulong(value)); return true;
        case 5: pp->setDstId(string2ulong(value)); return true;
        case 6: pp->setData(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *GenericPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *GenericPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GenericPacket *pp = (GenericPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


