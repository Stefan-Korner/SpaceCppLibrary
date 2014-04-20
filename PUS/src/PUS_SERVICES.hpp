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
    // constants
    static const size_t DEFAULT_TIME_BYTE_POS = 9;
    static const uint32_t DEFAULT_TIME_FORMAT = CCSDS::CUC::L2_TIME_4_3;

    namespace S1
    {
      static const size_t DEFAULT_TC_HEADER_BYTE_POS = 16;
      static const size_t DEFAULT_TM_1_1_BYTE_SIZE = 22;
      static const size_t DEFAULT_TM_1_2_BYTE_SIZE = 24;
      static const size_t DEFAULT_TM_1_3_BYTE_SIZE = 22;
      static const size_t DEFAULT_TM_1_4_BYTE_SIZE = 24;
      static const size_t DEFAULT_TM_1_5_BYTE_SIZE = 24;
      static const size_t DEFAULT_TM_1_6_BYTE_SIZE = 26;
      static const size_t DEFAULT_TM_1_7_BYTE_SIZE = 22;
      static const size_t DEFAULT_TM_1_8_BYTE_SIZE = 24;
    }

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

      // creates TM response to TC, the caller is responsible for
      // - initialization of source sequence counter, packet time and CRC
      // - deletion of the TM packet
      PUS::PACKET::TMpacket* respond(const PUS::PACKET::TCpacket& p_tcPkt,
                                     uint8_t p_subType) throw(UTIL::Exception);

      // change setup values
      virtual void setTcHeaderPos(size_t p_tcHeaderPos);
      virtual void setTM_1_1_ByteSize(size_t p_byteSize);
      virtual void setTM_1_2_ByteSize(size_t p_byteSize);
      virtual void setTM_1_3_ByteSize(size_t p_byteSize);
      virtual void setTM_1_4_ByteSize(size_t p_byteSize);
      virtual void setTM_1_5_ByteSize(size_t p_byteSize);
      virtual void setTM_1_6_ByteSize(size_t p_byteSize);
      virtual void setTM_1_7_ByteSize(size_t p_byteSize);
      virtual void setTM_1_8_ByteSize(size_t p_byteSize);

    protected:
      // position of the TC header in the TM response
      size_t m_tcHeaderPos;
      // TM packet sizes depending on the service sub type (1...8)
      size_t m_tmPacketSizes[9];

    private:
      Service1(const Service1& p_service);
      const Service1& operator=(const Service1& p_task);

      static Service1* s_instance;
    };
  }
}

#endif
