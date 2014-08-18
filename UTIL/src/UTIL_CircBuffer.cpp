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
// Utilities - Circular Buffer                                                *
//*****************************************************************************
#include "UTIL_CircBuffer.hpp"

#include <string.h>


//-----------------------------------------------------------------------------
UTIL::CircBuffer::CircBuffer(size_t p_bufferSize): 
  m_buffer(NULL),
  m_bufferSize(p_bufferSize),
  m_firstPos(0),
  m_freePos(0)
//-----------------------------------------------------------------------------
{
  m_buffer = new uint8_t[m_bufferSize];
}

//-----------------------------------------------------------------------------
UTIL::CircBuffer::CircBuffer(const CircBuffer& p_other):
  m_buffer(NULL),
  m_bufferSize(p_other.m_bufferSize),
  m_firstPos(p_other.m_firstPos),
  m_freePos(p_other.m_freePos)
//-----------------------------------------------------------------------------
{
  m_buffer = new uint8_t[m_bufferSize];
  memcpy(m_buffer, p_other.m_buffer, m_bufferSize);
}

//-----------------------------------------------------------------------------
const UTIL::CircBuffer&
UTIL::CircBuffer::operator=(const CircBuffer& p_other)
//-----------------------------------------------------------------------------
{
  if(&p_other != this)
  {
    delete[] m_buffer;
    m_bufferSize = p_other.m_bufferSize;
    m_firstPos = p_other.m_firstPos;
    m_freePos = p_other.m_freePos;
    m_buffer = new uint8_t[m_bufferSize];
    memcpy(m_buffer, p_other.m_buffer, m_bufferSize);
  }
  return *this;
}

//-----------------------------------------------------------------------------
UTIL::CircBuffer::~CircBuffer()
//-----------------------------------------------------------------------------
{
  delete[] m_buffer;
}

//-----------------------------------------------------------------------------
size_t UTIL::CircBuffer::size() const
//-----------------------------------------------------------------------------
{
  return((m_bufferSize + m_freePos - m_firstPos) % m_bufferSize);
}

//-----------------------------------------------------------------------------
size_t UTIL::CircBuffer::freeSize() const
//-----------------------------------------------------------------------------
{
  return((m_bufferSize + m_firstPos - m_freePos - 1) % m_bufferSize);
}

//-----------------------------------------------------------------------------
bool UTIL::CircBuffer::pushBack(const void* p_data, size_t p_dataSize)
//-----------------------------------------------------------------------------
{
  if(p_dataSize > freeSize())
  {
    return false;
  }
  if((m_freePos + p_dataSize) > m_bufferSize)
  {
    // the new data must be split
    size_t firstPartSize = m_bufferSize - m_freePos;
    size_t secondPartSize = p_dataSize - firstPartSize;
    const uint8_t* typedData = (const uint8_t*) p_data;
    memcpy(m_buffer + m_freePos, p_data, firstPartSize);
    memcpy(m_buffer, typedData + firstPartSize, secondPartSize);
  }
  else
  {
    // the new data fit directly into the buffer
    memcpy(m_buffer + m_freePos, p_data, p_dataSize);
  }
  m_freePos = (m_freePos + p_dataSize) % m_bufferSize;
  return true;
}

//-----------------------------------------------------------------------------
bool UTIL::CircBuffer::front(uint8_t* p_data, size_t p_dataSize) const
//-----------------------------------------------------------------------------
{
  if(p_dataSize > size())
  {
    return false;
  }
  if((m_firstPos + p_dataSize) > m_bufferSize)
  {
    // the returned data are split
    size_t firstPartSize = m_bufferSize - m_firstPos;
    size_t secondPartSize = p_dataSize - firstPartSize;
    memcpy(p_data, m_buffer + m_firstPos, firstPartSize);
    memcpy(p_data + firstPartSize, m_buffer, secondPartSize);
  }
  else
  {
    // the returned data fit directly
    memcpy(p_data, m_buffer + m_firstPos, p_dataSize);
  }
  return true;
}

//-----------------------------------------------------------------------------
bool UTIL::CircBuffer::popFront(size_t p_dataSize)
//-----------------------------------------------------------------------------
{
  if(p_dataSize > size())
  {
    return false;
  }
  m_firstPos = (m_firstPos + p_dataSize) % m_bufferSize;
  return true;
}

//-----------------------------------------------------------------------------
uint8_t UTIL::CircBuffer::operator[](size_t p_index) const
//-----------------------------------------------------------------------------
{
  if(p_index >= size())
  {
    // failure
    return 0;
  }
  size_t indexPos = (m_firstPos + p_index) % m_bufferSize;
  return m_buffer[indexPos];
}
