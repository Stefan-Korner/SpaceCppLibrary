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
#ifndef SCOS_MIB_hpp
#define SCOS_MIB_hpp

#include <list>
#include <map>
#include <vector>
#include "UTIL_EXCEPTION.hpp"

namespace SCOS
{
  namespace MIB
  {
    /////////////
    // structs //
    /////////////

    //-------------------------------------------------------------------------
    // MIB record from pid.dat
    struct PIDrecord
    //-------------------------------------------------------------------------
    {
      int pidType;
      int pidSType;
      int pidAPID;
      int pidPI1;
      int pidPI2;
      int pidSPID;
      std::string pidDescr;
      int pidTPSD;
      int pidDFHsize;
      bool pidCheck;

      PIDrecord();
      // initialise selected attributes from the record
      PIDrecord(const std::vector<std::string>& p_fields);
      // record key
      int key() const;
      // foreign key to PICrecord
      std::string picKey() const;
      // for debugging
      void dump(const std::string& prefix) const;
    };

    //-------------------------------------------------------------------------
    // MIB record from pic.dat
    struct PICrecord
    //-------------------------------------------------------------------------
    {
      int picType;
      int picSType;
      int picPI1off;
      int picPI1wid;
      int picPI2off;
      int picPI2wid;

      PICrecord();
      // initialise selected attributes from the record
      PICrecord(const std::vector<std::string>& p_fields);
      // record key
      std::string key() const;
      // for debugging
      void dump(const std::string& prefix) const;
    };

    //-------------------------------------------------------------------------
    // MIB record from tpcf.dat
    struct TPCFrecord
    //-------------------------------------------------------------------------
    {
      int tpcfSPID;
      std::string tpcfName;
      int tpcfSize;

      TPCFrecord();
      // initialise selected attributes from the record
      TPCFrecord(const std::vector<std::string>& p_fields);
      // record key
      int key() const;
      // for debugging
      void dump(const std::string& prefix) const;
    };

    //-------------------------------------------------------------------------
    // MIB record from pcf.dat
    struct PCFrecord
    //-------------------------------------------------------------------------
    {
      std::string pcfName;
      std::string pcfDescr;
      int pcfPtc;
      int pcfPfc;

      PCFrecord();
      // initialise selected attributes from the record
      PCFrecord(const std::vector<std::string>& p_fields);
      // record key
      std::string key() const;
      // for debugging
      void dump(const std::string& prefix) const;
    };

    //-------------------------------------------------------------------------
    // MIB record from plf.dat
    struct PLFrecord
    //-------------------------------------------------------------------------
    {
      std::string plfName;
      int plfSPID;
      int plfOffby;
      int plfOffbi;
      // keep the strigified value, because it could be empty
      std::string plfNbocc;
      std::string plfLgocc;

      PLFrecord();
      // initialise selected attributes from the record
      PLFrecord(const std::vector<std::string>& p_fields);
      // record key
      std::string key() const;
      // for debugging
      void dump(const std::string& prefix) const;
    };

    //-------------------------------------------------------------------------
    // MIB record from vpd.dat
    struct VPDrecord
    //-------------------------------------------------------------------------
    {
      int vpdTPSD;
      int vpdPos;
      std::string vpdName;
      int vpdGrpSize;
      int vpdFixRep;
      int vpdOffset;

      VPDrecord();
      // initialise selected attributes from the record
      VPDrecord(const std::vector<std::string>& p_fields);
      // record key
      int key() const;
      // for debugging
      void dump(const std::string& prefix) const;
    };

    typedef std::map<int, PIDrecord> PIDmap;
    typedef std::map<std::string, PICrecord> PICmap;
    typedef std::map<int, TPCFrecord> TPCFmap;
    typedef std::map<std::string, PCFrecord> PCFmap;
    typedef std::map<std::string, std::list<PLFrecord> > PLFmap;
    typedef std::map<int, std::list<VPDrecord> > VPDmap;

    ///////////////
    // functions //
    ///////////////

    // Reads a MIB table
    void readTable(PIDmap& p_map) throw(UTIL::Exception);
    void readTable(PICmap& p_map) throw(UTIL::Exception);
    void readTable(TPCFmap& p_map) throw(UTIL::Exception);
    void readTable(PCFmap& p_map) throw(UTIL::Exception);
    void readTable(PLFmap& p_map) throw(UTIL::Exception);
    void readTable(VPDmap& p_map) throw(UTIL::Exception);

    // Dumps a MIB table
    void dumpTable(const PIDmap& p_map);
    void dumpTable(const PICmap& p_map);
    void dumpTable(const TPCFmap& p_map);
    void dumpTable(const PCFmap& p_map);
    void dumpTable(const PLFmap& p_map);
    void dumpTable(const VPDmap& p_map);
  }
}

#endif
