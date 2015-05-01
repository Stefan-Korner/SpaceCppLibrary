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
// Space Simulation - Space Data Definitions                                  *
//*****************************************************************************
#include "SPACE_DEF.hpp"

#include <iostream>
#include "SCOS_MIB.hpp"
#include "UTIL_STRING.hpp"

using namespace std;

#define DUMP_MIB
#define DUMP_DEF

/////////////////
// Definitions //
/////////////////

//-----------------------------------------------------------------------------
SPACE::DEF::TMpktDef::TMpktDef():
  pktSPID(-1),
  pktAPID(-1),
  pktType(-1),
  pktSType(-1),
  pktDFHsize(-1),
  pktHasDFhdr(false),
  pktCheck(false),
  pktPI1off(-1),
  pktPI1wid(-1),
  pktPI1val(-1),
  pktPI2off(-1),
  pktPI2wid(-1),
  pktPI2val(-1),
  pktSPsize(-1),
  pktS2Ksize(-1),
  pktSPDFsize(-1),
  pktSPDFdataSize(-1),
  pktTPSD(-1),
  vppStructure("vppStructure")
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
void SPACE::DEF::TMpktDef::dump(const string& prefix) const
//-----------------------------------------------------------------------------
{
  cout << prefix << ".pktSPID = " << pktSPID << endl;
  cout << prefix << ".pktAPID = " << pktAPID << endl;
  cout << prefix << ".pktType = " << pktType << endl;
  cout << prefix << ".pktSType = " << pktSType << endl;
  cout << prefix << ".pktDFHsize = " << pktDFHsize << endl;
  cout << prefix << ".pktHasDFhdr = " << pktHasDFhdr << endl;
  cout << prefix << ".pktCheck = " << pktCheck << endl;
  cout << prefix << ".pktPI1off = " << pktPI1off << endl;
  cout << prefix << ".pktPI1wid = " << pktPI1wid << endl;
  cout << prefix << ".pktPI1val = " << pktPI1val << endl;
  cout << prefix << ".pktPI2off = " << pktPI2off << endl;
  cout << prefix << ".pktPI2wid = " << pktPI2wid << endl;
  cout << prefix << ".pktPI2val = " << pktPI2val << endl;
  cout << prefix << ".pktSPsize = " << pktSPsize << endl;
  cout << prefix << ".pktS2Ksize = " << pktS2Ksize << endl;
  cout << prefix << ".pktSPDFsize = " << pktSPDFsize << endl;
  cout << prefix << ".pktSPDFdataSize = " << pktSPDFdataSize << endl;
  cout << prefix << ".pktTPSD = " << pktTPSD << endl;
  if(pktTPSD > 0)
  {
    vppStructure.dump(prefix);
  }
}

// global variables
SPACE::DEF::Definitions* SPACE::DEF::Definitions::s_instance = NULL;

//-----------------------------------------------------------------------------
SPACE::DEF::Definitions::Definitions()
//-----------------------------------------------------------------------------
{
  s_instance = this;
}

//-----------------------------------------------------------------------------
SPACE::DEF::Definitions::~Definitions()
//-----------------------------------------------------------------------------
{
  s_instance = NULL;
}

//-----------------------------------------------------------------------------
SPACE::DEF::Definitions* SPACE::DEF::Definitions::instance()
//-----------------------------------------------------------------------------
{
  return s_instance;
}

//-----------------------------------------------------------------------------
int getBitWidth(int p_ptc, int p_pfc) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  switch(p_ptc)
  {
  case 1:
    if(p_pfc == 0)
    {
      // unsigned integer (boolean parameter)
      return 1;
    }
    break;
  case 2:
    if(p_pfc <= 32)
    {
      // unsigned integer (enumeration parameter)
      return p_pfc;
    }
    break;
  case 3:
    // unsigned integer
    if(p_pfc <= 12)
    {
      return p_pfc + 4;
    }
    else if(p_pfc == 13)
    {
      return 24;
    }
    else if(p_pfc == 14)
    {
      return 32;
    }
    else if(p_pfc == 15)
    {
      // not supported by SCOS-2000
      return 48;
    }
    else if(p_pfc == 16)
    {
      // not supported by SCOS-2000
      return 64;
    }
    break;
  case 4:
    // signed integer
    if(p_pfc <= 12)
    {
      return p_pfc + 4;
    }
    else if(p_pfc == 13)
    {
      return 24;
    }
    else if(p_pfc == 14)
    {
      return 32;
    }
    else if(p_pfc == 15)
    {
      // not supported by SCOS-2000
      return 48;
    }
    else if(p_pfc == 16)
    {
      // not supported by SCOS-2000
      return 64;
    }
    break;
  case 5:
    // floating point
    if(p_pfc == 1)
    {
      // simple precision real (IEEE)
      return 32;
    }
    else if(p_pfc == 2)
    {
      // double precision real (IEEE)
      return 64;
    }
    else if(p_pfc == 3)
    {
      // simple precision real (MIL 1750A)
      return 32;
    }
    else if(p_pfc == 4)
    {
      // extended precision real (MIL 1750a)
      return 48;
    }
    break;
  case 6:
    // bit string
    if(p_pfc == 0)
    {
      // variable bit string, not supported by SCOS-2000
      break;
    }
    else if(p_pfc <= 32)
    {
      // fixed length bit strings, unsigned integer in SCOS-2000
      return p_pfc;
    }
    break;
  case 7:
    // octet string
    if(p_pfc == 0)
    {
      // variable octet string, not supported by SCOS-2000 TM
      break;
    }
    else
    {
      // fixed length octet strings
      return p_pfc * 8;
    }
    break;
  case 8:
    // ASCII string
    if(p_pfc == 0)
    {
      // variable ASCII string, not supported by SCOS-2000 TM
      break;
    }
    else
    {
      // fixed length ASCII strings
      return p_pfc * 8;
    }
    break;
  case 9:
    // absolute time
    if(p_pfc == 0)
    {
      // variable length, not supported by SCOS-2000 TM
      break;
    }
    else if(p_pfc == 1)
    {
      // CDS format, without microseconds
      return 48;
    }
    else if(p_pfc == 2)
    {
      // CDS format, with microseconds
      return 64;
    }
    else if(p_pfc <= 6)
    {
      // CUC format, 1st octet coarse time, 2nd - n-th octet for fine time
      return (p_pfc - 2) * 8;
    }
    else if(p_pfc <= 10)
    {
      // CUC format, 1st & 2nd octet coarse time, 3rd - n-th octet for fine time
      return (p_pfc - 5) * 8;
    }
    else if(p_pfc <= 14)
    {
      // CUC format, 1st - 3rd octet coarse time, 4rd - n-th octet for fine time
      return (p_pfc - 8) * 8;
    }
    else if(p_pfc <= 18)
    {
      // CUC format, 1st - 4th octet coarse time, 5rd - n-th octet for fine time
      return (p_pfc - 11) * 8;
    }
    break;
  case 10:
    // relative time
    if(p_pfc <= 2)
    {
      // not used
      break;
    }
    else if(p_pfc <= 6)
    {
      // CUC format, 1st octet coarse time, 2nd - n-th octet for fine time
      return (p_pfc - 2) * 8;
    }
    else if(p_pfc <= 10)
    {
      // CUC format, 1st & 2nd octet coarse time, 3rd - n-th octet for fine time
      return (p_pfc - 5) * 8;
    }
    else if(p_pfc <= 14)
    {
      // CUC format, 1st - 3rd octet coarse time, 4rd - n-th octet for fine time
      return (p_pfc - 8) * 8;
    }
    else if(p_pfc <= 18)
    {
      // CUC format, 1st - 4th octet coarse time, 5rd - n-th octet for fine time
      return (p_pfc - 11) * 8;
    }
    break;
  case 11:
    // deduced parameter, N/A
    break;
  case 13:
    // saved synthetic parameter, N/A
    break;
  }
  // illegal ptc/pfc combination
  string errorMessage("ptc/pfc combination ");
  errorMessage += UTIL::STRING::str(p_ptc);
  errorMessage += "/";
  errorMessage += UTIL::STRING::str(p_pfc);
  errorMessage += " not supported";
  throw UTIL::Exception(errorMessage);
}

//-----------------------------------------------------------------------------
// initialise the definition data from file or MIB
void SPACE::DEF::Definitions::init() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  SCOS::MIB::PIDmap pidMap;
  SCOS::MIB::PICmap picMap;
  SCOS::MIB::TPCFmap tpcfMap;
  SCOS::MIB::PCFmap pcfMap;
  SCOS::MIB::PLFmap plfMap;
  SCOS::MIB::VPDmap vpdMap;
  SCOS::MIB::readTable(pidMap);
  SCOS::MIB::readTable(picMap);
  SCOS::MIB::readTable(tpcfMap);
  SCOS::MIB::readTable(pcfMap);
  SCOS::MIB::readTable(plfMap);
  SCOS::MIB::readTable(vpdMap);
#ifdef DUMP_MIB
  SCOS::MIB::dumpTable(pidMap);
  SCOS::MIB::dumpTable(picMap);
  SCOS::MIB::dumpTable(tpcfMap);
  SCOS::MIB::dumpTable(pcfMap);
  SCOS::MIB::dumpTable(plfMap);
  SCOS::MIB::dumpTable(vpdMap);
#endif
  // create the packets with (optional) variable packet definition
  for(SCOS::MIB::PIDmap::iterator pidIter = pidMap.begin();
      pidIter != pidMap.end();
      pidIter++)
  {
    int spid = pidIter->first;
    SCOS::MIB::PIDrecord& pidRecord = pidIter->second;
    SPACE::DEF::TMpktDef* tmPktDef = new SPACE::DEF::TMpktDef;
    tmPktDef->pktSPID = pidRecord.pidSPID;
    tmPktDef->pktName = "###"; // take from tpcfRecord
    tmPktDef->pktDescr = pidRecord.pidDescr;
    tmPktDef->pktAPID = pidRecord.pidAPID;
    tmPktDef->pktType = pidRecord.pidType;
    tmPktDef->pktSType = pidRecord.pidSType;
    tmPktDef->pktDFHsize = pidRecord.pidDFHsize;
    tmPktDef->pktHasDFhdr = pidRecord.pidDFHsize > 6;
    tmPktDef->pktCheck = pidRecord.pidCheck;
    // fill the attributes below from picRecord
    tmPktDef->pktPI1off = -1;
    tmPktDef->pktPI1wid = -1;
    tmPktDef->pktPI1val = -1;
    tmPktDef->pktPI2off = -1;
    tmPktDef->pktPI2wid = -1;
    tmPktDef->pktPI2val = -1;
    // fill the attributes below from environment info
    tmPktDef->pktSPsize = -1;
    tmPktDef->pktS2Ksize = -1;
    tmPktDef->pktSPDFsize = -1;
    tmPktDef->pktSPDFdataSize = -1;
    // fill the attibute below later on
    //std::map<std::string, const TMparamToPkt*> paramLinks;
    // fill the variable packet structure
    tmPktDef->pktTPSD = pidRecord.pidTPSD;
    if(tmPktDef->pktTPSD > 0)
    {
      SCOS::MIB::VPDmap::iterator vpdIter = vpdMap.find(tmPktDef->pktTPSD);
      if(vpdIter == vpdMap.end())
      {
        string errorMessage("missing VPD entries for packet ");
        errorMessage += tmPktDef->pktName;
        errorMessage += "(";
        errorMessage += UTIL::STRING::str(spid);
        errorMessage += ")";
        throw UTIL::Exception(errorMessage);
      }
      list<SCOS::MIB::VPDrecord>& vpdEntries = vpdIter->second;
      size_t startPos = 0;
      for(list<SCOS::MIB::VPDrecord>::iterator vpdEntriesIter =
            vpdEntries.begin();
          vpdEntriesIter != vpdEntries.end();
          vpdEntriesIter++)
      {
        SCOS::MIB::VPDrecord& vpdRecord = *vpdEntriesIter;
        string paramName = vpdRecord.vpdName;
        // take the related TM parameter definition for details
        SCOS::MIB::PCFmap::iterator pcfIter = pcfMap.find(paramName);
        if(pcfIter == pcfMap.end())
        {
          throw UTIL::Exception("missing PCF entriy for parameter " +
                                paramName);
        }
        SCOS::MIB::PCFrecord& pcfRecord = pcfIter->second;
        int bitWidth = getBitWidth(pcfRecord.pcfPtc, pcfRecord.pcfPfc);
        int bitOffset = vpdRecord.vpdOffset;
        UTIL::VPP::FieldDef* fieldDef =
          new UTIL::VPP::FieldDef(paramName,
                                  UTIL::VPP::FieldDef::ANY_FIELD,
                                  bitOffset,
                                  bitWidth);
        tmPktDef->vppStructure.addAttributeDef(fieldDef);
      }
    }
    m_pktDefs[spid] = tmPktDef;
  }
#ifdef DUMP_DEF
  for(map<int, TMpktDef*>::iterator pktDefIter = m_pktDefs.begin();
      pktDefIter != m_pktDefs.end();
      pktDefIter++)
  {
    string prefix("m_pktDefs[");
    prefix += UTIL::STRING::str(pktDefIter->first);
    prefix += "]";
    SPACE::DEF::TMpktDef* tmPktDef = pktDefIter->second;
    tmPktDef->dump(prefix);
  }
#endif
}
