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
#include "CCSDS_PACKET.hpp"

#include "CCSDS_TIME.hpp"
#include "UTIL_CRC.hpp"

////////////
// Packet //
////////////

//-----------------------------------------------------------------------------
CCSDS::PACKET::Packet::Packet()
//-----------------------------------------------------------------------------
{
  resize(PRIMARY_HEADER_BYTE_SIZE);
  setPacketLength();
  versionNumber(CCSDS::PACKET::VERSION_NUMBER);
  segmentationFlags(CCSDS::PACKET::SEGMENTATION_NONE);
  dataFieldHeaderFlag(0);
}

//-----------------------------------------------------------------------------
CCSDS::PACKET::Packet::Packet(size_t p_bufferSize):
  UTIL::DU::DU(p_bufferSize)
//-----------------------------------------------------------------------------
{
  if(p_bufferSize < PRIMARY_HEADER_BYTE_SIZE)
  {
    resize(PRIMARY_HEADER_BYTE_SIZE);
  }
  setPacketLength();
  versionNumber(CCSDS::PACKET::VERSION_NUMBER);
  segmentationFlags(CCSDS::PACKET::SEGMENTATION_NONE);
  dataFieldHeaderFlag(0);
}

//-----------------------------------------------------------------------------
CCSDS::PACKET::Packet::Packet(void* p_buffer, size_t p_bufferSize):
  UTIL::DU::DU(p_buffer, p_bufferSize)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
CCSDS::PACKET::Packet::Packet(const void* p_buffer,
                              size_t p_bufferSize,
                              bool p_copyBuffer):
  UTIL::DU::DU(p_buffer, p_bufferSize, p_copyBuffer)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
CCSDS::PACKET::Packet::Packet(const CCSDS::PACKET::Packet& p_du):
  UTIL::DU::DU(p_du)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const CCSDS::PACKET::Packet& CCSDS::PACKET::Packet::operator=(
  const CCSDS::PACKET::Packet& p_du)
//-----------------------------------------------------------------------------
{
  UTIL::DU::operator=(p_du);
  return *this;
}

//-----------------------------------------------------------------------------
CCSDS::PACKET::Packet::~Packet()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
void CCSDS::PACKET::Packet::versionNumber(uint32_t p_val)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(CCSDS::PACKET::PRIMARY_HEADER::VERSION_NUMBER, p_val);
}

//-----------------------------------------------------------------------------
uint32_t CCSDS::PACKET::Packet::versionNumber() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(CCSDS::PACKET::PRIMARY_HEADER::VERSION_NUMBER);
}

//-----------------------------------------------------------------------------
void CCSDS::PACKET::Packet::packetType(uint32_t p_val) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(CCSDS::PACKET::PRIMARY_HEADER::PACKET_TYPE, p_val);
}

//-----------------------------------------------------------------------------
uint32_t CCSDS::PACKET::Packet::packetType() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(CCSDS::PACKET::PRIMARY_HEADER::PACKET_TYPE);
}

//-----------------------------------------------------------------------------
void CCSDS::PACKET::Packet::dataFieldHeaderFlag(uint32_t p_val)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(CCSDS::PACKET::PRIMARY_HEADER::DATA_FIELD_HEADER_FLAG, p_val);
}

//-----------------------------------------------------------------------------
uint32_t CCSDS::PACKET::Packet::dataFieldHeaderFlag() const
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(CCSDS::PACKET::PRIMARY_HEADER::DATA_FIELD_HEADER_FLAG);
}

//-----------------------------------------------------------------------------
void CCSDS::PACKET::Packet::applicationProcessId(uint32_t p_val)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(CCSDS::PACKET::PRIMARY_HEADER::APPLICATION_PROCESS_ID, p_val);
}

//-----------------------------------------------------------------------------
uint32_t CCSDS::PACKET::Packet::applicationProcessId() const
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(CCSDS::PACKET::PRIMARY_HEADER::APPLICATION_PROCESS_ID);
}

//-----------------------------------------------------------------------------
void CCSDS::PACKET::Packet::segmentationFlags(uint32_t p_val)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(CCSDS::PACKET::PRIMARY_HEADER::SEGMENTATION_FLAGS, p_val);
}

//-----------------------------------------------------------------------------
uint32_t CCSDS::PACKET::Packet::segmentationFlags() const
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(CCSDS::PACKET::PRIMARY_HEADER::SEGMENTATION_FLAGS);
}

//-----------------------------------------------------------------------------
void CCSDS::PACKET::Packet::sequenceControlCount(uint32_t p_val)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(CCSDS::PACKET::PRIMARY_HEADER::SEQUENCE_CONTROL_COUNT, p_val);
}

//-----------------------------------------------------------------------------
uint32_t CCSDS::PACKET::Packet::sequenceControlCount() const
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(CCSDS::PACKET::PRIMARY_HEADER::SEQUENCE_CONTROL_COUNT);
}

//-----------------------------------------------------------------------------
void CCSDS::PACKET::Packet::packetLength(uint32_t p_val) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(CCSDS::PACKET::PRIMARY_HEADER::PACKET_LENGTH, p_val);
}

//-----------------------------------------------------------------------------
uint32_t CCSDS::PACKET::Packet::packetLength() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(CCSDS::PACKET::PRIMARY_HEADER::PACKET_LENGTH);
}

//-----------------------------------------------------------------------------
UTIL::AbsTime CCSDS::PACKET::Packet::getAbsTime(size_t p_bytePos,
                                                uint32_t p_timeCode)
   const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // check if there are sufficient data bytes via getBytes()
  const uint8_t* cucTime;
  switch(p_timeCode)
  {
  case CCSDS::CUC::L1_TIME_4_0:
    cucTime = getBytes(p_bytePos, 5);
    break;
  case CCSDS::CUC::L1_TIME_4_1:
    cucTime = getBytes(p_bytePos, 6);
    break;
  case CCSDS::CUC::L1_TIME_4_2:
    cucTime = getBytes(p_bytePos, 7);
    break;
  case CCSDS::CUC::L1_TIME_4_3:
    cucTime = getBytes(p_bytePos, 8);
    break;
  case CCSDS::CUC::L2_TIME_4_0:
    cucTime = getBytes(p_bytePos, 5);
    break;
  case CCSDS::CUC::L2_TIME_4_1:
    cucTime = getBytes(p_bytePos, 6);
    break;
  case CCSDS::CUC::L2_TIME_4_2:
    cucTime = getBytes(p_bytePos, 7);
    break;
  case CCSDS::CUC::L2_TIME_4_3:
    cucTime = getBytes(p_bytePos, 8);
    break;
  case CCSDS::CUC::T1_TIME_4_0:
    cucTime = getBytes(p_bytePos, 4);
    break;
  case CCSDS::CUC::T1_TIME_4_1:
    cucTime = getBytes(p_bytePos, 5);
    break;
  case CCSDS::CUC::T1_TIME_4_2:
    cucTime = getBytes(p_bytePos, 6);
    break;
  case CCSDS::CUC::T1_TIME_4_3:
    cucTime = getBytes(p_bytePos, 7);
    break;
  case CCSDS::CUC::T2_TIME_4_0:
    cucTime = getBytes(p_bytePos, 4);
    break;
  case CCSDS::CUC::T2_TIME_4_1:
    cucTime = getBytes(p_bytePos, 5);
    break;
  case CCSDS::CUC::T2_TIME_4_2:
    cucTime = getBytes(p_bytePos, 6);
    break;
  case CCSDS::CUC::T2_TIME_4_3:
    cucTime = getBytes(p_bytePos, 7);
    break;
  default:
    throw UTIL::Exception("invalid time code for CUC time");
  }
  // convert from CUC time to AbsTime
  return CCSDS::CUC::convert(cucTime, p_timeCode);
}

//-----------------------------------------------------------------------------
void CCSDS::PACKET::Packet::setAbsTime(size_t p_bytePos,
                                       uint32_t p_timeCode,
                                       const UTIL::AbsTime& p_time)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // convert from AbsTime time to CUC time
  CCSDS::CUC::Time cucTime =
    CCSDS::CUC::convert(p_time, (CCSDS::CUC::TimeCode) p_timeCode);
  // write only relevant bytes into buffer
  switch(p_timeCode)
  {
  case CCSDS::CUC::L1_TIME_4_0:
    setBytes(p_bytePos, 5, &cucTime);
    break;
  case CCSDS::CUC::L1_TIME_4_1:
    setBytes(p_bytePos, 6, &cucTime);
    break;
  case CCSDS::CUC::L1_TIME_4_2:
    setBytes(p_bytePos, 7, &cucTime);
    break;
  case CCSDS::CUC::L1_TIME_4_3:
    setBytes(p_bytePos, 8, &cucTime);
    break;
  case CCSDS::CUC::L2_TIME_4_0:
    setBytes(p_bytePos, 5, &cucTime);
    break;
  case CCSDS::CUC::L2_TIME_4_1:
    setBytes(p_bytePos, 6, &cucTime);
    break;
  case CCSDS::CUC::L2_TIME_4_2:
    setBytes(p_bytePos, 7, &cucTime);
    break;
  case CCSDS::CUC::L2_TIME_4_3:
    setBytes(p_bytePos, 8, &cucTime);
    break;
  case CCSDS::CUC::T1_TIME_4_0:
    setBytes(p_bytePos, 4, &cucTime.m_tCoarse0);
    break;
  case CCSDS::CUC::T1_TIME_4_1:
    setBytes(p_bytePos, 5, &cucTime.m_tCoarse0);
    break;
  case CCSDS::CUC::T1_TIME_4_2:
    setBytes(p_bytePos, 6, &cucTime.m_tCoarse0);
    break;
  case CCSDS::CUC::T1_TIME_4_3:
    setBytes(p_bytePos, 7, &cucTime.m_tCoarse0);
    break;
  case CCSDS::CUC::T2_TIME_4_0:
    setBytes(p_bytePos, 4, &cucTime.m_tCoarse0);
    break;
  case CCSDS::CUC::T2_TIME_4_1:
    setBytes(p_bytePos, 5, &cucTime.m_tCoarse0);
    break;
  case CCSDS::CUC::T2_TIME_4_2:
    setBytes(p_bytePos, 6, &cucTime.m_tCoarse0);
    break;
  case CCSDS::CUC::T2_TIME_4_3:
    setBytes(p_bytePos, 7, &cucTime.m_tCoarse0);
    break;
  default:
    throw UTIL::Exception("invalid time code for CUC time");
  }
}

//-----------------------------------------------------------------------------
// sets the packetLength according to the data unit's buffer size
void CCSDS::PACKET::Packet::setPacketLength() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  packetLength(bufferSize() - PRIMARY_HEADER_BYTE_SIZE - 1);
}

//-----------------------------------------------------------------------------
// checks the packetLength according to the data unit's buffer size
bool CCSDS::PACKET::Packet::checkPacketLength() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return (packetLength() == (bufferSize() - PRIMARY_HEADER_BYTE_SIZE - 1));
}

//-----------------------------------------------------------------------------
// sets the checksum out of the binary data,
// buffer and packetLength must be correctly initialised
void CCSDS::PACKET::Packet::setChecksum() throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(!checkPacketLength())
  {
    throw UTIL::Exception("inconsistent packetLength");
  }
  size_t crcPos = bufferSize() - 2;
  uint16_t crc = UTIL::CRC::calculate(buffer(), crcPos);
  setUnsigned(crcPos, 2, crc);
}

//-----------------------------------------------------------------------------
// checks the checksum out of the binary data,
// buffer and, packetLength must be correctly initialised
bool CCSDS::PACKET::Packet::checkChecksum() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(!checkPacketLength())
  {
    return false;
  }
  size_t crcPos = bufferSize() - 2;
  uint16_t crc = UTIL::CRC::calculate(buffer(), crcPos);
  return (getUnsigned(crcPos, 2) == crc);
}

//////////////
// TMpacket //
//////////////

//-----------------------------------------------------------------------------
CCSDS::PACKET::TMpacket::TMpacket()
//-----------------------------------------------------------------------------
{
  packetType(TM_PACKET_TYPE);
}

//-----------------------------------------------------------------------------
CCSDS::PACKET::TMpacket::TMpacket(size_t p_bufferSize):
  CCSDS::PACKET::Packet::Packet(p_bufferSize)
//-----------------------------------------------------------------------------
{
  packetType(TM_PACKET_TYPE);
}

//-----------------------------------------------------------------------------
CCSDS::PACKET::TMpacket::TMpacket(void* p_buffer, size_t p_bufferSize):
  CCSDS::PACKET::Packet::Packet(p_buffer, p_bufferSize)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
CCSDS::PACKET::TMpacket::TMpacket(const void* p_buffer,
                                  size_t p_bufferSize,
                                  bool p_copyBuffer):
  CCSDS::PACKET::Packet::Packet(p_buffer, p_bufferSize, p_copyBuffer)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
CCSDS::PACKET::TMpacket::TMpacket(const CCSDS::PACKET::TMpacket& p_du):
  CCSDS::PACKET::Packet::Packet(p_du)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const CCSDS::PACKET::TMpacket& CCSDS::PACKET::TMpacket::operator=(
  const CCSDS::PACKET::TMpacket& p_du)
//-----------------------------------------------------------------------------
{
  CCSDS::PACKET::Packet::operator=(p_du);
  return *this;
}

//-----------------------------------------------------------------------------
CCSDS::PACKET::TMpacket::~TMpacket()
//-----------------------------------------------------------------------------
{}

//////////////
// TCpacket //
//////////////

//-----------------------------------------------------------------------------
CCSDS::PACKET::TCpacket::TCpacket()
//-----------------------------------------------------------------------------
{
  packetType(TC_PACKET_TYPE);
}

//-----------------------------------------------------------------------------
CCSDS::PACKET::TCpacket::TCpacket(size_t p_bufferSize):
  CCSDS::PACKET::Packet::Packet(p_bufferSize)
//-----------------------------------------------------------------------------
{
  packetType(TC_PACKET_TYPE);
}

//-----------------------------------------------------------------------------
CCSDS::PACKET::TCpacket::TCpacket(void* p_buffer, size_t p_bufferSize):
  CCSDS::PACKET::Packet::Packet(p_buffer, p_bufferSize)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
CCSDS::PACKET::TCpacket::TCpacket(const void* p_buffer,
                                  size_t p_bufferSize,
                                  bool p_copyBuffer):
  CCSDS::PACKET::Packet::Packet(p_buffer, p_bufferSize, p_copyBuffer)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
CCSDS::PACKET::TCpacket::TCpacket(const CCSDS::PACKET::TCpacket& p_du):
  CCSDS::PACKET::Packet::Packet(p_du)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const CCSDS::PACKET::TCpacket& CCSDS::PACKET::TCpacket::operator=(
  const CCSDS::PACKET::TCpacket& p_du)
//-----------------------------------------------------------------------------
{
  CCSDS::PACKET::Packet::operator=(p_du);
  return *this;
}

//-----------------------------------------------------------------------------
CCSDS::PACKET::TCpacket::~TCpacket()
//-----------------------------------------------------------------------------
{}
