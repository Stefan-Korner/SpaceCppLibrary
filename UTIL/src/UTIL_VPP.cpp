//*****************************************************************************
// (C) 2015, Stefan Korner, Austria                                           *
//                                                                            *
// The Space C++ Library is free software; you can redistribute it and/or     *
// modify it under the terms of the GNU Lesser General Public License as      *
// published by the Free Software Foundation; either version 2.1 of the       *
// License, or (at your option) any later version.                            *
//                                                                            *
// The Space C++ Library is distributed in the hope that it will be useful,   *
// but WITHOUT ANY WARRANTY; without even the implied warranty of             *
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser    *
// General Public License for more details.                                   *
//*****************************************************************************
// Variable Packets Definition and Instances                                  *
//*****************************************************************************
#include "UTIL_VPP.hpp"

#include <iostream>
#include "UTIL_STRING.hpp"

using namespace std;

//////////////////////
// Node Definitions //
//////////////////////

//-----------------------------------------------------------------------------
UTIL::VPP::NodeDef::NodeDef(const string& p_nodeName):
  m_nodeName(p_nodeName)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::VPP::NodeDef::~NodeDef()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
string UTIL::VPP::NodeDef::getNodeName() const
//-----------------------------------------------------------------------------
{
  return m_nodeName;
}

//-----------------------------------------------------------------------------
// for debugging
void UTIL::VPP::NodeDef::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  cout << p_prefix << "." << m_nodeName << endl;
}

//-----------------------------------------------------------------------------
UTIL::VPP::ListDef::ListDef(const string& p_nodeName,
                            ssize_t p_counterBitOffset,
                            size_t p_counterBitLength):
  UTIL::VPP::NodeDef(p_nodeName),
  m_entryDef(NULL),
  m_counterBitOffset(p_counterBitOffset),
  m_counterBitLength(p_counterBitLength)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::VPP::ListDef::~ListDef()
//-----------------------------------------------------------------------------
{
  if(m_entryDef != NULL)
  {
    delete m_entryDef;
  }
}

//-----------------------------------------------------------------------------
// takes over the ownership of p_entryDef
void UTIL::VPP::ListDef::setEntryDef(UTIL::VPP::NodeDef* p_entryDef)
//-----------------------------------------------------------------------------
{
  if(m_entryDef != NULL)
  {
    delete m_entryDef;
  }
  m_entryDef = p_entryDef;
}

//-----------------------------------------------------------------------------
const UTIL::VPP::NodeDef* UTIL::VPP::ListDef::getEntryDef() const
//-----------------------------------------------------------------------------
{
  return m_entryDef;
}

//-----------------------------------------------------------------------------
ssize_t UTIL::VPP::ListDef::getCounterBitOffset() const
//-----------------------------------------------------------------------------
{
  return m_counterBitOffset;
}

//-----------------------------------------------------------------------------
size_t UTIL::VPP::ListDef::getCounterBitLength() const
//-----------------------------------------------------------------------------
{
  return m_counterBitLength;
}

//-----------------------------------------------------------------------------
// for debugging
void UTIL::VPP::ListDef::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  string prefix(p_prefix);
  prefix += ".LIST";
  prefix += "(";
  if(getNodeName() != "")
  {
    prefix += getNodeName();
    prefix += ",";
  }
  prefix += UTIL::STRING::str(m_counterBitOffset);
  prefix += ",";
  prefix += UTIL::STRING::str(m_counterBitLength);
  prefix += ")";
  if(m_entryDef != NULL)
  {
    m_entryDef->dump(prefix);
  }
  else
  {
    cout << prefix << ".NULL" << endl;
  }
}

//-----------------------------------------------------------------------------
UTIL::VPP::StructDef::StructDef(const string& p_nodeName):
  UTIL::VPP::NodeDef(p_nodeName)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::VPP::StructDef::~StructDef()
//-----------------------------------------------------------------------------
{
  for(list<UTIL::VPP::NodeDef*>::iterator nIter = m_attributesDef.begin();
      nIter != m_attributesDef.end();
      nIter++)
  {
    delete (*nIter);
  }
}

//-----------------------------------------------------------------------------
// takes over the ownership of p_attributeDef
void
UTIL::VPP::StructDef::addAttributeDef(UTIL::VPP::NodeDef* p_attributeDef)
//-----------------------------------------------------------------------------
{
  m_attributesDef.push_back(p_attributeDef);
}

//-----------------------------------------------------------------------------
const list<UTIL::VPP::NodeDef*>& UTIL::VPP::StructDef::getAttributesDef() const
//-----------------------------------------------------------------------------
{
  return m_attributesDef;
}

//-----------------------------------------------------------------------------
// for debugging
void UTIL::VPP::StructDef::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  string prefix(p_prefix);
  prefix += ".STRUCT";
  if(getNodeName() != "")
  {
    prefix += "(";
    prefix += getNodeName();
    prefix += ")";
  }
  if(m_attributesDef.size() > 0)
  {
    size_t i = 0;
    for(list<UTIL::VPP::NodeDef*>::const_iterator nIter =
          m_attributesDef.begin();
        nIter != m_attributesDef.end();
        nIter++)
    {
      (*nIter)->dump(prefix + "[" + UTIL::STRING::str(i) + "]");
      i++;
    }
  }
  else
  {
    cout << prefix << ".NIL" << endl;
  }
}

//-----------------------------------------------------------------------------
UTIL::VPP::FieldDef::FieldDef(const string& p_nodeName,
                              UTIL::VPP::FieldDef::FieldType p_fieldType,
                              ssize_t p_bitOffset,
                              size_t p_bitLength,
                              uint32_t p_fieldTypeDetails):
  UTIL::VPP::NodeDef(p_nodeName),
  m_fieldType(p_fieldType),
  m_bitOffset(p_bitOffset),
  m_bitLength(p_bitLength),
  m_fieldTypeDetails(p_fieldTypeDetails)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::VPP::FieldDef::~FieldDef()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::VPP::FieldDef::FieldType UTIL::VPP::FieldDef::getFieldType() const
//-----------------------------------------------------------------------------
{
  return m_fieldType;
}

//-----------------------------------------------------------------------------
ssize_t UTIL::VPP::FieldDef::getBitOffset() const
//-----------------------------------------------------------------------------
{
  return m_bitOffset;
}

//-----------------------------------------------------------------------------
size_t UTIL::VPP::FieldDef::getBitLength() const
//-----------------------------------------------------------------------------
{
  return m_bitLength;
}

//-----------------------------------------------------------------------------
uint32_t UTIL::VPP::FieldDef::getFieldTypeDetails() const
//-----------------------------------------------------------------------------
{
  return m_fieldTypeDetails;
}

//-----------------------------------------------------------------------------
// for debugging
void UTIL::VPP::FieldDef::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  string prefix(p_prefix);
  switch(m_fieldType)
  {
  case ANY_FIELD:
    prefix += ".ANY_FIELD(";
    break;
  case BIT_FIELD:
    prefix += ".BIT_FIELD(";
    break;
  case BYTE_FIELD:
    prefix += ".BYTE_FIELD(";
    break;
  case UNSIGNED_FIELD:
    prefix += ".UNSIGNED_FIELD(";
    break;
  case BIG_UNSIGNED_FIELD:
    prefix += ".BIG_UNSIGNED_FIELD(";
    break;
  case STRING_FIELD:
    prefix += ".STRING_FIELD(";
    break;
  case ABS_TIME_FIELD:
    prefix += ".ABS_TIME_FIELD(";
    break;
  }
  if(getNodeName() != "")
  {
    prefix += getNodeName();
    prefix += ",";
  }
  prefix += UTIL::STRING::str(m_bitOffset);
  prefix += ",";
  prefix += UTIL::STRING::str(m_bitLength);
  prefix += ")";
  cout << prefix << endl;
}

////////////////////
// Node Instances //
////////////////////

//-----------------------------------------------------------------------------
UTIL::VPP::Node::Node(const UTIL::VPP::NodeDef* p_nodeDef):
  m_nodeDef(p_nodeDef)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::VPP::Node::~Node()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const UTIL::VPP::NodeDef* UTIL::VPP::Node::getNodeDef() const
//-----------------------------------------------------------------------------
{
  return m_nodeDef;
}

//-----------------------------------------------------------------------------
string UTIL::VPP::Node::getNodeName() const
//-----------------------------------------------------------------------------
{
  return m_nodeDef->getNodeName();
}

//-----------------------------------------------------------------------------
// generic access to sub-nodes, only provided by List and Struct
UTIL::VPP::Node& UTIL::VPP::Node::operator[](size_t) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  throw UTIL::Exception("This Node does not have child nodes");
}

//-----------------------------------------------------------------------------
// only provided by List, creates also defaut entries
void UTIL::VPP::Node::setListSize(size_t p_nr) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  throw
  UTIL::Exception("This Node does support changing number of child nodes");
}

//-----------------------------------------------------------------------------
// only provided by List
UTIL::VPP::Node& UTIL::VPP::Node::addNode() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  throw UTIL::Exception("This Node does support adding of child nodes");
}

//-----------------------------------------------------------------------------
void UTIL::VPP::Node::addNodes(size_t p_nr) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  for(size_t i = 0; i < p_nr; i++)
  {
    addNode();
  }
}

//-----------------------------------------------------------------------------
// only provided by List, takes over the ownership of p_node
void
UTIL::VPP::Node::appendNode(UTIL::VPP::Node* p_node) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  throw UTIL::Exception("This Node does support appending of child nodes");
}

//-----------------------------------------------------------------------------
// only provided by List, ownership passed to caller
UTIL::VPP::Node* UTIL::VPP::Node::popNode() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  throw UTIL::Exception("This Node does support retrieving of child nodes");
}

//-----------------------------------------------------------------------------
// moves the childs from p_node to this
void UTIL::VPP::Node::moveNodes(UTIL::VPP::Node& p_node) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(p_node.getNodeDef() != getNodeDef())
  {
    throw UTIL::Exception("Source and target Nodes have different types for move");
  }
}

//-----------------------------------------------------------------------------
// only provided by Field
void
UTIL::VPP::Node::setValue(const UTIL::Value& p_value) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  throw UTIL::Exception("This Node does support setting of a value");
}

//-----------------------------------------------------------------------------
// only provided by Field
const UTIL::Value& UTIL::VPP::Node::getValue() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  throw UTIL::Exception("This Node does support getting of a value");
}

//-----------------------------------------------------------------------------
// only provided by Field
UTIL::Value& UTIL::VPP::Node::value() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  throw UTIL::Exception("This Node does support accessing of a value");
}

//-----------------------------------------------------------------------------
// for debugging
void UTIL::VPP::Node::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  cout << p_prefix << "." << getNodeName() << ".NIL" << endl;
}

//-----------------------------------------------------------------------------
UTIL::VPP::List::List(const UTIL::VPP::ListDef* p_listDef):
  UTIL::VPP::Node(p_listDef)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::VPP::List::~List()
//-----------------------------------------------------------------------------
{
  for(list<UTIL::VPP::Node*>::iterator nIter = m_entries.begin();
      nIter != m_entries.end();
      nIter++)
  {
    delete (*nIter);
  }
}

//-----------------------------------------------------------------------------
const UTIL::VPP::ListDef* UTIL::VPP::List::getListDef() const
//-----------------------------------------------------------------------------
{
  return dynamic_cast<const UTIL::VPP::ListDef*>(getNodeDef());
}

//-----------------------------------------------------------------------------
list<UTIL::VPP::Node*>& UTIL::VPP::List::getEntries()
//-----------------------------------------------------------------------------
{
  return m_entries;
}

//-----------------------------------------------------------------------------
// overloaded from Node
UTIL::VPP::Node&
UTIL::VPP::List::operator[](size_t p_pos) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  size_t i = 0;
  for(list<UTIL::VPP::Node*>::iterator nIter = m_entries.begin();
      nIter != m_entries.end();
      nIter++)
  {
    if(i == p_pos)
    {
      return *(*nIter);
    }
    i++;
  }
  throw UTIL::Exception("UTIL::VPP::List::at(" + UTIL::STRING::str(i) + ") out of range");
}

//-----------------------------------------------------------------------------
// only provided by List, creates also defaut entries
void UTIL::VPP::List::setListSize(size_t p_nr) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // delete entries if the size is shrinked
  while(m_entries.size() > p_nr)
  {
    delete (m_entries.back());
    m_entries.pop_back();
  }
  // add entries if the size is expanded
  while(m_entries.size() < p_nr)
  {
    addNode();
  }
}

//-----------------------------------------------------------------------------
// overloaded from Node
UTIL::VPP::Node& UTIL::VPP::List::addNode() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  const UTIL::VPP::NodeDef* entryDef = getListDef()->getEntryDef();
  UTIL::VPP::Node* entry =
    UTIL::VPP::NodeFactory::instance()->createNode(entryDef);
  m_entries.push_back(entry);
  return *entry;
}

//-----------------------------------------------------------------------------
// overloaded from Node, takes over the ownership of p_node
void
UTIL::VPP::List::appendNode(UTIL::VPP::Node* p_node) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  const UTIL::VPP::NodeDef* entryDef = getListDef()->getEntryDef();
  if(p_node->getNodeDef() != entryDef)
  {
    throw UTIL::Exception("Append node has invalid definition type");
  }
  m_entries.push_back(p_node);
}

//-----------------------------------------------------------------------------
// overloaded from Node, ownership passed to caller
UTIL::VPP::Node* UTIL::VPP::List::popNode() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(m_entries.size() == 0)
  {
    return NULL;
  }
  UTIL::VPP::Node* entry = m_entries.front();
  m_entries.pop_front();
  return entry;
}

//-----------------------------------------------------------------------------
// overloaded from Node, moves the childs from p_node to this
void UTIL::VPP::List::moveNodes(UTIL::VPP::Node& p_node) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(p_node.getNodeDef() != getNodeDef())
  {
    throw UTIL::Exception("Source and target Nodes have different types for move");
  }
  UTIL::VPP::Node* child = p_node.popNode();
  while(child != NULL)
  {
    appendNode(child);
    child = p_node.popNode();
  }
}

//-----------------------------------------------------------------------------
// for debugging
void UTIL::VPP::List::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  string prefix(p_prefix);
  prefix += ".";
  prefix += getNodeName();
  if(m_entries.size() > 0)
  {
    size_t i = 0;
    for(list<UTIL::VPP::Node*>::const_iterator nIter = m_entries.begin();
        nIter != m_entries.end();
        nIter++)
    {
      (*nIter)->dump(prefix + "[" + UTIL::STRING::str(i) + "]");
      i++;
    }
  }
  else
  {
    cout << prefix << ".NIL" << endl;
  }
}

//-----------------------------------------------------------------------------
UTIL::VPP::Struct::Struct(const UTIL::VPP::StructDef* p_structDef):
  UTIL::VPP::Node(p_structDef)
//-----------------------------------------------------------------------------
{
  // create the attributes according to the struct definition
  const list<UTIL::VPP::NodeDef*>& attributesDef =
    p_structDef->getAttributesDef();
  for(list<UTIL::VPP::NodeDef*>::const_iterator nIter =
        attributesDef.begin();
      nIter != attributesDef.end();
      nIter++)
  {
    const UTIL::VPP::NodeDef* attributeDef = *nIter;
    UTIL::VPP::Node* attribute =
      UTIL::VPP::NodeFactory::instance()->createNode(attributeDef);
    m_attributes.push_back(attribute);
  }
}

//-----------------------------------------------------------------------------
UTIL::VPP::Struct::~Struct()
//-----------------------------------------------------------------------------
{
  for(list<UTIL::VPP::Node*>::iterator nIter = m_attributes.begin();
      nIter != m_attributes.end();
      nIter++)
  {
    delete (*nIter);
  }
}

//-----------------------------------------------------------------------------
const UTIL::VPP::StructDef* UTIL::VPP::Struct::getStructDef() const
//-----------------------------------------------------------------------------
{
  return dynamic_cast<const UTIL::VPP::StructDef*>(getNodeDef());
}

//-----------------------------------------------------------------------------
list<UTIL::VPP::Node*>& UTIL::VPP::Struct::getAttributes()
//-----------------------------------------------------------------------------
{
  return m_attributes;
}

//-----------------------------------------------------------------------------
// overloaded from Node
UTIL::VPP::Node&
UTIL::VPP::Struct::operator[](size_t p_pos) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  size_t i = 0;
  for(list<UTIL::VPP::Node*>::iterator nIter = m_attributes.begin();
      nIter != m_attributes.end();
      nIter++)
  {
    if(i == p_pos)
    {
      return *(*nIter);
    }
    i++;
  }
  throw UTIL::Exception("UTIL::VPP::Struct::at(" + UTIL::STRING::str(i) + ") out of range");
}

//-----------------------------------------------------------------------------
// overloaded from Node, moves the childs from p_node to this
void
UTIL::VPP::Struct::moveNodes(UTIL::VPP::Node& p_node) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(p_node.getNodeDef() != getNodeDef())
  {
    throw UTIL::Exception("Source and target Nodes have different types for move");
  }
  // delegate the move to all attributes
  size_t i = 0;
  for(list<UTIL::VPP::Node*>::iterator nIterTarget = m_attributes.begin();
      nIterTarget != m_attributes.end();
      nIterTarget++)
  {
    UTIL::VPP::Node& sourceAttribute = p_node[i];
    UTIL::VPP::Node* targetAttribute = *nIterTarget;
    targetAttribute->moveNodes(sourceAttribute);
    i++;
  }
}

//-----------------------------------------------------------------------------
// for debugging
void UTIL::VPP::Struct::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  string prefix(p_prefix);
  prefix += ".";
  prefix += getNodeName();
  if(m_attributes.size() > 0)
  {
    size_t i = 0;
    for(list<UTIL::VPP::Node*>::const_iterator nIter = m_attributes.begin();
        nIter != m_attributes.end();
        nIter++)
    {
      (*nIter)->dump(prefix + "[" + UTIL::STRING::str(i) + "]");
      i++;
    }
  }
  else
  {
    cout << prefix << ".NIL" << endl;
  }
}

//-----------------------------------------------------------------------------
UTIL::VPP::Field::Field(const UTIL::VPP::FieldDef* p_fieldDef):
  UTIL::VPP::Node(p_fieldDef)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::VPP::Field::~Field()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const UTIL::VPP::FieldDef* UTIL::VPP::Field::getFieldDef() const
//-----------------------------------------------------------------------------
{
  return dynamic_cast<const UTIL::VPP::FieldDef*>(getNodeDef());
}

//-----------------------------------------------------------------------------
// only provided by Field
void
UTIL::VPP::Field::setValue(const UTIL::Value& p_value) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  m_value = p_value;
}

//-----------------------------------------------------------------------------
// only provided by Field
const UTIL::Value& UTIL::VPP::Field::getValue() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return m_value;
}

//-----------------------------------------------------------------------------
// only provided by Field
UTIL::Value& UTIL::VPP::Field::value() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return m_value;
}

//-----------------------------------------------------------------------------
// for debugging
void UTIL::VPP::Field::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  cout << p_prefix
       << "."
       << getNodeName()
       << "("
       << m_value.dumpStr()
       << ")"
       << endl;
}

//////////////////
// Node Factory //
//////////////////

// global variables
UTIL::VPP::NodeFactory* UTIL::VPP::NodeFactory::s_instance = NULL;

//-----------------------------------------------------------------------------
UTIL::VPP::NodeFactory::NodeFactory()
//-----------------------------------------------------------------------------
{
  s_instance = this;
}

//-----------------------------------------------------------------------------
UTIL::VPP::NodeFactory::~NodeFactory()
//-----------------------------------------------------------------------------
{
  s_instance = NULL;
}

//-----------------------------------------------------------------------------
UTIL::VPP::NodeFactory* UTIL::VPP::NodeFactory::instance()
//-----------------------------------------------------------------------------
{
  return s_instance;
}

//-----------------------------------------------------------------------------
UTIL::VPP::Node*
UTIL::VPP::NodeFactory::createNode(const UTIL::VPP::NodeDef* p_nodeDef)
//-----------------------------------------------------------------------------
{
  {
    // *** List ***
    const UTIL::VPP::ListDef* listDef =
      dynamic_cast<const UTIL::VPP::ListDef*>(p_nodeDef);
    if(listDef != NULL)
    {
      return new UTIL::VPP::List(listDef);
    }
  }
  {
    // *** Struct ***
    const UTIL::VPP::StructDef* structDef =
      dynamic_cast<const UTIL::VPP::StructDef*>(p_nodeDef);
    if(structDef != NULL)
    {
      return new UTIL::VPP::Struct(structDef);
    }
  }
  {
    // *** Field ***
    const UTIL::VPP::FieldDef* fieldDef =
      dynamic_cast<const UTIL::VPP::FieldDef*>(p_nodeDef);
    if(fieldDef != NULL)
    {
      return new UTIL::VPP::Field(fieldDef);
    }
  }
  // no specific instance type --> create general instance type
  return new UTIL::VPP::Node(p_nodeDef);
}

///////////////////////////
// convenience functions //
///////////////////////////

//-----------------------------------------------------------------------------
ssize_t UTIL::VPP::getBinarySize(const UTIL::VPP::Node* p_node)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // traverse recursive through all nodes and accumulates the node sizes
  UTIL::VPP::Node* node = const_cast<UTIL::VPP::Node*>(p_node);
  {
    // *** List ***
    UTIL::VPP::List* listNode = dynamic_cast<UTIL::VPP::List*>(node);
    if(listNode != NULL)
    {
      const UTIL::VPP::ListDef* listDef = listNode->getListDef();
      ssize_t retVal = listDef->getCounterBitOffset() +
                       listDef->getCounterBitLength();
      list<UTIL::VPP::Node*>& entries = listNode->getEntries();
      for(list<UTIL::VPP::Node*>::iterator entryIter =  entries.begin();
          entryIter != entries.end();
          entryIter++)
      {
        UTIL::VPP::Node* entryNode = *entryIter;
        retVal += getBinarySize(entryNode);
      }
      return retVal;
    }
  }
  {
    // *** Struct ***
    UTIL::VPP::Struct* structNode = dynamic_cast<UTIL::VPP::Struct*>(node);
    if(structNode != NULL)
    {
      ssize_t retVal = 0;
      list<UTIL::VPP::Node*>& attributes = structNode->getAttributes();
      for(list<UTIL::VPP::Node*>::iterator attributeIter =  attributes.begin();
          attributeIter != attributes.end();
          attributeIter++)
      {
        UTIL::VPP::Node* attributeNode = *attributeIter;
        retVal += getBinarySize(attributeNode);
      }
      return retVal;
    }
  }
  {
    // *** Field ***
    UTIL::VPP::Field* fieldNode = dynamic_cast<UTIL::VPP::Field*>(node);
    if(fieldNode != NULL)
    {
      const UTIL::VPP::FieldDef* fieldDef = fieldNode->getFieldDef();
      return (fieldDef->getBitOffset() + fieldDef->getBitLength());
    }
  }
  throw UTIL::Exception("size calculation only for specific nodes supported");
}

//-----------------------------------------------------------------------------
ssize_t UTIL::VPP::getBinarySize(const UTIL::VPP::NodeDef* p_nodeDef,
                                 const UTIL::DU* p_du,
                                 size_t p_bitPos) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // traverse recursive through all nodes and accumulates the node sizes
  // only the list sizes are read from the data unit
  {
    // *** List ***
    const UTIL::VPP::ListDef* listDef =
      dynamic_cast<const UTIL::VPP::ListDef*>(p_nodeDef);
    if(listDef != NULL)
    {
      // read the actual repeat counter
      ssize_t counterBitOffset = listDef->getCounterBitOffset();
      size_t getCounterBitLength = listDef->getCounterBitLength();
      size_t counter = p_du->getBits(p_bitPos + counterBitOffset,
                                     getCounterBitLength);
      // calculate the size of the entries
      ssize_t cntrAndEntriesSize = counterBitOffset + getCounterBitLength;
      const NodeDef* entryDef = listDef->getEntryDef();
      for(size_t i = 0; i < counter; i++)
      {
        cntrAndEntriesSize += getBinarySize(entryDef,
                                            p_du,
                                            p_bitPos + cntrAndEntriesSize);
      }
      return cntrAndEntriesSize;
    }
  }
  {
    // *** Struct ***
    const UTIL::VPP::StructDef* structDef =
      dynamic_cast<const UTIL::VPP::StructDef*>(p_nodeDef);
    if(structDef != NULL)
    {
      // calculate the size of the attributes
      ssize_t attributesSize = 0;
      const list<NodeDef*>& attributesDef = structDef->getAttributesDef();
      for(list<UTIL::VPP::NodeDef*>::const_iterator attributesDefIter =
            attributesDef.begin();
          attributesDefIter != attributesDef.end();
          attributesDefIter++)
      {
        const UTIL::VPP::NodeDef* attributeDef = *attributesDefIter;
        attributesSize += getBinarySize(attributeDef,
                                        p_du,
                                        p_bitPos + attributesSize);
      }
      return attributesSize;
    }
  }
  {
    // *** Field ***
    const UTIL::VPP::FieldDef* fieldDef =
      dynamic_cast<const UTIL::VPP::FieldDef*>(p_nodeDef);
    if(fieldDef != NULL)
    {
      return (fieldDef->getBitOffset() + fieldDef->getBitLength());
    }
  }
  throw UTIL::Exception("size calculation only for specific nodes supported");
}

//-----------------------------------------------------------------------------
// returns the number of bits written
ssize_t UTIL::VPP::writeToDataUnit(const UTIL::VPP::Node* p_node,
                                   UTIL::DU* p_du,
                                   size_t p_bitPos) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // traverse recursive through all nodes and write the node data to the DU
  UTIL::VPP::Node* node = const_cast<UTIL::VPP::Node*>(p_node);
  {
    // *** List ***
    UTIL::VPP::List* listNode = dynamic_cast<UTIL::VPP::List*>(node);
    if(listNode != NULL)
    {
      const UTIL::VPP::ListDef* listDef = listNode->getListDef();
      // write the actual repeat counter
      ssize_t counterBitOffset = listDef->getCounterBitOffset();
      size_t getCounterBitLength = listDef->getCounterBitLength();
      size_t counter = listNode->getEntries().size();
      p_du->setBits(p_bitPos + counterBitOffset,
                    getCounterBitLength,
                    counter);
      // write the entries
      ssize_t cntrAndEntriesSize = counterBitOffset + getCounterBitLength;
      list<UTIL::VPP::Node*>& entries = listNode->getEntries();
      for(list<UTIL::VPP::Node*>::iterator entryIter =  entries.begin();
          entryIter != entries.end();
          entryIter++)
      {
        UTIL::VPP::Node* entryNode = *entryIter;
        cntrAndEntriesSize +=
          writeToDataUnit(entryNode, p_du, p_bitPos + cntrAndEntriesSize);
      }
      return cntrAndEntriesSize;
    }
  }
  {
    // *** Struct ***
    UTIL::VPP::Struct* structNode = dynamic_cast<UTIL::VPP::Struct*>(node);
    if(structNode != NULL)
    {
      ssize_t attributesSize = 0;
      list<UTIL::VPP::Node*>& attributes = structNode->getAttributes();
      for(list<UTIL::VPP::Node*>::iterator attributeIter =  attributes.begin();
          attributeIter != attributes.end();
          attributeIter++)
      {
        UTIL::VPP::Node* attributeNode = *attributeIter;
        attributesSize += writeToDataUnit(attributeNode,
                                          p_du,
                                          p_bitPos + attributesSize);
      }
      return attributesSize;
    }
  }
  {
    // *** Field ***
    UTIL::VPP::Field* fieldNode = dynamic_cast<UTIL::VPP::Field*>(node);
    if(fieldNode != NULL)
    {
      const UTIL::VPP::FieldDef* fieldDef = fieldNode->getFieldDef();
      ssize_t bitOffset = fieldDef->getBitOffset();
      size_t absoluteBitOffset = p_bitPos + bitOffset;
      size_t bitLength = fieldDef->getBitLength();
      UTIL::VPP::FieldDef::FieldType fieldType = fieldDef->getFieldType();
      const UTIL::Value& fieldValue = fieldNode->getValue();
      // special handling of bit oriented fields
      if((fieldType == UTIL::VPP::FieldDef::ANY_FIELD) ||
         (fieldType == UTIL::VPP::FieldDef::BIT_FIELD))
      {
        uint32_t bitFieldValue = fieldValue.getUInt32();
        p_du->setBits(absoluteBitOffset, bitLength, bitFieldValue);
      }
      else
      {
        // byte oriented fields
        if((absoluteBitOffset % 8) != 0)
        {
          throw UTIL::Exception("byte oriented data field not byte aligned");
        }
        if((bitLength % 8) != 0)
        {
          throw UTIL::Exception("byte oriented data field not byte sized");
        }
        size_t absoluteByteOffset = absoluteBitOffset / 8;
        size_t byteLength = bitLength / 8;
        switch(fieldType)
        {
        case UTIL::VPP::FieldDef::BYTE_FIELD:
          {
            size_t octetStringLength = fieldValue.getOctetStringLength();
            if(octetStringLength != byteLength)
            {
              throw UTIL::Exception("byte field value has wrong size");
            }
            const uint8_t* octetString = fieldValue.getOctetString();
            p_du->setBytes(absoluteByteOffset, byteLength, octetString);
          }
          break;
        case UTIL::VPP::FieldDef::UNSIGNED_FIELD:
          {
            uint32_t uintFieldValue = fieldValue.getUInt32();
            p_du->setUnsigned(absoluteByteOffset, byteLength, uintFieldValue);
          }
          break;
        case UTIL::VPP::FieldDef::BIG_UNSIGNED_FIELD:
          {
            uint64_t bigUintFieldValue = fieldValue.getUInt64();
            p_du->setBigUnsigned(absoluteByteOffset,
                                 byteLength,
                                 bigUintFieldValue);
          }
          break;
        case UTIL::VPP::FieldDef::STRING_FIELD:
          {
            string asciiString(fieldValue.getAsciiString());
            size_t asciiStringLength = asciiString.size();
            if(asciiStringLength != byteLength)
            {
              throw UTIL::Exception("ascii field value has wrong size");
            }
            p_du->setString(absoluteByteOffset, byteLength, asciiString);
          }
          break;
        case UTIL::VPP::FieldDef::ABS_TIME_FIELD:
          {
            UTIL::AbsTime absTime(fieldValue.getAbsTime());
            uint32_t timeCode = fieldDef->getFieldTypeDetails();
            p_du->setAbsTime(absoluteByteOffset, timeCode, absTime);
          }
          break;
        default:
          // should not happen
          break;
        }
      }
      return (bitOffset + bitLength);
    }
  }
  throw UTIL::Exception("size calculation only for specific nodes supported");
}

//-----------------------------------------------------------------------------
// returns the number of bits read
ssize_t UTIL::VPP::readFromDataUnit(UTIL::VPP::Node* p_node,
                                    const UTIL::DU* p_du,
                                    size_t p_bitPos) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // traverse recursive through all nodes and read the node data from the DU
  {
    // *** List ***
    UTIL::VPP::List* listNode = dynamic_cast<UTIL::VPP::List*>(p_node);
    if(listNode != NULL)
    {
      const UTIL::VPP::ListDef* listDef = listNode->getListDef();
      // read the actual repeat counter
      ssize_t counterBitOffset = listDef->getCounterBitOffset();
      size_t getCounterBitLength = listDef->getCounterBitLength();
      size_t counter = p_du->getBits(p_bitPos + counterBitOffset,
                                     getCounterBitLength);
      listNode->setListSize(counter);
      // read the entries
      ssize_t cntrAndEntriesSize = counterBitOffset + getCounterBitLength;
      list<UTIL::VPP::Node*>& entries = listNode->getEntries();
      for(list<UTIL::VPP::Node*>::iterator entryIter =  entries.begin();
          entryIter != entries.end();
          entryIter++)
      {
        UTIL::VPP::Node* entryNode = *entryIter;
        cntrAndEntriesSize +=
          readFromDataUnit(entryNode, p_du, p_bitPos + cntrAndEntriesSize);
      }
      return cntrAndEntriesSize;
    }
  }
  {
    // *** Struct ***
    UTIL::VPP::Struct* structNode = dynamic_cast<UTIL::VPP::Struct*>(p_node);
    if(structNode != NULL)
    {
      ssize_t attributesSize = 0;
      list<UTIL::VPP::Node*>& attributes = structNode->getAttributes();
      for(list<UTIL::VPP::Node*>::iterator attributeIter =  attributes.begin();
          attributeIter != attributes.end();
          attributeIter++)
      {
        UTIL::VPP::Node* attributeNode = *attributeIter;
        attributesSize += readFromDataUnit(attributeNode,
                                           p_du,
                                           p_bitPos + attributesSize);
      }
      return attributesSize;
    }
  }
  {
    // *** Field ***
    UTIL::VPP::Field* fieldNode = dynamic_cast<UTIL::VPP::Field*>(p_node);
    if(fieldNode != NULL)
    {
      const UTIL::VPP::FieldDef* fieldDef = fieldNode->getFieldDef();
      ssize_t bitOffset = fieldDef->getBitOffset();
      size_t absoluteBitOffset = p_bitPos + bitOffset;
      size_t bitLength = fieldDef->getBitLength();
      UTIL::VPP::FieldDef::FieldType fieldType = fieldDef->getFieldType();
      UTIL::Value& fieldValue = fieldNode->value();
      // special handling of bit oriented fields
      if((fieldType == UTIL::VPP::FieldDef::ANY_FIELD) ||
         (fieldType == UTIL::VPP::FieldDef::BIT_FIELD))
      {
        uint32_t bitFieldValue = p_du->getBits(absoluteBitOffset, bitLength);
        fieldValue.set(bitFieldValue);
      }
      else
      {
        // byte oriented fields
        if((absoluteBitOffset % 8) != 0)
        {
          throw UTIL::Exception("byte oriented data field not byte aligned");
        }
        if((bitLength % 8) != 0)
        {
          throw UTIL::Exception("byte oriented data field not byte sized");
        }
        size_t absoluteByteOffset = absoluteBitOffset / 8;
        size_t byteLength = bitLength / 8;
        switch(fieldType)
        {
        case UTIL::VPP::FieldDef::BYTE_FIELD:
          {
            const uint8_t* octetString =
              p_du->getBytes(absoluteByteOffset, byteLength);
            fieldValue.set(octetString, byteLength);
          }
          break;
        case UTIL::VPP::FieldDef::UNSIGNED_FIELD:
          {
            uint32_t uintFieldValue =
              p_du->getUnsigned(absoluteByteOffset, byteLength);
            fieldValue.set(uintFieldValue);
          }
          break;
        case UTIL::VPP::FieldDef::BIG_UNSIGNED_FIELD:
          {
            uint64_t bigUintFieldValue =
              p_du->getBigUnsigned(absoluteByteOffset, byteLength);
            fieldValue.set(bigUintFieldValue);
          }
          break;
        case UTIL::VPP::FieldDef::STRING_FIELD:
          {
            string asciiString(p_du->getString(absoluteByteOffset,
                                               byteLength));
            fieldValue.set(asciiString);
          }
          break;
        case UTIL::VPP::FieldDef::ABS_TIME_FIELD:
          {
            uint32_t timeCode = fieldDef->getFieldTypeDetails();
            UTIL::AbsTime absTime(p_du->getAbsTime(absoluteByteOffset,
                                                   timeCode));

            fieldValue.set(absTime);
          }
          break;
        default:
          // should not happen
          break;
        }
      }
      return (bitOffset + bitLength);
    }
  }
  throw UTIL::Exception("size calculation only for specific nodes supported");
}
