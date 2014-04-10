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

////////////
// Packet //
////////////

//-----------------------------------------------------------------------------
SPW::PACKET::Packet::Packet(): m_spwAddrSize(0)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPW::PACKET::Packet::Packet(size_t p_spwAddrSize, size_t p_spwDataSize):
  UTIL::DU::DU(p_spwAddrSize + 2 + p_spwDataSize), m_spwAddrSize(p_spwAddrSize)
//-----------------------------------------------------------------------------
{
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

