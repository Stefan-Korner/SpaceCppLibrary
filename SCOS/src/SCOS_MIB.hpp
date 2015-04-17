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

#include <string>
#include <vector>

namespace SCOS
{
  namespace MIB
  {
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
      int pidDFHsize;
      bool pidCheck;

      // initialise selected attributes from the record
      PIDrecord(const std::vector<std::string>& p_fields);
      // record key
      int key() const;
      // foreign key to PICrecord
      std::string picKey() const;

    private:
      PIDrecord();
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

      // initialise selected attributes from the record
      PICrecord(const std::vector<std::string>& p_fields);
      // record key
      std::string key() const;

    private:
      PICrecord();
    };

    //-------------------------------------------------------------------------
    // MIB record from tpcf.dat
    struct TPCFrecord
    //-------------------------------------------------------------------------
    {
      int tpcfSPID;
      std::string tpcfName;
      int tpcfSize;

      // initialise selected attributes from the record
      TPCFrecord(const std::vector<std::string>& p_fields);
      // record key
      int key() const;

    private:
      TPCFrecord();
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

      // initialise selected attributes from the record
      PCFrecord(const std::vector<std::string>& p_fields);
      // record key
      std::string key() const;

    private:
      PCFrecord();
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

      // initialise selected attributes from the record
      PLFrecord(const std::vector<std::string>& p_fields);
      // record key
      std::string key() const;

    private:
      PLFrecord();
    };

    //-------------------------------------------------------------------------
    class Manager
    //-------------------------------------------------------------------------
    {
    public:
      // the manager (or a derived class) shall
      // be created and destroyed in main()
      Manager();
      virtual ~Manager();

      // the manager is a singleton
      static Manager* instance();

    private:
      Manager(const Manager& p_service);
      const Manager& operator=(const Manager& p_task);

      static Manager* s_instance;
    };
  }
}

#endif
