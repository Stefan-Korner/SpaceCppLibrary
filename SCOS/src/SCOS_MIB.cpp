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
#include <sstream>
#include "SCOS_ENV.hpp"
#include "UTIL_STRING.hpp"

using namespace std;
using namespace UTIL::STRING;

///////////////
// PIDrecord //
///////////////

//-----------------------------------------------------------------------------
SCOS::MIB::PIDrecord::PIDrecord():
  pidType(-1),
  pidSType(-1),
  pidAPID(-1),
  pidPI1(-1),
  pidPI2(-1),
  pidSPID(-1),
  pidDescr(),
  pidTPSD(-1),
  pidDFHsize(-1),
  pidCheck(false)
//-----------------------------------------------------------------------------
{}

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
  pidTPSD(asInt(p_fields[8])),
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

//-----------------------------------------------------------------------------
// for debugging
void SCOS::MIB::PIDrecord::dump(const string& prefix) const
//-----------------------------------------------------------------------------
{
  cout << prefix << ".pidType = " << pidType << endl;
  cout << prefix << ".pidSType = " << pidSType << endl;
  cout << prefix << ".pidAPID = " << pidAPID << endl;
  cout << prefix << ".pidPI1 = " << pidPI1 << endl;
  cout << prefix << ".pidPI2 = " << pidPI2 << endl;
  cout << prefix << ".pidSPID = " << pidSPID << endl;
  cout << prefix << ".pidDescr = " << pidDescr << endl;
  cout << prefix << ".pidTPSD = " << pidTPSD << endl;
  cout << prefix << ".pidDFHsize = " << pidDFHsize << endl;
  cout << prefix << ".pidCheck = " << pidCheck << endl;
}

///////////////
// PICrecord //
///////////////

//-----------------------------------------------------------------------------
SCOS::MIB::PICrecord::PICrecord():
  picType(-1),
  picSType(-1),
  picPI1off(-1),
  picPI1wid(-1),
  picPI2off(-1),
  picPI2wid(-1)
//-----------------------------------------------------------------------------
{}

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

//-----------------------------------------------------------------------------
// for debugging
void SCOS::MIB::PICrecord::dump(const string& prefix) const
//-----------------------------------------------------------------------------
{
  cout << prefix << ".picType = " << picType << endl;
  cout << prefix << ".picSType = " << picSType << endl;
  cout << prefix << ".picPI1off = " << picPI1off << endl;
  cout << prefix << ".picPI1wid = " << picPI1wid << endl;
  cout << prefix << ".picPI2off = " << picPI2off << endl;
  cout << prefix << ".picPI2wid = " << picPI2wid << endl;
}

////////////////
// TPCFrecord //
////////////////

//-----------------------------------------------------------------------------
SCOS::MIB::TPCFrecord::TPCFrecord():
  tpcfSPID(-1),
  tpcfName(),
  tpcfSize(-1)
//-----------------------------------------------------------------------------
{}

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

//-----------------------------------------------------------------------------
// for debugging
void SCOS::MIB::TPCFrecord::dump(const string& prefix) const
//-----------------------------------------------------------------------------
{
  cout << prefix << ".tpcfSPID = " << tpcfSPID << endl;
  cout << prefix << ".tpcfName = " << tpcfName << endl;
  cout << prefix << ".tpcfSize = " << tpcfSize << endl;
}

///////////////
// PCFrecord //
///////////////

//-----------------------------------------------------------------------------
SCOS::MIB::PCFrecord::PCFrecord():
  pcfName(),
  pcfDescr(),
  pcfPtc(-1),
  pcfPfc(-1)
//-----------------------------------------------------------------------------
{}

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

//-----------------------------------------------------------------------------
// for debugging
void SCOS::MIB::PCFrecord::dump(const string& prefix) const
//-----------------------------------------------------------------------------
{
  cout << prefix << ".pcfName = " << pcfName << endl;
  cout << prefix << ".pcfDescr = " << pcfDescr << endl;
  cout << prefix << ".pcfPtc = " << pcfPtc << endl;
  cout << prefix << ".pcfPfc = " << pcfPfc << endl;
}

///////////////
// PLFrecord //
///////////////

//-----------------------------------------------------------------------------
SCOS::MIB::PLFrecord::PLFrecord():
  plfName(),
  plfSPID(-1),
  plfOffby(-1),
  plfOffbi(-1),
  plfNbocc(),
  plfLgocc()
//-----------------------------------------------------------------------------
{}

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

//-----------------------------------------------------------------------------
// for debugging
void SCOS::MIB::PLFrecord::dump(const string& prefix) const
//-----------------------------------------------------------------------------
{
  cout << prefix << ".plfName = " << plfName << endl;
  cout << prefix << ".plfSPID = " << plfSPID << endl;
  cout << prefix << ".plfOffby = " << plfOffby << endl;
  cout << prefix << ".plfOffbi = " << plfOffbi << endl;
  cout << prefix << ".plfNbocc = " << plfNbocc << endl;
  cout << prefix << ".plfLgocc = " << plfLgocc << endl;
}

///////////////
// VPDrecord //
///////////////

//-----------------------------------------------------------------------------
SCOS::MIB::VPDrecord::VPDrecord():
  vpdTPSD(-1),
  vpdPos(-1),
  vpdName(),
  vpdGrpSize(-1),
  vpdFixRep(-1),
  vpdOffset(-1)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
// initialise selected attributes from the record
SCOS::MIB::VPDrecord::VPDrecord(const vector<string>& p_fields):
  vpdTPSD(asInt(p_fields[0])),
  vpdPos(asInt(p_fields[1])),
  vpdName(p_fields[2]),
  vpdGrpSize(asInt(p_fields[3])),
  vpdFixRep(asInt(p_fields[4])),
  vpdOffset(asInt(p_fields[13]))
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
// record key
int SCOS::MIB::VPDrecord::key() const
//-----------------------------------------------------------------------------
{
  return vpdTPSD;
}

//-----------------------------------------------------------------------------
// for debugging
void SCOS::MIB::VPDrecord::dump(const string& prefix) const
//-----------------------------------------------------------------------------
{
  cout << prefix << ".vpdTPSD = " << vpdTPSD << endl;
  cout << prefix << ".vpdPos = " << vpdPos << endl;
  cout << prefix << ".vpdName = " << vpdName << endl;
  cout << prefix << ".vpdGrpSize = " << vpdGrpSize << endl;
  cout << prefix << ".vpdFixRep = " << vpdFixRep << endl;
  cout << prefix << ".vpdOffset = " << vpdOffset << endl;
}

//////////////
// funtions //
//////////////

//-----------------------------------------------------------------------------
template<typename KEY, typename REC>
void readUniqueKeyTable(const char* p_tableName,
                        int p_minFieldNr,
                        map<KEY, REC>& p_map) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  string tableFilePath = SCOS::ENV::Environment::instance()->mibDir();
  tableFilePath += "/";
  tableFilePath += p_tableName;
  list<string> tableFileContents;
  readTextFile(tableFilePath.c_str(), tableFileContents);
  p_map.clear();
  int lineNr = 1;
  for(list<string>::iterator lineIter = tableFileContents.begin();
      lineIter != tableFileContents.end();
      lineIter++)
  {
    // tab separated table
    vector<string> fields;
    split((*lineIter), "\t", fields);
    if(fields.size() < p_minFieldNr)
    {
      string errorMessage = p_tableName;
      errorMessage += ": line ";
      errorMessage += str(lineNr);
      errorMessage += " has wrong structure";
      throw UTIL::Exception(errorMessage);
    }
    REC record(fields);
    KEY key = record.key();
    typename map<KEY, REC>::iterator findIter = p_map.find(key);
    if(findIter != p_map.end())
    {
      ostringstream errorOstr;
      errorOstr << p_tableName
                << ": multiple records assigned for key "
                << key;
      throw UTIL::Exception(errorOstr.str());
    }
    p_map[key] = record;
    lineNr ++;
  }
}

//-----------------------------------------------------------------------------
template<typename KEY, typename REC>
void readMultiKeyTable(const char* p_tableName,
                       int p_minFieldNr,
                       map<KEY, list<REC> >& p_map) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  string tableFilePath = SCOS::ENV::Environment::instance()->mibDir();
  tableFilePath += "/";
  tableFilePath += p_tableName;
  list<string> tableFileContents;
  readTextFile(tableFilePath.c_str(), tableFileContents);
  p_map.clear();
  int lineNr = 1;
  for(list<string>::iterator lineIter = tableFileContents.begin();
      lineIter != tableFileContents.end();
      lineIter++)
  {
    // tab separated table
    vector<string> fields;
    split((*lineIter), "\t", fields);
    if(fields.size() < p_minFieldNr)
    {
      string errorMessage = p_tableName;
      errorMessage += ": line ";
      errorMessage += str(lineNr);
      errorMessage += " has wrong structure";
      throw UTIL::Exception(errorMessage);
    }
    REC record(fields);
    KEY key = record.key();
    // multiple keys allowed ---> use a list for all records with same key
    p_map[key].push_back(record);
    lineNr ++;
  }
}

//-----------------------------------------------------------------------------
template<typename KEY, typename REC>
void dumpUniqueKeyTable(const char* p_tableName,
                        const map<KEY, REC>& p_map)
//-----------------------------------------------------------------------------
{
  for(typename map<KEY, REC>::const_iterator mapIter = p_map.begin();
      mapIter != p_map.end();
      mapIter++)
  {
    ostringstream dumpOstr;
    dumpOstr << p_tableName
             << "["
             << (mapIter->first)
             << "]";
    mapIter->second.dump(dumpOstr.str());
  }
}

//-----------------------------------------------------------------------------
template<typename KEY, typename REC>
void dumpMultiKeyTable(const char* p_tableName,
                       const map<KEY, list<REC> >& p_map)
//-----------------------------------------------------------------------------
{
  for(typename map<KEY, list<REC> >::const_iterator mapIter = p_map.begin();
      mapIter != p_map.end();
      mapIter++)
  {
    ostringstream dumpOstr;
    dumpOstr << p_tableName
             << "["
             << (mapIter->first)
             << "]";
    for(typename list<REC>::const_iterator listIter = mapIter->second.begin();
        listIter != mapIter->second.end();
        listIter++)
    {
      listIter->dump(dumpOstr.str());
    }
  }
}

//-----------------------------------------------------------------------------
void SCOS::MIB::readTable(SCOS::MIB::PIDmap& p_map) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  readUniqueKeyTable("pid.dat", 14, p_map);
}

//-----------------------------------------------------------------------------
void SCOS::MIB::readTable(SCOS::MIB::PICmap& p_map) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  readUniqueKeyTable("pic.dat", 6, p_map);
}

//-----------------------------------------------------------------------------
void SCOS::MIB::readTable(SCOS::MIB::TPCFmap& p_map) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  readUniqueKeyTable("tpcf.dat", 3, p_map);
}

//-----------------------------------------------------------------------------
void SCOS::MIB::readTable(SCOS::MIB::PCFmap& p_map) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  readUniqueKeyTable("pcf.dat", 6, p_map);
}

//-----------------------------------------------------------------------------
void SCOS::MIB::readTable(SCOS::MIB::PLFmap& p_map) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  readMultiKeyTable("plf.dat", 6, p_map);
}

//-----------------------------------------------------------------------------
void SCOS::MIB::readTable(SCOS::MIB::VPDmap& p_map) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  readMultiKeyTable("vpd.dat", 14, p_map);
}

//-----------------------------------------------------------------------------
void SCOS::MIB::dumpTable(const SCOS::MIB::PIDmap& p_map)
//-----------------------------------------------------------------------------
{
  dumpUniqueKeyTable("PIDmap", p_map);
}

//-----------------------------------------------------------------------------
void SCOS::MIB::dumpTable(const SCOS::MIB::PICmap& p_map)
//-----------------------------------------------------------------------------
{
  dumpUniqueKeyTable("PICmap", p_map);
}

//-----------------------------------------------------------------------------
void SCOS::MIB::dumpTable(const SCOS::MIB::TPCFmap& p_map)
//-----------------------------------------------------------------------------
{
  dumpUniqueKeyTable("TPCFmap", p_map);
}

//-----------------------------------------------------------------------------
void SCOS::MIB::dumpTable(const SCOS::MIB::PCFmap& p_map)
//-----------------------------------------------------------------------------
{
  dumpUniqueKeyTable("PCFmap", p_map);
}

//-----------------------------------------------------------------------------
void SCOS::MIB::dumpTable(const SCOS::MIB::PLFmap& p_map)
//-----------------------------------------------------------------------------
{
  dumpMultiKeyTable("PLFmap", p_map);
}

//-----------------------------------------------------------------------------
void SCOS::MIB::dumpTable(const SCOS::MIB::VPDmap& p_map)
//-----------------------------------------------------------------------------
{
  dumpMultiKeyTable("VPDmap", p_map);
}

/////////////
// Manager //
/////////////

// global variables
SCOS::MIB::Manager* SCOS::MIB::Manager::s_instance = NULL;

//-----------------------------------------------------------------------------
SCOS::MIB::Manager::Manager(): m_initialized(false)
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

//-----------------------------------------------------------------------------
// initialise the MIB tables
void SCOS::MIB::Manager::init() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(m_initialized)
  {
    throw UTIL::Exception("SCOS::MIB::Manager already initialized");
  }
  SCOS::MIB::readTable(m_pidMap);
  SCOS::MIB::readTable(m_picMap);
  SCOS::MIB::readTable(m_tpcfMap);
  SCOS::MIB::readTable(m_pcfMap);
  SCOS::MIB::readTable(m_plfMap);
  SCOS::MIB::readTable(m_vpdMap);
  m_initialized = true;
}

//-----------------------------------------------------------------------------
const SCOS::MIB::PIDmap& SCOS::MIB::Manager::getPIDmap() const
//-----------------------------------------------------------------------------
{
  return m_pidMap;
}

//-----------------------------------------------------------------------------
const SCOS::MIB::PICmap& SCOS::MIB::Manager::getPICmap() const
//-----------------------------------------------------------------------------
{
  return m_picMap;
}

//-----------------------------------------------------------------------------
const SCOS::MIB::TPCFmap& SCOS::MIB::Manager::getTPCFmap() const
//-----------------------------------------------------------------------------
{
  return m_tpcfMap;
}

//-----------------------------------------------------------------------------
const SCOS::MIB::PCFmap& SCOS::MIB::Manager::getPCFmap() const
//-----------------------------------------------------------------------------
{
  return m_pcfMap;
}

//-----------------------------------------------------------------------------
const SCOS::MIB::PLFmap& SCOS::MIB::Manager::getPLFmap() const
//-----------------------------------------------------------------------------
{
  return m_plfMap;
}

//-----------------------------------------------------------------------------
const SCOS::MIB::VPDmap& SCOS::MIB::Manager::getVPDmap() const
//-----------------------------------------------------------------------------
{
  return m_vpdMap;
}

//-----------------------------------------------------------------------------
void SCOS::MIB::Manager::dumpMIBtables() const
//-----------------------------------------------------------------------------
{
  SCOS::MIB::dumpTable(m_pidMap);
  SCOS::MIB::dumpTable(m_picMap);
  SCOS::MIB::dumpTable(m_tpcfMap);
  SCOS::MIB::dumpTable(m_pcfMap);
  SCOS::MIB::dumpTable(m_plfMap);
  SCOS::MIB::dumpTable(m_vpdMap);
}
