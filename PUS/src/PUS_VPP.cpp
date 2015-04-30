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
// PUS Services - Variable Packet Module                                      *
//*****************************************************************************
#include "PUS_VPP.hpp"

#include <iostream>
#include "UTIL_STRING.hpp"

using namespace std;

//////////////
// TMpacket //
//////////////

//-----------------------------------------------------------------------------
PUS::VPP::TMpacket::TMpacket(): m_parameters(NULL)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::TMpacket::TMpacket(size_t p_bufferSize):
  PUS::PACKET::TMpacket::TMpacket(p_bufferSize), m_parameters(NULL)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::TMpacket::TMpacket(void* p_buffer, size_t p_bufferSize):
  PUS::PACKET::TMpacket::TMpacket(p_buffer, p_bufferSize), m_parameters(NULL)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::TMpacket::TMpacket(const void* p_buffer,
                             size_t p_bufferSize,
                             bool p_copyBuffer):
  PUS::PACKET::TMpacket::TMpacket(p_buffer, p_bufferSize, p_copyBuffer),
  m_parameters(NULL)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::TMpacket::TMpacket(const PUS::VPP::TMpacket& p_du):
  PUS::PACKET::TMpacket::TMpacket(p_du), m_parameters(NULL)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const PUS::VPP::TMpacket& PUS::VPP::TMpacket::operator=(
  const PUS::VPP::TMpacket& p_du)
//-----------------------------------------------------------------------------
{
  PUS::PACKET::TMpacket::operator=(p_du);
  return *this;
}

//-----------------------------------------------------------------------------
PUS::VPP::TMpacket::~TMpacket()
//-----------------------------------------------------------------------------
{
  if(m_parameters != NULL)
  {
    delete m_parameters;
  }
}

//-----------------------------------------------------------------------------
void
PUS::VPP::TMpacket::setParameterRootType(const UTIL::VPP::NodeDef* p_rootType)
//-----------------------------------------------------------------------------
{
  //initialize the variable parameters only if not already done
  if(m_parameters != NULL)
  {
    m_parameters = UTIL::VPP::NodeFactory::instance()->createNode(p_rootType);
  }
}

//////////////
// TCpacket //
//////////////

//-----------------------------------------------------------------------------
PUS::VPP::TCpacket::TCpacket(): m_parameters(NULL)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::TCpacket::TCpacket(size_t p_bufferSize):
  PUS::PACKET::TCpacket::TCpacket(p_bufferSize), m_parameters(NULL)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::TCpacket::TCpacket(void* p_buffer, size_t p_bufferSize):
  PUS::PACKET::TCpacket::TCpacket(p_buffer, p_bufferSize), m_parameters(NULL)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::TCpacket::TCpacket(const void* p_buffer,
                             size_t p_bufferSize,
                             bool p_copyBuffer):
  PUS::PACKET::TCpacket::TCpacket(p_buffer, p_bufferSize, p_copyBuffer),
  m_parameters(NULL)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::TCpacket::TCpacket(const PUS::VPP::TCpacket& p_du):
  PUS::PACKET::TCpacket::TCpacket(p_du)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const PUS::VPP::TCpacket& PUS::VPP::TCpacket::operator=(
  const PUS::VPP::TCpacket& p_du)
//-----------------------------------------------------------------------------
{
  PUS::PACKET::TCpacket::operator=(p_du);
  return *this;
}

//-----------------------------------------------------------------------------
PUS::VPP::TCpacket::~TCpacket()
//-----------------------------------------------------------------------------
{
  if(m_parameters != NULL)
  {
    delete m_parameters;
  }
}

//-----------------------------------------------------------------------------
void
PUS::VPP::TCpacket::setParameterRootType(const UTIL::VPP::NodeDef* p_rootType)
//-----------------------------------------------------------------------------
{
  //initialize the variable parameters only if not already done
  if(m_parameters != NULL)
  {
    m_parameters = UTIL::VPP::NodeFactory::instance()->createNode(p_rootType);
  }
}

////////////////////
// Node Instances //
////////////////////

//-----------------------------------------------------------------------------
PUS::VPP::List::List(const UTIL::VPP::ListDef* p_listDef):
  UTIL::VPP::List(p_listDef)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::List::~List()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::Struct::Struct(const UTIL::VPP::StructDef* p_structDef):
  UTIL::VPP::Struct(p_structDef)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::Struct::~Struct()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::Field::Field(const UTIL::VPP::FieldDef* p_fieldDef):
  UTIL::VPP::Field(p_fieldDef)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::Field::~Field()
//-----------------------------------------------------------------------------
{}

//////////////////
// Node Factory //
//////////////////

//-----------------------------------------------------------------------------
PUS::VPP::NodeFactory::NodeFactory()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::VPP::NodeFactory::~NodeFactory()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::VPP::Node*
PUS::VPP::NodeFactory::createNode(const UTIL::VPP::NodeDef* p_nodeDef)
//-----------------------------------------------------------------------------
{
  // try creation of UTIL::VPP::List
  {
    const UTIL::VPP::ListDef* listDef =
      dynamic_cast<const UTIL::VPP::ListDef*>(p_nodeDef);
    if(listDef != NULL)
    {
      return new PUS::VPP::List(listDef);
    }
  }
  // try creation of UTIL::VPP::Struct
  {
    const UTIL::VPP::StructDef* structDef =
      dynamic_cast<const UTIL::VPP::StructDef*>(p_nodeDef);
    if(structDef != NULL)
    {
      return new PUS::VPP::Struct(structDef);
    }
  }
  // try creation of UTIL::VPP::Field
  {
    const UTIL::VPP::FieldDef* fieldDef =
      dynamic_cast<const UTIL::VPP::FieldDef*>(p_nodeDef);
    if(fieldDef != NULL)
    {
      return new PUS::VPP::Field(fieldDef);
    }
  }
  // no specific instance type (should not happen) --> delegate to superclass
  return UTIL::VPP::NodeFactory::createNode(p_nodeDef);
}
