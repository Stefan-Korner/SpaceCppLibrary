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
#include "SPW_PACKET.hpp"

#include "UTIL_CRC.hpp"

////////////
// Packet //
////////////

//-----------------------------------------------------------------------------
SPW::PACKET::Packet::Packet(): m_spwAddrSize(0)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPW::PACKET::Packet::Packet(size_t p_spwAddrSize, size_t p_spwDataSize):
  UTIL::DU::DU(p_spwAddrSize + p_spwDataSize), m_spwAddrSize(p_spwAddrSize)
//-----------------------------------------------------------------------------
{
  // these method can throw exceptions but this should not happen,
  // because the buffer is allocated with proper size
  setLogAddr(SPW::PACKET::UNKNOWN_LOG_ADDR);
  setProtocolID(SPW::PACKET::PROTOCOL_ID::INVALID);
}

//-----------------------------------------------------------------------------
SPW::PACKET::Packet::Packet(void* p_buffer,
                            size_t p_bufferSize,
                            size_t p_spwAddrSize):
  UTIL::DU::DU(p_buffer, p_bufferSize), m_spwAddrSize(p_spwAddrSize)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPW::PACKET::Packet::Packet(const void* p_buffer,
                            size_t p_bufferSize,
                            bool p_copyBuffer,
                            size_t p_spwAddrSize):
  UTIL::DU::DU(p_buffer, p_bufferSize, p_copyBuffer),
  m_spwAddrSize(p_spwAddrSize)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPW::PACKET::Packet::Packet(const SPW::PACKET::Packet& p_du):
  UTIL::DU::DU(p_du), m_spwAddrSize(p_du.m_spwAddrSize)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const SPW::PACKET::Packet& SPW::PACKET::Packet::operator=(
  const SPW::PACKET::Packet& p_du)
//-----------------------------------------------------------------------------
{
  if(&p_du != this)
  {
    UTIL::DU::operator=(p_du);
    m_spwAddrSize = p_du.m_spwAddrSize;
  }
  return *this;
}

//-----------------------------------------------------------------------------
SPW::PACKET::Packet::~Packet()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
size_t SPW::PACKET::Packet::getSPWaddrSize() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return m_spwAddrSize;
}

//-----------------------------------------------------------------------------
void SPW::PACKET::Packet::setSPWaddr(size_t p_byteLength, const void* p_bytes)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // check if there is a writable buffer with proper size
  if(bufferIsReadonly())
  {
    throw UTIL::Exception("SPW packet is configured for Read Only");
  }
  // the buffer must have at least the size of the SPW address
  if(p_byteLength > bufferSize())
  {
    throw UTIL::Exception("SPW address is too large for available packet buffer");
  }
  // copy the address
  setBytes(0, p_byteLength, p_bytes);
}

//-----------------------------------------------------------------------------
const uint8_t* SPW::PACKET::Packet::getSPWaddr() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return buffer();
}

//-----------------------------------------------------------------------------
void SPW::PACKET::Packet::setLogAddr(uint8_t p_logAddr) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // check if there is a writable buffer with proper size
  if(bufferIsReadonly())
  {
    throw UTIL::Exception("SPW packet is configured for Read Only");
  }
  // the SPW data size must be least 1 bytes large
  if(getSPWdataSize() < 1)
  {
    throw UTIL::Exception("Logical address does not fit into SPW data field");
  }
  // copy the address
  (*this)[m_spwAddrSize] = p_logAddr;  
}

//-----------------------------------------------------------------------------
uint8_t SPW::PACKET::Packet::getLogAddr() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // the SPW data size must be least 1 bytes large
  if(getSPWdataSize() < 1)
  {
    throw UTIL::Exception("Logical address does not fit into SPW data field");
  }
  // fetch the address
  return (*this)[m_spwAddrSize];  
}

//-----------------------------------------------------------------------------
void SPW::PACKET::Packet::setProtocolID(uint8_t p_id) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // check if there is a writable buffer with proper size
  if(bufferIsReadonly())
  {
    throw UTIL::Exception("SPW packet is configured for Read Only");
  }
  // the SPW data size must be least 2 bytes large
  // (with logical address and protocol ID)
  if(getSPWdataSize() < 2)
  {
    throw UTIL::Exception("Protocol ID does not fit into SPW data field");
  }
  // copy the protocol ID
  (*this)[m_spwAddrSize + 1] = p_id;  
}

//-----------------------------------------------------------------------------
uint8_t SPW::PACKET::Packet::getProtocolID() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // the SPW data size must be least 2 bytes large
  // (with logical address and protocol ID)
  if(getSPWdataSize() < 2)
  {
    throw UTIL::Exception("Protocol ID does not fit into SPW data field");
  }
  // fetch the protocol ID
  return (*this)[m_spwAddrSize + 1];  
}

//-----------------------------------------------------------------------------
size_t SPW::PACKET::Packet::getSPWdataSize() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // the buffer must have at least the size of the SPW address
  if(m_spwAddrSize > bufferSize())
  {
    throw UTIL::Exception("Data out of SPW packet buffer");
  }
  return (bufferSize() - m_spwAddrSize);
}

//-----------------------------------------------------------------------------
void SPW::PACKET::Packet::setSPWdata(size_t p_byteLength, const void* p_bytes)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // check if there is a writable buffer with proper size
  if(bufferIsReadonly())
  {
    throw UTIL::Exception("SPW packet is configured for Read Only");
  }
  // the existing buffer must have at least the size for the passed data
  if(p_byteLength > getSPWdataSize())
  {
    throw UTIL::Exception("Data do not fit into SPW packet buffer");
  }
  // copy the data
  return setBytes(m_spwAddrSize, p_byteLength, p_bytes);
}

//-----------------------------------------------------------------------------
const uint8_t* SPW::PACKET::Packet::getSPWdata() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // this checks also the consistency of the buffer
  // and throws an exception if there are no data
  size_t spwDataSize = getSPWdataSize();
  return getBytes(m_spwAddrSize, spwDataSize);
}

////////////////
// RMAPpacket //
////////////////

//-----------------------------------------------------------------------------
SPW::PACKET::RMAPpacket::RMAPpacket()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPW::PACKET::RMAPpacket::RMAPpacket(size_t p_spwAddrSize,
                                    uint8_t p_instruction,
                                    size_t p_dataSize):
  SPW::PACKET::Packet::Packet(p_spwAddrSize,
                              headerSize(p_instruction) + p_dataSize) 
//-----------------------------------------------------------------------------
{
  // set protocol ID and instruction
  (*this)[p_spwAddrSize + 1] = SPW::PACKET::PROTOCOL_ID::RMAP;
  (*this)[p_spwAddrSize + 2] = p_instruction;
}

//-----------------------------------------------------------------------------
SPW::PACKET::RMAPpacket::RMAPpacket(void* p_buffer,
                                    size_t p_bufferSize,
                                    size_t p_spwAddrSize):
  SPW::PACKET::Packet::Packet(p_buffer, p_bufferSize, p_spwAddrSize)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPW::PACKET::RMAPpacket::RMAPpacket(const void* p_buffer,
                                    size_t p_bufferSize,
                                    bool p_copyBuffer,
                                    size_t p_spwAddrSize):
  SPW::PACKET::Packet::Packet(
    p_buffer, p_bufferSize, p_copyBuffer, p_spwAddrSize)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPW::PACKET::RMAPpacket::RMAPpacket(const SPW::PACKET::RMAPpacket& p_du):
  SPW::PACKET::Packet::Packet(p_du)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const SPW::PACKET::RMAPpacket&
SPW::PACKET::RMAPpacket::operator=(const SPW::PACKET::RMAPpacket& p_du)
//-----------------------------------------------------------------------------
{
  SPW::PACKET::Packet::operator=(p_du);
  return *this;
}

//-----------------------------------------------------------------------------
SPW::PACKET::RMAPpacket::~RMAPpacket()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
uint8_t SPW::PACKET::RMAPpacket::getInstruction() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // the RMAP header size must be least 3 bytes large
  // (with logical address, protocol ID, instruction)
  if(getHeaderSize() < 3)
  {
    throw UTIL::Exception("Instruction does not fit into RMAP header");
  }
  // fetch the protocol ID
  return (*this)[getSPWaddrSize() + 2];  
}

//-----------------------------------------------------------------------------
size_t SPW::PACKET::RMAPpacket::getHeaderSize() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  size_t hdrSize = headerSize(getInstruction());
  // header starts at the beginning of the SPW data field
  if(hdrSize > getSPWdataSize())
  {
    throw UTIL::Exception("Encoded RMAP header does not fit into SPW packet buffer");
  }
  return hdrSize;
}

//-----------------------------------------------------------------------------
const uint8_t* SPW::PACKET::RMAPpacket::getHeader() const
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  size_t hdrSize = headerSize(getInstruction());
  if(hdrSize > getSPWdataSize())
  {
    throw UTIL::Exception("Encoded RMAP header does not fit into SPW packet buffer");
  }
  // fetch the header (starts at the beginning of the SPW data field)
  return getSPWdata();
}

//-----------------------------------------------------------------------------
void SPW::PACKET::RMAPpacket::setHeaderCRC() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // check if there is a writable buffer with proper size
  if(bufferIsReadonly())
  {
    throw UTIL::Exception("RMAP packet is configured for Read Only");
  }
  // the RMAP header size must be least 4 bytes large
  // (with logical address, protocol ID, instruction, header CRC)
  size_t headerSize = getHeaderSize();
  if(headerSize < 4)
  {
    throw UTIL::Exception("Header CRC does not fit into RMAP header");
  }
  // calculate CRC exclusive CRC byte
  size_t crcPosInHeader = headerSize - 1;
  uint8_t crc = UTIL::CRC::calculate8(getHeader(), crcPosInHeader);
  // set the header CRC
  size_t crcPosInDU = getSPWaddrSize() + headerSize - 1;
  (*this)[crcPosInDU] = crc;
}

//-----------------------------------------------------------------------------
uint8_t SPW::PACKET::RMAPpacket::getHeaderCRC() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // the RMAP header size must be least 4 bytes large
  // (with logical address, protocol ID, instruction, header CRC)
  size_t headerSize = getHeaderSize();
  if(headerSize < 4)
  {
    throw UTIL::Exception("Header CRC does not fit into RMAP header");
  }
  // fetch the header CRC
  size_t crcPosInDU = getSPWaddrSize() + headerSize - 1;
  return (*this)[crcPosInDU];
}

//-----------------------------------------------------------------------------
size_t SPW::PACKET::RMAPpacket::getDataSize() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return getDataLength();
}

//-----------------------------------------------------------------------------
uint32_t SPW::PACKET::RMAPpacket::getDataLength() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // data length = 3 bytes -> the RMAP header size must be least 7 bytes large
  // (with logical address, protocol ID, instruction, data length, header CRC)
  size_t headerSize = getHeaderSize();
  if(headerSize < 7)
  {
    throw UTIL::Exception("data size field does not fit into RMAP header");
  }
  // fetch the data size
  size_t dataSizePos = getSPWaddrSize() + headerSize - 4;
  return getUnsigned(dataSizePos, 3);
}

//-----------------------------------------------------------------------------
void SPW::PACKET::RMAPpacket::setData(size_t p_byteLength, const void* p_bytes)
        throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // this checks also the consistency of the buffer
  // and throws an exception if there are no data
  if(p_byteLength > getDataSize())
  {
    throw UTIL::Exception("data do not fit into RMAP data field");
  }
  size_t dataPos = getSPWaddrSize() + getHeaderSize();
  setBytes(dataPos, p_byteLength, p_bytes);
}

//-----------------------------------------------------------------------------
const uint8_t* SPW::PACKET::RMAPpacket::getData() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // check if there is a writable buffer with proper size
  if(bufferIsReadonly())
  {
    throw UTIL::Exception("RMAP packet is configured for Read Only");
  }
  // this checks also the consistency of the buffer
  // and throws an exception if there are no data
  size_t dataPos = getSPWaddrSize() + getHeaderSize();
  size_t dataSize = getDataSize();
  return getBytes(dataPos, dataSize);
}

//-----------------------------------------------------------------------------
void SPW::PACKET::RMAPpacket::setDataCRC() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // check if there is a writable buffer with proper size
  if(bufferIsReadonly())
  {
    throw UTIL::Exception("RMAP packet is configured for Read Only");
  }
  // the RMAP data size must be least 1 byte large
  size_t dataSize = getDataSize();
  if(dataSize < 1)
  {
    throw UTIL::Exception("Data CRC does not fit into RMAP data field");
  }
  // calculate CRC exclusive CRC byte
  size_t crcPosInData = dataSize - 1;
  uint8_t crc = UTIL::CRC::calculate8(getData(), crcPosInData);
  // set the header CRC
  size_t crcPosInDU = getSPWaddrSize() + getHeaderSize() + dataSize - 1;
  (*this)[crcPosInDU] = crc;
}

//-----------------------------------------------------------------------------
uint8_t SPW::PACKET::RMAPpacket::getDataCRC() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // the RMAP data size must be least 1 byte large
  size_t dataSize = getDataSize();
  if(dataSize < 1)
  {
    throw UTIL::Exception("Data CRC does not fit into RMAP data field");
  }
  // fetch the data CRC
  size_t crcPosInDU = getSPWaddrSize() + getHeaderSize() + dataSize - 1;
  return (*this)[crcPosInDU];
}

//-----------------------------------------------------------------------------
bool SPW::PACKET::RMAPpacket::isCommand(uint8_t p_instruction)
//-----------------------------------------------------------------------------
{
  return ((p_instruction & 0x40) == 0x40);
}

//-----------------------------------------------------------------------------
bool SPW::PACKET::RMAPpacket::isReply(uint8_t p_instruction)
//-----------------------------------------------------------------------------
{
  return ((p_instruction & 0x40) == 0x00);
}

//-----------------------------------------------------------------------------
bool SPW::PACKET::RMAPpacket::isRead(uint8_t p_instruction)
//-----------------------------------------------------------------------------
{
  return ((p_instruction & 0x20) == 0x00);
}

//-----------------------------------------------------------------------------
bool SPW::PACKET::RMAPpacket::isWrite(uint8_t p_instruction)
//-----------------------------------------------------------------------------
{
  return ((p_instruction & 0x20) == 0x20);
}

//-----------------------------------------------------------------------------
bool SPW::PACKET::RMAPpacket::verifyDataBeforeWrite(uint8_t p_instruction)
//-----------------------------------------------------------------------------
{
  return ((p_instruction & 0x10) == 0x10);
}

//-----------------------------------------------------------------------------
bool SPW::PACKET::RMAPpacket::hasReply(uint8_t p_instruction)
//-----------------------------------------------------------------------------
{
  return ((p_instruction & 0x08) == 0x08);
}

//-----------------------------------------------------------------------------
bool SPW::PACKET::RMAPpacket::incrementAddress(uint8_t p_instruction)
//-----------------------------------------------------------------------------
{
  return ((p_instruction & 0x04) == 0x04);
}

//-----------------------------------------------------------------------------
SPW::PACKET::RMAPpacket::ReplyAddressLength
SPW::PACKET::RMAPpacket::replyAddrLength(uint8_t p_instruction)
//-----------------------------------------------------------------------------
{
  switch(p_instruction & 0x03)
  {
  case 0x00: return BYTES_0;
  case 0x01: return BYTES_4;
  case 0x02: return BYTES_8;
  case 0x03: return BYTES_12;
  }
  // should not be reached (to satisfy the compiler)
  return BYTES_0;
}

//-----------------------------------------------------------------------------
SPW::PACKET::RMAPpacket::CommandCode
SPW::PACKET::RMAPpacket::commandCode(uint8_t p_instruction)
//-----------------------------------------------------------------------------
{
  switch(p_instruction & 0x3C)
  {
  case 0x00: return CMD_INVALID;
  case 0x04: return CMD_INVALID;
  case 0x08: return CMD_READ_SINGLE_ADDR;
  case 0x0C: return CMD_READ_INCR_ADDR;
  case 0x10: return CMD_INVALID;
  case 0x14: return CMD_INVALID;
  case 0x18: return CMD_INVALID;
  case 0x1C: return CMD_READ_MOD_WRITE_INCR_ADDR;
  case 0x20: return CMD_WRITE_SINGLE_ADDR;
  case 0x24: return CMD_WRITE_INCR_ADDR;
  case 0x28: return CMD_WRITE_SINGLE_ADDR_RPLY;
  case 0x2C: return CMD_WRITE_INCR_ADDR_RPLY;
  case 0x30: return CMD_WRITE_SINGLE_ADDR_VERIF;
  case 0x34: return CMD_WRITE_INCR_ADDR_VERIF;
  case 0x38: return CMD_WRITE_SINGLE_ADDR_VERIF_RPLY;
  case 0x3C: return CMD_WRITE_INCR_ADDR_VERIF_RPLY;
  }
  // should not be reached (to satisfy the compiler)
  return CMD_INVALID;
}

//-----------------------------------------------------------------------------
uint8_t SPW::PACKET::RMAPpacket::headerSize(uint8_t p_instruction)
//-----------------------------------------------------------------------------
{
  if(isCommand(p_instruction))
  {
    return (replyAddrLength(p_instruction) + 16);
  }
  else
  {
    // reply
    if(isWrite(p_instruction))
    {
      return 8;
    }
    else
    {
      return 12;
    }
  }
}

//-----------------------------------------------------------------------------
uint8_t SPW::PACKET::RMAPpacket::instruction(
  bool p_isCommand,
  ReplyAddressLength p_rplyAddrLength,
  CommandCode p_commandCode)
//-----------------------------------------------------------------------------
{
  uint8_t retVal = (p_isCommand ? 0x40 : 0x00);
  switch(p_rplyAddrLength)
  {
  case BYTES_0:                  break;
  case BYTES_4:  retVal |= 0x01; break;
  case BYTES_8:  retVal |= 0x02; break;
  case BYTES_12: retVal |= 0x03; break;
  }
  switch(p_commandCode)
  {
  case CMD_INVALID:                                      break;
  case CMD_READ_SINGLE_ADDR:             retVal |= 0x08; break;
  case CMD_READ_INCR_ADDR:               retVal |= 0x0C; break;
  case CMD_READ_MOD_WRITE_INCR_ADDR:     retVal |= 0x1C; break;
  case CMD_WRITE_SINGLE_ADDR:            retVal |= 0x20; break;
  case CMD_WRITE_INCR_ADDR:              retVal |= 0x24; break;
  case CMD_WRITE_SINGLE_ADDR_RPLY:       retVal |= 0x28; break;
  case CMD_WRITE_INCR_ADDR_RPLY:         retVal |= 0x2C; break;
  case CMD_WRITE_SINGLE_ADDR_VERIF:      retVal |= 0x30; break;
  case CMD_WRITE_INCR_ADDR_VERIF:        retVal |= 0x34; break;
  case CMD_WRITE_SINGLE_ADDR_VERIF_RPLY: retVal |= 0x38; break;
  case CMD_WRITE_INCR_ADDR_VERIF_RPLY:   retVal |= 0x3C; break;
  }
  return retVal;
}

