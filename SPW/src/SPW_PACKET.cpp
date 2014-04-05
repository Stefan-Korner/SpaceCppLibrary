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
SPW::PACKET::Packet::Packet()
//-----------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------
SPW::PACKET::Packet::Packet(size_t p_bufferSize):
  UTIL::DU::DU(p_bufferSize)
//-----------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------
SPW::PACKET::Packet::Packet(void* p_buffer, size_t p_bufferSize):
  UTIL::DU::DU(p_buffer, p_bufferSize)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPW::PACKET::Packet::Packet(const void* p_buffer,
                              size_t p_bufferSize,
                              bool p_copyBuffer):
  UTIL::DU::DU(p_buffer, p_bufferSize, p_copyBuffer)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPW::PACKET::Packet::Packet(const SPW::PACKET::Packet& p_du):
  UTIL::DU::DU(p_du)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
const SPW::PACKET::Packet& SPW::PACKET::Packet::operator=(
  const SPW::PACKET::Packet& p_du)
//-----------------------------------------------------------------------------
{
  UTIL::DU::operator=(p_du);
  return *this;
}

//-----------------------------------------------------------------------------
SPW::PACKET::Packet::~Packet()
//-----------------------------------------------------------------------------
{}
