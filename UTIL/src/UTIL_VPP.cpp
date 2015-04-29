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
std::string UTIL::VPP::NodeDef::getNodeName() const
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
UTIL::VPP::ListDef::ListDef(const string& p_nodeName):
  UTIL::VPP::NodeDef(p_nodeName), m_entryDef(NULL)
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
// for debugging
void UTIL::VPP::ListDef::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  string prefix(p_prefix);
  prefix += ".";
  prefix += getNodeName();
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
const std::list<UTIL::VPP::NodeDef*>&
UTIL::VPP::StructDef::getAttributesDef() const
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
  prefix += ".";
  prefix += getNodeName();
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
UTIL::VPP::FieldDef::FieldDef(const string& p_nodeName):
  UTIL::VPP::NodeDef(p_nodeName)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::VPP::FieldDef::~FieldDef()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
// for debugging
void UTIL::VPP::FieldDef::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  cout << p_prefix << "." << getNodeName() << endl;
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
std::string UTIL::VPP::Node::getNodeName() const
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
// overloaded from Node
UTIL::VPP::Node& UTIL::VPP::List::addNode() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  const UTIL::VPP::NodeDef* entryDef = getListDef()->getEntryDef();
  UTIL::VPP::Node* entry = UTIL::VPP::createNode(entryDef);
  m_entries.push_back(entry);
  return *entry;
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
    UTIL::VPP::Node* attribute = UTIL::VPP::createNode(attributeDef);
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
std::list<UTIL::VPP::Node*>&
UTIL::VPP::Struct::getAttributes()
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
// for debugging
void UTIL::VPP::Field::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  cout << p_prefix << "." << getNodeName() << endl;
}

///////////////////////////
// Node Instance Factory //
///////////////////////////

//-----------------------------------------------------------------------------
UTIL::VPP::Node* UTIL::VPP::createNode(const UTIL::VPP::NodeDef* p_nodeDef)
//-----------------------------------------------------------------------------
{
  // try creation of UTIL::VPP::List
  {
    const UTIL::VPP::ListDef* listDef =
      dynamic_cast<const UTIL::VPP::ListDef*>(p_nodeDef);
    if(listDef != NULL)
    {
      return new UTIL::VPP::List(listDef);
    }
  }
  // try creation of UTIL::VPP::Struct
  {
    const UTIL::VPP::StructDef* structDef =
      dynamic_cast<const UTIL::VPP::StructDef*>(p_nodeDef);
    if(structDef != NULL)
    {
      return new UTIL::VPP::Struct(structDef);
    }
  }
  // try creation of UTIL::VPP::Field
  {
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
