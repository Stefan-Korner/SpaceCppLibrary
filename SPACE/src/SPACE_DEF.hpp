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
#ifndef SPACE_DEF_hpp
#define SPACE_DEF_hpp

#include <memory>
#include "SCOS_MIB.hpp"
#include "UTIL_VPP.hpp"

namespace SPACE
{
  namespace DEF
  {
    struct TMparamDef;
    struct TMpktDef;

    //-------------------------------------------------------------------------
    // Contains the data for a single raw value extraction
    struct TMparamToPkt
    //-------------------------------------------------------------------------
    {
      TMparamDef* paramDef;
      std::string paramName;
      TMpktDef* pktDef;
      int pktSPID;
      int locOffby;
      int locOffbi;
      int locNbocc;
      int locLgocc;

      TMparamToPkt(TMparamDef* p_paramDef,
                   TMpktDef* p_pktDef,
                   const SCOS::MIB::PLFrecord& p_plfRecord);
      // for debugging
      void dump(const std::string& prefix) const;
    };

    //-------------------------------------------------------------------------
    // Defines a dedicated parameter extraction in a packet
    struct TMparamExtraction
    //-------------------------------------------------------------------------
    {
      int bitPos;
      int bitWidth;
      std::string name;
      std::string descr;
      bool isInteger;
      int piValue;

      TMparamExtraction(int p_bitPos,
                        int p_bitWidth,
                        const std::string& p_name,
                        const std::string& p_descr,
                        bool p_isInteger,
                        int p_piValue=0);
      int compare(const TMparamExtraction& p_paramExtr) const;
      // for debugging
      void dump(const std::string& prefix) const;
    };

    // compare operators
    bool operator==(const TMparamExtraction& p_paramExtr1,
                    const TMparamExtraction& p_paramExtr2);
    bool operator!=(const TMparamExtraction& p_paramExtr1,
                    const TMparamExtraction& p_paramExtr2);
    bool operator< (const TMparamExtraction& p_paramExtr1,
                    const TMparamExtraction& p_paramExtr2);
    bool operator> (const TMparamExtraction& p_paramExtr1,
                    const TMparamExtraction& p_paramExtr2);
    bool operator<=(const TMparamExtraction& p_paramExtr1,
                    const TMparamExtraction& p_paramExtr2);
    bool operator>=(const TMparamExtraction& p_paramExtr1,
                    const TMparamExtraction& p_paramExtr2);

    //-------------------------------------------------------------------------
    // Contains the most important definition data of a TM packet
    struct TMpktDef
    //-------------------------------------------------------------------------
    {
      int pktSPID;
      std::string pktName;
      std::string pktDescr;
      int pktAPID;
      int pktType;
      int pktSType;
      int pktDFHsize;
      bool pktHasDFhdr;
      bool pktCheck;
      int pktPI1off;
      int pktPI1wid;
      int pktPI1val;
      int pktPI2off;
      int pktPI2wid;
      int pktPI2val;
      int pktSPsize;
      int pktS2Ksize;
      int pktSPDFsize;
      int pktSPDFdataSize;
      std::map<std::string, const TMparamToPkt*> paramLinks;
      int pktTPSD;
      UTIL::VPP::StructDef vppStructure;
      ssize_t vppTopLevelListBitOffset;
      size_t vppTopLevelListBitLength;

      TMpktDef();
      // for debugging
      void dump(const std::string& prefix) const;
      // used to append later on links to related parameters
      void appendParamLink(const TMparamToPkt* p_paramToPacket);
      // checks if two ranges overlap
      static bool rangeOverlap(int p_bitPos1,
                               int p_bitWidth1,
                               int p_bitPos2,
                               int p_bitWidth2);
      // returns a parameter extraction of a related parameters
      TMparamExtraction
      getParamExtraction(const std::string& p_paramName) const;
      // returns all parameter extractions, ordered by packet location
      std::list<TMparamExtraction> getParamExtractions() const;
    };

    //-------------------------------------------------------------------------
    // Contains the most important definition data of a TM parameter
    struct TMparamDef
    //-------------------------------------------------------------------------
    {
      std::string paramName;
      std::string paramDescr;
      int paramPtc;
      int paramPfc;
      int minCommutations;
      int maxCommutations;

      TMparamDef();
      int compare(const TMparamDef& p_paramDef) const;
      // for debugging
      void dump(const std::string& prefix) const;
      // returns the commutated param name
      std::string getCommutatedParamName(int p_commutation) const;
      // tells if the parameter is signed or unsigned integer
      bool isInteger();
      int getBitWidth() throw(UTIL::Exception);
    };

    // compare operators
    bool operator==(const TMparamDef& p_paramDef1,
                    const TMparamDef& p_paramDef2);
    bool operator!=(const TMparamDef& p_paramDef1,
                    const TMparamDef& p_paramDef2);
    bool operator< (const TMparamDef& p_paramDef1,
                    const TMparamDef& p_paramDef2);
    bool operator> (const TMparamDef& p_paramDef1,
                    const TMparamDef& p_paramDef2);
    bool operator<=(const TMparamDef& p_paramDef1,
                    const TMparamDef& p_paramDef2);
    bool operator>=(const TMparamDef& p_paramDef1,
                    const TMparamDef& p_paramDef2);

    //-------------------------------------------------------------------------
    // Manager for definition data
    class Definitions
    //-------------------------------------------------------------------------
    {
    public:
      // an instance of this class (or a derived class) shall
      // be created and destroyed in main()
      Definitions();
      virtual ~Definitions();

      // Definitions is a singleton
      static Definitions* instance();

      // initialise the definition data from the MIB
      void init() throw(UTIL::Exception);
/*
      // returns a TM packet definition
      const TMpktDef* getTMpktDefByIndex(int p_index) const;
*/
      // returns a TM packet definition
      const TMpktDef* getTMpktDefBySPID(int p_spid) const;
/*
      // returns the packet SPID for a packet name
      int getSPIDbyPktName(const std::string& p_name) const;
      // returns the TM packet definitions
      const std::list<const TMpktDef*> getTMpktDefs() const;
      // returns the TM parameter definitions
      const std::list<const TMparamDef*> getTMparamDefs() const;
*/
      void dumpDefinitions() const;

    protected:
      bool m_initialized;
      std::map<int, TMpktDef*> m_pktDefs;

    private:
      Definitions(const Definitions& p_service);
      const Definitions& operator=(const Definitions& p_task);

      static Definitions* s_instance;
    };
  }
}

#endif
