//*****************************************************************************
// (C) 2014, Stefan Korner, Austria                                           *
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
// PUS Services - Services Module                                             *
//*****************************************************************************
#ifndef PUS_SERVICES_hpp
#define PUS_SERVICES_hpp

#include "CCSDS_TIME.hpp"
#include "PUS_PACKET.hpp"

#include <map>

namespace PUS
{
  namespace SERVICES
  {
    //-------------------------------------------------------------------------
    class Service1
    //-------------------------------------------------------------------------
    {
    public:
      // the service (or a derived class) shall
      // be created and destroyed in main()
      Service1();
      virtual ~Service1();

      // the service is a singleton
      static Service1* instance();

      // create TM response to TC
      PUS::PACKET::TMpacket* respond(const PUS::PACKET::TCpacket& p_tcPkt,
                                     uint8_t p_subType);

    protected:
      // APID is key
      std::map<uint32_t, uint16_t> m_sequCtrlCounters;
      // position of the time field in the TM response
      size_t m_timePos;
      // type of the time field in the TM response
      CCSDS::CUC::TimeCode m_timeCode;
      // position of the TC header in the TM response
      size_t m_tcHeaderPos;

    private:
      Service1(const Service1& p_service);
      const Service1& operator=(const Service1& p_task);

      static Service1* s_instance;
    };
  }
}

#endif
