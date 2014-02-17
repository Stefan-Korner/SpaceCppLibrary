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
// PUS Services - Packet Module                                               *
//*****************************************************************************
#ifndef PUS_DU_hpp
#define PUS_DU_hpp

#include "CCSDS_PACKET.hpp"

namespace PUS
{
  namespace PACKET
  {
    ///////////////
    // constants //
    ///////////////
    static const uint32_t PUS_VERSION_NUMBER = 1;
    static const size_t TM_PACKET_DATAFIELD_HEADER_BYTE_SIZE = 3;
    namespace TM_PACKET_DATAFIELD_HEADER
    {
      // offsets are absolute: from the beginning of the CCSDS packet
      // byte 6
      static const UTIL::DU::BitAccessor PUS_SPARE_1 =           {48,  1};
      static const UTIL::DU::BitAccessor PUS_VERSION_NUMBER =    {49,  3};
      static const UTIL::DU::BitAccessor PUS_SPARE_2 =           {52,  4};
      static const UTIL::DU::UnsignedAccessor SERVICE_TYPE =     { 7,  1};
      static const UTIL::DU::UnsignedAccessor SERVICE_SUB_TYPE = { 8,  1};
    }

    static const size_t TC_PACKET_DATAFIELD_HEADER_BYTE_SIZE = 3;
    namespace TC_PACKET_DATAFIELD_HEADER
    {
      // offsets are absolute: from the beginning of the CCSDS packet
      // byte 6
      static const UTIL::DU::BitAccessor PUS_SPARE_1 =           {48,  1};
      static const UTIL::DU::BitAccessor PUS_VERSION_NUMBER =    {49,  3};
      static const UTIL::DU::BitAccessor ACK =                   {52,  4};
      static const UTIL::DU::UnsignedAccessor SERVICE_TYPE =     { 7,  1};
      static const UTIL::DU::UnsignedAccessor SERVICE_SUB_TYPE = { 8,  1};
    }

    //-------------------------------------------------------------------------
    class TMpacket: public CCSDS::PACKET::TMpacket
    //-------------------------------------------------------------------------
    {
    public:
      // constructors and destructur
      TMpacket();
      TMpacket(size_t p_bufferSize);
      TMpacket(void* p_buffer, size_t p_bufferSize);
      TMpacket(const void* p_buffer, size_t p_bufferSize, bool p_copyBuffer);
      TMpacket(const TMpacket& p_du);
      const TMpacket& operator=(const TMpacket& p_du);
      virtual ~TMpacket();

      // access methods (convenience methods)
      virtual void pusVersionNumber(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t pusVersionNumber() const
        throw(UTIL::DU::Exception);
      virtual void serviceType(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t serviceType() const
        throw(UTIL::DU::Exception);
      virtual void serviceSubType(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t serviceSubType() const
        throw(UTIL::DU::Exception);
    };

    //-------------------------------------------------------------------------
    class TCpacket: public CCSDS::PACKET::TCpacket
    //-------------------------------------------------------------------------
    {
    public:
      // constructors and destructur
      TCpacket();
      TCpacket(size_t p_bufferSize);
      TCpacket(void* p_buffer, size_t p_bufferSize);
      TCpacket(const void* p_buffer, size_t p_bufferSize, bool p_copyBuffer);
      TCpacket(const TCpacket& p_du);
      const TCpacket& operator=(const TCpacket& p_du);
      virtual ~TCpacket();

      // access methods (convenience methods)
      virtual void pusVersionNumber(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t pusVersionNumber() const
        throw(UTIL::DU::Exception);
      virtual void ack(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t ack() const
        throw(UTIL::DU::Exception);
      virtual void serviceType(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t serviceType() const
        throw(UTIL::DU::Exception);
      virtual void serviceSubType(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t serviceSubType() const
        throw(UTIL::DU::Exception);
    };
  }
}

#endif
