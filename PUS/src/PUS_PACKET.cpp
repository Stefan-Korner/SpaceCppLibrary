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
#include "PUS_PACKET.hpp"

//////////////
// TMpacket //
//////////////

//-----------------------------------------------------------------------------
PUS::PACKET::TMpacket::TMpacket(): CCSDS::PACKET::TMpacket::TMpacket(
  CCSDS::PACKET::PRIMARY_HEADER_BYTE_SIZE +
  PUS::PACKET::TM_PACKET_DATAFIELD_HEADER_BYTE_SIZE)
//-----------------------------------------------------------------------------
{
  dataFieldHeaderFlag(1);
  pusVersionNumber(PUS::PACKET::PUS_VERSION_NUMBER);
}

//-----------------------------------------------------------------------------
PUS::PACKET::TMpacket::TMpacket(size_t p_bufferSize):
  CCSDS::PACKET::TMpacket::TMpacket(p_bufferSize)
//-----------------------------------------------------------------------------
{
  if(p_bufferSize < (CCSDS::PACKET::PRIMARY_HEADER_BYTE_SIZE +
                     PUS::PACKET::TM_PACKET_DATAFIELD_HEADER_BYTE_SIZE))
  {
    resize(CCSDS::PACKET::PRIMARY_HEADER_BYTE_SIZE +
           PUS::PACKET::TM_PACKET_DATAFIELD_HEADER_BYTE_SIZE);
  }
  setPacketLength();
  dataFieldHeaderFlag(1);
  pusVersionNumber(PUS::PACKET::PUS_VERSION_NUMBER);
}

//-----------------------------------------------------------------------------
PUS::PACKET::TMpacket::TMpacket(void* p_buffer, size_t p_bufferSize):
  CCSDS::PACKET::TMpacket::TMpacket(p_buffer, p_bufferSize)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::PACKET::TMpacket::TMpacket(const void* p_buffer,
                              size_t p_bufferSize,
                              bool p_copyBuffer):
  CCSDS::PACKET::TMpacket::TMpacket(p_buffer, p_bufferSize, p_copyBuffer)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::PACKET::TMpacket::TMpacket(const PUS::PACKET::TMpacket& p_du):
  CCSDS::PACKET::TMpacket::TMpacket(p_du)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const PUS::PACKET::TMpacket& PUS::PACKET::TMpacket::operator=(
  const PUS::PACKET::TMpacket& p_du)
//-----------------------------------------------------------------------------
{
  CCSDS::PACKET::TMpacket::operator=(p_du);
  return *this;
}

//-----------------------------------------------------------------------------
PUS::PACKET::TMpacket::~TMpacket()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
void PUS::PACKET::TMpacket::pusVersionNumber(uint32_t p_val)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(PUS::PACKET::TM_PACKET_DATAFIELD_HEADER::PUS_VERSION_NUMBER, p_val);
}

//-----------------------------------------------------------------------------
uint32_t PUS::PACKET::TMpacket::pusVersionNumber() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(PUS::PACKET::TM_PACKET_DATAFIELD_HEADER::PUS_VERSION_NUMBER);
}

//-----------------------------------------------------------------------------
void PUS::PACKET::TMpacket::serviceType(uint32_t p_val) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(PUS::PACKET::TM_PACKET_DATAFIELD_HEADER::SERVICE_TYPE, p_val);
}

//-----------------------------------------------------------------------------
uint32_t PUS::PACKET::TMpacket::serviceType() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(PUS::PACKET::TM_PACKET_DATAFIELD_HEADER::SERVICE_TYPE);
}

//-----------------------------------------------------------------------------
void PUS::PACKET::TMpacket::serviceSubType(uint32_t p_val)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(PUS::PACKET::TM_PACKET_DATAFIELD_HEADER::SERVICE_SUB_TYPE, p_val);
}

//-----------------------------------------------------------------------------
uint32_t PUS::PACKET::TMpacket::serviceSubType() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(PUS::PACKET::TM_PACKET_DATAFIELD_HEADER::SERVICE_SUB_TYPE);
}

//////////////
// TCpacket //
//////////////

//-----------------------------------------------------------------------------
PUS::PACKET::TCpacket::TCpacket(): CCSDS::PACKET::TCpacket::TCpacket(
  CCSDS::PACKET::PRIMARY_HEADER_BYTE_SIZE +
  PUS::PACKET::TC_PACKET_DATAFIELD_HEADER_BYTE_SIZE)
//-----------------------------------------------------------------------------
{
  dataFieldHeaderFlag(1);
  pusVersionNumber(PUS::PACKET::PUS_VERSION_NUMBER);
}

//-----------------------------------------------------------------------------
PUS::PACKET::TCpacket::TCpacket(size_t p_bufferSize):
  CCSDS::PACKET::TCpacket::TCpacket(p_bufferSize)
//-----------------------------------------------------------------------------
{
  if(p_bufferSize < (CCSDS::PACKET::PRIMARY_HEADER_BYTE_SIZE +
                     PUS::PACKET::TC_PACKET_DATAFIELD_HEADER_BYTE_SIZE))
  {
    resize(CCSDS::PACKET::PRIMARY_HEADER_BYTE_SIZE +
           PUS::PACKET::TC_PACKET_DATAFIELD_HEADER_BYTE_SIZE);
  }
  setPacketLength();
  dataFieldHeaderFlag(1);
  pusVersionNumber(PUS::PACKET::PUS_VERSION_NUMBER);
}

//-----------------------------------------------------------------------------
PUS::PACKET::TCpacket::TCpacket(void* p_buffer, size_t p_bufferSize):
  CCSDS::PACKET::TCpacket::TCpacket(p_buffer, p_bufferSize)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::PACKET::TCpacket::TCpacket(const void* p_buffer,
                              size_t p_bufferSize,
                              bool p_copyBuffer):
  CCSDS::PACKET::TCpacket::TCpacket(p_buffer, p_bufferSize, p_copyBuffer)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
PUS::PACKET::TCpacket::TCpacket(const PUS::PACKET::TCpacket& p_du):
  CCSDS::PACKET::TCpacket::TCpacket(p_du)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const PUS::PACKET::TCpacket& PUS::PACKET::TCpacket::operator=(
  const PUS::PACKET::TCpacket& p_du)
//-----------------------------------------------------------------------------
{
  CCSDS::PACKET::TCpacket::operator=(p_du);
  return *this;
}

//-----------------------------------------------------------------------------
PUS::PACKET::TCpacket::~TCpacket()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
void PUS::PACKET::TCpacket::pusVersionNumber(uint32_t p_val)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(PUS::PACKET::TC_PACKET_DATAFIELD_HEADER::PUS_VERSION_NUMBER, p_val);
}

//-----------------------------------------------------------------------------
uint32_t PUS::PACKET::TCpacket::pusVersionNumber() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(PUS::PACKET::TC_PACKET_DATAFIELD_HEADER::PUS_VERSION_NUMBER);
}

//-----------------------------------------------------------------------------
void PUS::PACKET::TCpacket::ack(uint32_t p_val) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(PUS::PACKET::TC_PACKET_DATAFIELD_HEADER::ACK, p_val);
}

//-----------------------------------------------------------------------------
uint32_t PUS::PACKET::TCpacket::ack() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(PUS::PACKET::TC_PACKET_DATAFIELD_HEADER::ACK);
}

//-----------------------------------------------------------------------------
void PUS::PACKET::TCpacket::serviceType(uint32_t p_val) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(PUS::PACKET::TC_PACKET_DATAFIELD_HEADER::SERVICE_TYPE, p_val);
}

//-----------------------------------------------------------------------------
uint32_t PUS::PACKET::TCpacket::serviceType() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(PUS::PACKET::TC_PACKET_DATAFIELD_HEADER::SERVICE_TYPE);
}

//-----------------------------------------------------------------------------
void PUS::PACKET::TCpacket::serviceSubType(uint32_t p_val)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  set(PUS::PACKET::TC_PACKET_DATAFIELD_HEADER::SERVICE_SUB_TYPE, p_val);
}

//-----------------------------------------------------------------------------
uint32_t PUS::PACKET::TCpacket::serviceSubType() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return get(PUS::PACKET::TC_PACKET_DATAFIELD_HEADER::SERVICE_SUB_TYPE);
}
