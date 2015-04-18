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
SCOS::MIB::PICrecord::PICrecord(const vector<string>& p_fields):
  picType(asInt(p_fields[0])),
  picSType(asInt(p_fields[1])),
  picPI1off(asInt(p_fields[2])),
  picPI1wid(asInt(p_fields[3])),
  picPI2off(asInt(p_fields[4])),
  picPI2wid(asInt(p_fields[5]))
//-----------------------------------------------------------------------------
{}

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
SCOS::MIB::TPCFrecord::TPCFrecord(const vector<string>& p_fields):
  tpcfSPID(asInt(p_fields[0])),
  tpcfName(p_fields[1]),
  tpcfSize(asInt(p_fields[2]))
//-----------------------------------------------------------------------------
{}

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
SCOS::MIB::PCFrecord::PCFrecord(const vector<string>& p_fields):
  pcfName(p_fields[0]),
  pcfDescr(p_fields[1]),
  pcfPtc(asInt(p_fields[4])),
  pcfPfc(asInt(p_fields[5]))
//-----------------------------------------------------------------------------
{}

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
SCOS::MIB::PLFrecord::PLFrecord(const vector<string>& p_fields):
  plfName(p_fields[0]),
  plfSPID(asInt(p_fields[1])),
  plfOffby(asInt(p_fields[2])),
  plfOffbi(asInt(p_fields[3])),
  plfNbocc(p_fields[4]),
  plfLgocc(p_fields[5])
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
// record key
string SCOS::MIB::PLFrecord::key() const
//-----------------------------------------------------------------------------
{
  return plfName;
}

//////////////
// funtions //
//////////////

