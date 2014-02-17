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
// CCSDS Stack - CCSDS Packet Module                                          *
//*****************************************************************************
#ifndef CCSDS_DU_hpp
#define CCSDS_DU_hpp

#include "UTIL_DU.hpp"

namespace CCSDS
{
  namespace PACKET
  {
    ///////////////
    // constants //
    ///////////////
    static const uint32_t TM_PACKET_TYPE = 0;
    static const uint32_t TC_PACKET_TYPE = 1;
    static const uint32_t VERSION_NUMBER = 0;
    static const uint32_t SEGMENTATION_CONTINUATION = 0;
    static const uint32_t SEGMENTATION_FIRST = 1;
    static const uint32_t SEGMENTATION_LAST = 2;
    static const uint32_t SEGMENTATION_NONE = 3;
    static const size_t CRC_BYTE_SIZE = 2;
    static const size_t PRIMARY_HEADER_BYTE_SIZE = 6;
    namespace PRIMARY_HEADER
    {
      static const UTIL::DU::BitAccessor VERSION_NUMBER =         { 0,  3};
      static const UTIL::DU::BitAccessor PACKET_TYPE =            { 3,  1};
      static const UTIL::DU::BitAccessor DATA_FIELD_HEADER_FLAG = { 4,  1};
      static const UTIL::DU::BitAccessor APPLICATION_PROCESS_ID = { 5, 11};
      // byte 2
      static const UTIL::DU::BitAccessor SEGMENTATION_FLAGS =     {16,  2};
      static const UTIL::DU::BitAccessor SEQUENCE_CONTROL_COUNT = {18, 14};
      static const UTIL::DU::UnsignedAccessor PACKET_LENGTH =     { 4,  2};
    }

    //-------------------------------------------------------------------------
    class Packet: public UTIL::DU
    //-------------------------------------------------------------------------
    {
    public:
      // constructors and destructur
      Packet();
      Packet(size_t p_bufferSize);
      Packet(void* p_buffer, size_t p_bufferSize);
      Packet(const void* p_buffer, size_t p_bufferSize, bool p_copyBuffer);
      Packet(const Packet& p_du);
      const Packet& operator=(const Packet& p_du);
      virtual ~Packet();

      // access methods (convenience methods)
      virtual void versionNumber(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t versionNumber() const
        throw(UTIL::DU::Exception);
      virtual void packetType(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t packetType() const
        throw(UTIL::DU::Exception);
      virtual void dataFieldHeaderFlag(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t dataFieldHeaderFlag() const
        throw(UTIL::DU::Exception);
      virtual void applicationProcessId(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t applicationProcessId() const
        throw(UTIL::DU::Exception);
      virtual void segmentationFlags(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t segmentationFlags() const
        throw(UTIL::DU::Exception);
      virtual void sequenceControlCount(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t sequenceControlCount() const
        throw(UTIL::DU::Exception);
      virtual void packetLength(uint32_t p_val)
        throw(UTIL::DU::Exception);
      virtual uint32_t packetLength() const
        throw(UTIL::DU::Exception);

      // other methods
      virtual void setPacketLength()
        throw(UTIL::DU::Exception);
      virtual bool checkPacketLength() const
        throw(UTIL::DU::Exception);
      virtual void setChecksum()
        throw(UTIL::DU::Exception);
      virtual bool checkChecksum() const
        throw(UTIL::DU::Exception);
    };

    //-------------------------------------------------------------------------
    class TMpacket: public Packet
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
    };

    //-------------------------------------------------------------------------
    class TCpacket: public Packet
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
    };
  }
}

#endif
