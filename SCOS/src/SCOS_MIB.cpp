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
// SCOS - Mission Database (MIB) handling                                     *
//*****************************************************************************
#include "SCOS_MIB.hpp"

#include <iostream>
#include "UTIL_STRING.hpp"

using namespace std;
using namespace UTIL::STRING;

///////////////
// PIDrecord //
///////////////

//-----------------------------------------------------------------------------
// initialise selected attributes from the record
SCOS::MIB::PIDrecord::PIDrecord(const vector<string>& p_fields):
  pidType(asInt(p_fields[0])),
  pidSType(asInt(p_fields[1])),
  pidAPID(asInt(p_fields[2])),
  pidPI1(asInt(p_fields[3])),
  pidPI2(asInt(p_fields[4])),
  pidSPID(asInt(p_fields[5])),
  pidDescr(p_fields[6]),
  pidDFHsize(asInt(p_fields[9])),
  pidCheck(p_fields[13] == "1")
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
// record key
int SCOS::MIB::PIDrecord::key() const
//-----------------------------------------------------------------------------
{
  return pidSPID;
}

//-----------------------------------------------------------------------------
// foreign key to PICrecord
string SCOS::MIB::PIDrecord::picKey() const
//-----------------------------------------------------------------------------
{
  return ("[" + str(pidType) + ", " + str(pidSType) + "]");
}

///////////////
// PICrecord //
///////////////

//-----------------------------------------------------------------------------
// initialise selected attributes from the record
SCOS::MIB::PICrecord::PICrecord(const vector<string>& p_fields)
//-----------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------
// record key
string SCOS::MIB::PICrecord::key() const
//-----------------------------------------------------------------------------
{
  return ("[" + str(picType) + ", " + str(picSType) + "]");
}

////////////////
// TPCFrecord //
////////////////

//-----------------------------------------------------------------------------
// initialise selected attributes from the record
SCOS::MIB::TPCFrecord::TPCFrecord(const vector<string>& p_fields)
//-----------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------
// record key
int SCOS::MIB::TPCFrecord::key() const
//-----------------------------------------------------------------------------
{
  return tpcfSPID;
}

///////////////
// PCFrecord //
///////////////

//-----------------------------------------------------------------------------
// initialise selected attributes from the record
SCOS::MIB::PCFrecord::PCFrecord(const vector<string>& p_fields)
//-----------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------
// record key
string SCOS::MIB::PCFrecord::key() const
//-----------------------------------------------------------------------------
{
  return pcfName;
}

///////////////
// PLFrecord //
///////////////

//-----------------------------------------------------------------------------
// initialise selected attributes from the record
SCOS::MIB::PLFrecord::PLFrecord(const vector<string>& p_fields)
//-----------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------
// record key
string SCOS::MIB::PLFrecord::key() const
//-----------------------------------------------------------------------------
{
  return plfName;
}

/////////////
// Manager //
/////////////

// global variables
SCOS::MIB::Manager* SCOS::MIB::Manager::s_instance = NULL;

//-----------------------------------------------------------------------------
SCOS::MIB::Manager::Manager()
//-----------------------------------------------------------------------------
{
  s_instance = this;
}

//-----------------------------------------------------------------------------
SCOS::MIB::Manager::~Manager()
//-----------------------------------------------------------------------------
{
  s_instance = NULL;
}

//-----------------------------------------------------------------------------
SCOS::MIB::Manager* SCOS::MIB::Manager::instance()
//-----------------------------------------------------------------------------
{
  return s_instance;
}
