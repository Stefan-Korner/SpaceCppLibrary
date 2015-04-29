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
// Space Simulation - Variable Packets Definition and Instances               *
//*****************************************************************************
#include "SPACE_VPP.hpp"

#include <iostream>
#include "UTIL_STRING.hpp"

using namespace std;

//////////////////////
// Node Definitions //
//////////////////////

//-----------------------------------------------------------------------------
SPACE::VPP::NodeDef::NodeDef(const string& p_nodeName):
  m_nodeName(p_nodeName)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPACE::VPP::NodeDef::~NodeDef()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
std::string SPACE::VPP::NodeDef::getNodeName() const
//-----------------------------------------------------------------------------
{
  return m_nodeName;
}

//-----------------------------------------------------------------------------
// for debugging
void SPACE::VPP::NodeDef::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  cout << p_prefix << "." << m_nodeName << endl;
}

//-----------------------------------------------------------------------------
SPACE::VPP::ListDef::ListDef(const string& p_nodeName):
  SPACE::VPP::NodeDef(p_nodeName), m_entryDef(NULL)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPACE::VPP::ListDef::~ListDef()
//-----------------------------------------------------------------------------
{
  if(m_entryDef != NULL)
  {
    delete m_entryDef;
  }
}

//-----------------------------------------------------------------------------
// takes over the ownership of p_entryDef
void SPACE::VPP::ListDef::setEntryDef(SPACE::VPP::NodeDef* p_entryDef)
//-----------------------------------------------------------------------------
{
  if(m_entryDef != NULL)
  {
    delete m_entryDef;
  }
  m_entryDef = p_entryDef;
}

//-----------------------------------------------------------------------------
const SPACE::VPP::NodeDef* SPACE::VPP::ListDef::getEntryDef() const
//-----------------------------------------------------------------------------
{
  return m_entryDef;
}

//-----------------------------------------------------------------------------
// for debugging
void SPACE::VPP::ListDef::dump(const string& p_prefix) const
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
SPACE::VPP::StructDef::StructDef(const string& p_nodeName):
  SPACE::VPP::NodeDef(p_nodeName)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPACE::VPP::StructDef::~StructDef()
//-----------------------------------------------------------------------------
{
  for(list<SPACE::VPP::NodeDef*>::iterator nIter = m_attributesDef.begin();
      nIter != m_attributesDef.end();
      nIter++)
  {
    delete (*nIter);
  }
}

//-----------------------------------------------------------------------------
// takes over the ownership of p_attributeDef
void
SPACE::VPP::StructDef::addAttributeDef(SPACE::VPP::NodeDef* p_attributeDef)
//-----------------------------------------------------------------------------
{
  m_attributesDef.push_back(p_attributeDef);
}

//-----------------------------------------------------------------------------
const std::list<SPACE::VPP::NodeDef*>&
SPACE::VPP::StructDef::getAttributesDef() const
//-----------------------------------------------------------------------------
{
  return m_attributesDef;
}

//-----------------------------------------------------------------------------
// for debugging
void SPACE::VPP::StructDef::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  string prefix(p_prefix);
  prefix += ".";
  prefix += getNodeName();
  if(m_attributesDef.size() > 0)
  {
    size_t i = 0;
    for(list<SPACE::VPP::NodeDef*>::const_iterator nIter =
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
SPACE::VPP::FieldDef::FieldDef(const string& p_nodeName):
  SPACE::VPP::NodeDef(p_nodeName)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPACE::VPP::FieldDef::~FieldDef()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
// for debugging
void SPACE::VPP::FieldDef::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  cout << p_prefix << "." << getNodeName() << endl;
}

////////////////////
// Node Instances //
////////////////////

//-----------------------------------------------------------------------------
SPACE::VPP::Node::Node(const SPACE::VPP::NodeDef* p_nodeDef):
  m_nodeDef(p_nodeDef)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPACE::VPP::Node::~Node()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const SPACE::VPP::NodeDef* SPACE::VPP::Node::getNodeDef() const
//-----------------------------------------------------------------------------
{
  return m_nodeDef;
}

//-----------------------------------------------------------------------------
std::string SPACE::VPP::Node::getNodeName() const
//-----------------------------------------------------------------------------
{
  return m_nodeDef->getNodeName();
}

//-----------------------------------------------------------------------------
// generic access to sub-nodes, only provided by List and Struct
SPACE::VPP::Node& SPACE::VPP::Node::operator[](size_t) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  throw UTIL::Exception("This Node does not have child nodes");
}

//-----------------------------------------------------------------------------
// only provided by List
SPACE::VPP::Node& SPACE::VPP::Node::addNode() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  throw UTIL::Exception("This Node does support adding of child nodes");
}

//-----------------------------------------------------------------------------
void SPACE::VPP::Node::addNodes(size_t p_nr) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  for(size_t i = 0; i < p_nr; i++)
  {
    addNode();
  }
}

//-----------------------------------------------------------------------------
// for debugging
void SPACE::VPP::Node::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  cout << p_prefix << "." << getNodeName() << ".NIL" << endl;
}

//-----------------------------------------------------------------------------
SPACE::VPP::List::List(const SPACE::VPP::ListDef* p_listDef):
  SPACE::VPP::Node(p_listDef)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPACE::VPP::List::~List()
//-----------------------------------------------------------------------------
{
  for(list<SPACE::VPP::Node*>::iterator nIter = m_entries.begin();
      nIter != m_entries.end();
      nIter++)
  {
    delete (*nIter);
  }
}

//-----------------------------------------------------------------------------
const SPACE::VPP::ListDef* SPACE::VPP::List::getListDef() const
//-----------------------------------------------------------------------------
{
  return dynamic_cast<const SPACE::VPP::ListDef*>(getNodeDef());
}

//-----------------------------------------------------------------------------
list<SPACE::VPP::Node*>& SPACE::VPP::List::getEntries()
//-----------------------------------------------------------------------------
{
  return m_entries;
}

//-----------------------------------------------------------------------------
// overloaded from Node
SPACE::VPP::Node&
SPACE::VPP::List::operator[](size_t p_pos) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  size_t i = 0;
  for(list<SPACE::VPP::Node*>::iterator nIter = m_entries.begin();
      nIter != m_entries.end();
      nIter++)
  {
    if(i == p_pos)
    {
      return *(*nIter);
    }
    i++;
  }
  throw UTIL::Exception("SPACE::VPP::List::at(" + UTIL::STRING::str(i) + ") out of range");
}

//-----------------------------------------------------------------------------
// overloaded from Node
SPACE::VPP::Node& SPACE::VPP::List::addNode() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  const SPACE::VPP::NodeDef* entryDef = getListDef()->getEntryDef();
  SPACE::VPP::Node* entry = SPACE::VPP::createNode(entryDef);
  m_entries.push_back(entry);
  return *entry;
}

//-----------------------------------------------------------------------------
// for debugging
void SPACE::VPP::List::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  string prefix(p_prefix);
  prefix += ".";
  prefix += getNodeName();
  if(m_entries.size() > 0)
  {
    size_t i = 0;
    for(list<SPACE::VPP::Node*>::const_iterator nIter = m_entries.begin();
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
SPACE::VPP::Struct::Struct(const SPACE::VPP::StructDef* p_structDef):
  SPACE::VPP::Node(p_structDef)
//-----------------------------------------------------------------------------
{
  // create the attributes according to the struct definition
  const list<SPACE::VPP::NodeDef*>& attributesDef =
    p_structDef->getAttributesDef();
  for(list<SPACE::VPP::NodeDef*>::const_iterator nIter =
        attributesDef.begin();
      nIter != attributesDef.end();
      nIter++)
  {
    const SPACE::VPP::NodeDef* attributeDef = *nIter;
    SPACE::VPP::Node* attribute = SPACE::VPP::createNode(attributeDef);
    m_attributes.push_back(attribute);
  }
}

//-----------------------------------------------------------------------------
SPACE::VPP::Struct::~Struct()
//-----------------------------------------------------------------------------
{
  for(list<SPACE::VPP::Node*>::iterator nIter = m_attributes.begin();
      nIter != m_attributes.end();
      nIter++)
  {
    delete (*nIter);
  }
}

//-----------------------------------------------------------------------------
const SPACE::VPP::StructDef* SPACE::VPP::Struct::getStructDef() const
//-----------------------------------------------------------------------------
{
  return dynamic_cast<const SPACE::VPP::StructDef*>(getNodeDef());
}

//-----------------------------------------------------------------------------
std::list<SPACE::VPP::Node*>&
SPACE::VPP::Struct::getAttributes()
//-----------------------------------------------------------------------------
{
  return m_attributes;
}

//-----------------------------------------------------------------------------
// overloaded from Node
SPACE::VPP::Node&
SPACE::VPP::Struct::operator[](size_t p_pos) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  size_t i = 0;
  for(list<SPACE::VPP::Node*>::iterator nIter = m_attributes.begin();
      nIter != m_attributes.end();
      nIter++)
  {
    if(i == p_pos)
    {
      return *(*nIter);
    }
    i++;
  }
  throw UTIL::Exception("SPACE::VPP::Struct::at(" + UTIL::STRING::str(i) + ") out of range");
}

//-----------------------------------------------------------------------------
// for debugging
void SPACE::VPP::Struct::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  string prefix(p_prefix);
  prefix += ".";
  prefix += getNodeName();
  if(m_attributes.size() > 0)
  {
    size_t i = 0;
    for(list<SPACE::VPP::Node*>::const_iterator nIter = m_attributes.begin();
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
SPACE::VPP::Field::Field(const SPACE::VPP::FieldDef* p_fieldDef):
  SPACE::VPP::Node(p_fieldDef)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPACE::VPP::Field::~Field()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const SPACE::VPP::FieldDef* SPACE::VPP::Field::getFieldDef() const
//-----------------------------------------------------------------------------
{
  return dynamic_cast<const SPACE::VPP::FieldDef*>(getNodeDef());
}

//-----------------------------------------------------------------------------
// for debugging
void SPACE::VPP::Field::dump(const string& p_prefix) const
//-----------------------------------------------------------------------------
{
  cout << p_prefix << "." << getNodeName() << endl;
}

///////////////////////////
// Node Instance Factory //
///////////////////////////

//-----------------------------------------------------------------------------
SPACE::VPP::Node* SPACE::VPP::createNode(const SPACE::VPP::NodeDef* p_nodeDef)
//-----------------------------------------------------------------------------
{
  // try creation of SPACE::VPP::List
  {
    const SPACE::VPP::ListDef* listDef =
      dynamic_cast<const SPACE::VPP::ListDef*>(p_nodeDef);
    if(listDef != NULL)
    {
      return new SPACE::VPP::List(listDef);
    }
  }
  // try creation of SPACE::VPP::Struct
  {
    const SPACE::VPP::StructDef* structDef =
      dynamic_cast<const SPACE::VPP::StructDef*>(p_nodeDef);
    if(structDef != NULL)
    {
      return new SPACE::VPP::Struct(structDef);
    }
  }
  // try creation of SPACE::VPP::Field
  {
    const SPACE::VPP::FieldDef* fieldDef =
      dynamic_cast<const SPACE::VPP::FieldDef*>(p_nodeDef);
    if(fieldDef != NULL)
    {
      return new SPACE::VPP::Field(fieldDef);
    }
  }
  // no specific instance type --> create general instance type
  return new SPACE::VPP::Node(p_nodeDef);
}
