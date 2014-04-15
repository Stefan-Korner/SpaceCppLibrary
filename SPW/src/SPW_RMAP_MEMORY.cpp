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
// SpaceWire - RMAP Memory                                                    *
//*****************************************************************************
#include "SPW_RMAP_MEMORY.hpp"

//-----------------------------------------------------------------------------
SPW::RMAP::Memory::Memory(size_t p_memorySize):
  m_buffer(p_memorySize), m_memoryPointer(0)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPW::RMAP::Memory::~Memory()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
size_t SPW::RMAP::Memory::getMemorySize() const
//-----------------------------------------------------------------------------
{
  return m_buffer.bufferSize();
}

//-----------------------------------------------------------------------------
UTIL::DU& SPW::RMAP::Memory::buffer()
//-----------------------------------------------------------------------------
{
  return m_buffer;
}

//-----------------------------------------------------------------------------
void SPW::RMAP::Memory::setMemoryPointer(size_t p_pos) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(p_pos >= getMemorySize())
  {
    throw UTIL::Exception("Pointer out of buffer range");
  }
  m_memoryPointer = p_pos;
}

//-----------------------------------------------------------------------------
size_t SPW::RMAP::Memory::getMemoryPointer() const
//-----------------------------------------------------------------------------
{
  return m_memoryPointer;
}

//-----------------------------------------------------------------------------
SPW::PACKET::RMAPreply* SPW::RMAP::Memory::execute(
        const SPW::PACKET::RMAPcommand& p_command)
//-----------------------------------------------------------------------------
{
  return NULL;
}
