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
// SpaceWire - SpaceWire Packet Module                                        *
//*****************************************************************************
#ifndef CCSDS_DU_hpp
#define CCSDS_DU_hpp

#include "UTIL_DU.hpp"

namespace SPW
{
  namespace PACKET
  {
    ///////////////
    // constants //
    ///////////////
    namespace PROTOCOL_ID
    {
      static const uint8_t EXTENDED = 0;
      static const uint8_t RMAP = 1;
      static const uint8_t CCSDS = 2;
      static const uint8_t GOES = 238;
      static const uint8_t STUP = 239;
      static const uint8_t INVALID = 255;
    }
    static const uint8_t UNKNOWN_LOG_ADDR = 254;

    //-------------------------------------------------------------------------
    class Packet: public UTIL::DU
    //-------------------------------------------------------------------------
    {
    public:
      // constructors and destructur
      Packet();
      // structure of the SpaceWire packet:
      // - SpW address: 0-n bytes (p_spwAddrSize)
      // - logical address: 1 byte
      // - protocol ID: 1 byte 
      // - data field: 0-n bytes (p_spwDataSize)
      Packet(size_t p_spwAddrSize, size_t p_spwDataSize);
      // the buffer shall contain a correct SpaceWire packet
      Packet(void* p_buffer, size_t p_bufferSize, size_t p_spwAddrSize);
      // the buffer shall contain a correct SpaceWire packet
      Packet(const void* p_buffer,
             size_t p_bufferSize,
             bool p_copyBuffer,
             size_t p_spwAddrSize);
      Packet(const Packet& p_du);
      const Packet& operator=(const Packet& p_du);
      virtual ~Packet();

      // access methods
      virtual size_t getSPWaddrSize() const throw(UTIL::Exception);
      virtual void setSPWaddr(size_t p_byteLength, const void* p_bytes)
        throw(UTIL::Exception);
      virtual const uint8_t* getSPWaddr() const throw(UTIL::Exception);
      virtual void setLogAddr(uint8_t p_logAddr) throw(UTIL::Exception);
      virtual uint8_t getLogAddr() const throw(UTIL::Exception);
      virtual void setProtocolID(uint8_t p_id) throw(UTIL::Exception);
      virtual uint8_t setProtocolID() const throw(UTIL::Exception);
      virtual size_t getSPWdataSize() const throw(UTIL::Exception);
      virtual void setSPWdata(size_t p_byteLength, const void* p_bytes)
        throw(UTIL::Exception);
      virtual const uint8_t* getSPWdata() const throw(UTIL::Exception);

    private:
      size_t m_spwAddrSize;
    };

    //-------------------------------------------------------------------------
    class RMAPpacket: public Packet
    //-------------------------------------------------------------------------
    {
    public:
      // constructors and destructur
      RMAPpacket();
      RMAPpacket(size_t p_spwAddrSize,
                 uint8_t p_instruction,
                 size_t p_dataSize);
      RMAPpacket(void* p_buffer, size_t p_bufferSize, size_t p_spwAddrSize);
      RMAPpacket(const void* p_buffer,
                 size_t p_bufferSize,
                 bool p_copyBuffer,
                 size_t p_spwAddrSize);
      RMAPpacket(const RMAPpacket& p_du);
      const RMAPpacket& operator=(const RMAPpacket& p_du);
      virtual ~RMAPpacket();

      // access methods
      virtual uint8_t getInstruction() const throw(UTIL::Exception);
      virtual void setHeaderCRC() throw(UTIL::Exception);
      virtual uint8_t getHeaderCRC() const throw(UTIL::Exception);
      virtual size_t getDataSize() const throw(UTIL::Exception);
      virtual uint32_t getDataLength() const throw(UTIL::Exception);
      virtual void setData(size_t p_byteLength, const void* p_bytes)
        throw(UTIL::Exception);
      virtual const uint8_t* getData() const throw(UTIL::Exception);
      virtual void setDataCRC() throw(UTIL::Exception);
      virtual uint8_t getDataCRC() const throw(UTIL::Exception);
    };

    //-------------------------------------------------------------------------
    class RMAPcommand: public RMAPpacket
    //-------------------------------------------------------------------------
    {
    public:
      // constructors and destructur
      RMAPcommand();
      RMAPcommand(size_t p_targetSPWaddrSize,
                  uint8_t p_instruction,
                  size_t p_dataSize);
      RMAPcommand(void* p_buffer, size_t p_bufferSize, size_t p_targetSPWaddrSize);
      RMAPcommand(const void* p_buffer,
                  size_t p_bufferSize,
                  bool p_copyBuffer,
                  size_t p_targetSPWaddrSize);
      RMAPcommand(const RMAPcommand& p_du);
      const RMAPcommand& operator=(const RMAPcommand& p_du);
      virtual ~RMAPcommand();

      // access methods
      virtual void setReplyAddr(size_t p_byteLength, const void* p_bytes)
        throw(UTIL::Exception);
      virtual const uint8_t* getReplyAddr() const throw(UTIL::Exception);
      virtual void setInitLogAddr(uint8_t p_logAddr) throw(UTIL::Exception);
      virtual uint8_t getInitLogAddr() const throw(UTIL::Exception);
      virtual void setTransactionID(uint16_t p_transID) throw(UTIL::Exception);
      virtual uint16_t getTransactionID() const throw(UTIL::Exception);
      virtual void setExtendedMemAddr(uint8_t p_extMemAddr) throw(UTIL::Exception);
      virtual uint8_t getExtendedMemAddr() const throw(UTIL::Exception);
      virtual void setMemoryAddr(uint32_t p_memAddr) throw(UTIL::Exception);
      virtual uint32_t getMemoryAddr() const throw(UTIL::Exception);
      virtual void setReadModWriteData(uint32_t p_data) throw(UTIL::Exception);
      virtual uint32_t getReadModWriteData() const throw(UTIL::Exception);
      virtual void setReadModWriteMask(uint32_t p_mask) throw(UTIL::Exception);
      virtual uint32_t getReadModWriteMask() const throw(UTIL::Exception);
    };

    //-------------------------------------------------------------------------
    class RMAPreply: public RMAPpacket
    //-------------------------------------------------------------------------
    {
    public:
      // constructors and destructur
      RMAPreply();
      RMAPreply(const RMAPcommand& p_command);
      RMAPreply(void* p_buffer, size_t p_bufferSize, size_t p_initSPWaddrSize);
      RMAPreply(const void* p_buffer,
                size_t p_bufferSize,
                bool p_copyBuffer,
                size_t p_initSPWaddrSize);
      RMAPreply(const RMAPreply& p_du);
      const RMAPreply& operator=(const RMAPreply& p_du);
      virtual ~RMAPreply();

      // access methods
      virtual void setStatus(uint8_t p_status) throw(UTIL::Exception);
      virtual uint8_t getStatus() const throw(UTIL::Exception);
      virtual uint8_t getInitLogAddr() const throw(UTIL::Exception);
      virtual uint16_t getTransactionID() const throw(UTIL::Exception);
      virtual void setReadModWriteData(uint32_t p_data) throw(UTIL::Exception);
      virtual uint32_t getReadModWriteData() const throw(UTIL::Exception);
    };
  }
}

#endif
