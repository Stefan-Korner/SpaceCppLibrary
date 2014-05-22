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
// Utilities - Data Unit                                                      *
//*****************************************************************************
#include "UTIL_DU.hpp"

#include <iostream>
#include <stdio.h>
#include <string.h>

// index = [firstBitInBytePos][lastBitInBytePos]
static const uint8_t BIT_FILTER[8][8] =
{
  {0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00},
  {   0, 0xBF, 0x9F, 0x8F, 0x87, 0x83, 0x81, 0x80},
  {   0,    0, 0xDF, 0xCF, 0xC7, 0xC3, 0xC1, 0xC0},
  {   0,    0,    0, 0xEF, 0xE7, 0xE3, 0xE1, 0xE0},
  {   0,    0,    0,    0, 0xF7, 0xF3, 0xF1, 0xF0},
  {   0,    0,    0,    0,    0, 0xFB, 0xF9, 0xF8},
  {   0,    0,    0,    0,    0,    0, 0xFD, 0xFC},
  {   0,    0,    0,    0,    0,    0,    0, 0xFE}
};

//-----------------------------------------------------------------------------
UTIL::DU::DU():
  m_buffer(NULL), m_constBuffer(NULL), m_bufferSize(0), m_usedBufferSize(0)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::DU::DU(size_t p_bufferSize):
  m_buffer(NULL),
  m_constBuffer(NULL),
  m_bufferSize(p_bufferSize),
  m_usedBufferSize(p_bufferSize)
//-----------------------------------------------------------------------------
{
  m_buffer = new uint8_t[p_bufferSize];
  memset(m_buffer, 0, p_bufferSize);
}

//-----------------------------------------------------------------------------
UTIL::DU::DU(void* p_buffer, size_t p_bufferSize):
  m_buffer((uint8_t*) p_buffer),
  m_constBuffer(NULL),
  m_bufferSize(p_bufferSize),
  m_usedBufferSize(p_bufferSize)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::DU::DU(const void* p_buffer, size_t p_bufferSize, bool p_copyBuffer):
  m_buffer(NULL),
  m_constBuffer(NULL),
  m_bufferSize(p_bufferSize),
  m_usedBufferSize(p_bufferSize)
//-----------------------------------------------------------------------------
{
  if(p_copyBuffer)
  {
    m_buffer = new uint8_t[p_bufferSize];
    memcpy(m_buffer, p_buffer, p_bufferSize);
  }
  else
  {
    m_constBuffer = (const uint8_t*) p_buffer;
  }
}

//-----------------------------------------------------------------------------
UTIL::DU::DU(const UTIL::DU& p_du):
  m_buffer(NULL),
  m_constBuffer(NULL),
  m_bufferSize(p_du.m_usedBufferSize),
  m_usedBufferSize(p_du.m_usedBufferSize)
//-----------------------------------------------------------------------------
{
  if(p_du.m_buffer != NULL)
  {
    m_buffer = new uint8_t[m_bufferSize];
    memcpy(m_buffer, p_du.m_buffer, m_bufferSize);
  }
  else
  {
    m_constBuffer = p_du.m_constBuffer;
  }
}

//-----------------------------------------------------------------------------
const UTIL::DU& UTIL::DU::operator=(const UTIL::DU& p_du)
//-----------------------------------------------------------------------------
{
  init(p_du);
  return *this;
}

//-----------------------------------------------------------------------------
UTIL::DU::~DU()
//-----------------------------------------------------------------------------
{
  if(m_buffer != NULL)
  {
    delete[] m_buffer;
  }
}

//-----------------------------------------------------------------------------
bool UTIL::DU::bufferIsReadonly() const
//-----------------------------------------------------------------------------
{
  return (m_buffer == NULL);
}

//-----------------------------------------------------------------------------
void UTIL::DU::init(size_t p_bufferSize)
//-----------------------------------------------------------------------------
{
  // delete old contents (like destructor)
  if(m_buffer != NULL)
  {
    delete[] m_buffer;
  }
  // initialise new contents (like constructor)
  m_buffer = new uint8_t[p_bufferSize];
  memset(m_buffer, 0, p_bufferSize);
  m_constBuffer = NULL;
  m_bufferSize = p_bufferSize;
  m_usedBufferSize = p_bufferSize;
}

//-----------------------------------------------------------------------------
void UTIL::DU::init(void* p_buffer, size_t p_bufferSize)
//-----------------------------------------------------------------------------
{
  // delete old contents (like destructor)
  if(m_buffer != NULL)
  {
    delete[] m_buffer;
  }
  // initialise new contents (like constructor)
  m_buffer = (uint8_t*) p_buffer;
  m_constBuffer = 0;
  m_bufferSize = p_bufferSize;
  m_usedBufferSize = p_bufferSize;
}

//-----------------------------------------------------------------------------
void
UTIL::DU::init(const void* p_buffer, size_t p_bufferSize, bool p_copyBuffer)
//-----------------------------------------------------------------------------
{
  // delete old contents (like destructor)
  if(m_buffer != NULL)
  {
    delete[] m_buffer;
  }
  // initialise new contents (like constructor)
  m_buffer = NULL;
  m_constBuffer = NULL;
  m_bufferSize = p_bufferSize;
  m_usedBufferSize = p_bufferSize;
  if(p_copyBuffer)
  {
    m_buffer = new uint8_t[p_bufferSize];
    memcpy(m_buffer, p_buffer, p_bufferSize);
  }
  else
  {
    m_constBuffer = (const uint8_t*) p_buffer;
  }
}

//-----------------------------------------------------------------------------
void UTIL::DU::init(const UTIL::DU& p_du)
//-----------------------------------------------------------------------------
{
  if(&p_du != this)
  {
    // delete old contents (like destructor)
    if(m_buffer != NULL)
    {
      delete[] m_buffer;
    }
    // initialise new contents (like copy constructor)
    m_buffer = NULL;
    m_constBuffer = NULL;
    m_bufferSize = p_du.m_usedBufferSize;
    m_usedBufferSize = p_du.m_usedBufferSize;
    if(p_du.m_buffer != NULL)
    {
      m_buffer = new uint8_t[m_bufferSize];
      memcpy(m_buffer, p_du.m_buffer, m_bufferSize);
    }
    else
    {
      m_constBuffer = p_du.m_constBuffer;
    }
  }
}

//-----------------------------------------------------------------------------
void UTIL::DU::append(const UTIL::DU& p_du)
//-----------------------------------------------------------------------------
{
  // performance optimization
  size_t duBufferSize = p_du.bufferSize();
  if(duBufferSize == 0)
  {
    return;
  }
  size_t thisBufferSize = bufferSize();
  if(thisBufferSize == 0)
  {
    init(p_du);
    return;
  }
  size_t totalBufferSize = thisBufferSize + duBufferSize;
  uint8_t* newBuffer = new uint8_t[totalBufferSize];
  memcpy(newBuffer, buffer(), thisBufferSize);
  memcpy(newBuffer + thisBufferSize, p_du.buffer(), duBufferSize);
  if(m_buffer != NULL)
  {
    delete[] m_buffer;
  }
  m_buffer = newBuffer;
  m_constBuffer = NULL;
  m_bufferSize = totalBufferSize;
  m_usedBufferSize = totalBufferSize;
}

//-----------------------------------------------------------------------------
void UTIL::DU::clear()
//-----------------------------------------------------------------------------
{
  // delete old contents (like destructor)
  if(m_buffer != NULL)
  {
    delete[] m_buffer;
  }
  // initialise new contents (like default constructor)
  m_buffer = NULL;
  m_constBuffer = NULL;
  m_bufferSize = 0;
  m_usedBufferSize = 0;
}

//-----------------------------------------------------------------------------
void UTIL::DU::resize(size_t p_bufferSize) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // shrink is done without re-allocation
  if(p_bufferSize <= m_bufferSize)
  {
    m_usedBufferSize = p_bufferSize;
    return;
  }
  if(m_buffer == NULL)
  {
    if(bufferSize() == 0)
    {
      // empty buffer --> allocate fresh buffer
      m_buffer = new uint8_t[p_bufferSize];
      memset(m_buffer, 0, p_bufferSize);
      m_constBuffer = NULL;
      m_bufferSize = p_bufferSize;
      m_usedBufferSize = p_bufferSize;
    }
    else
    {
      throw UTIL::Exception("DU is configured for Read Only");
    }
  }
  else
  {
    // enlargement must be done with re-allocation
    uint8_t* oldBuffer = m_buffer;
    m_buffer = new uint8_t[p_bufferSize];
    memcpy(m_buffer, oldBuffer, m_bufferSize);
    memset(m_buffer + m_bufferSize, 0, p_bufferSize - m_bufferSize);
    m_constBuffer = NULL;
    m_bufferSize = p_bufferSize;
    m_usedBufferSize = p_bufferSize;
    delete[] oldBuffer;
  }
}

//-----------------------------------------------------------------------------
uint8_t* UTIL::DU::release(size_t& p_bufferSize)
//-----------------------------------------------------------------------------
{
  uint8_t* retVal = NULL;
  p_bufferSize = m_usedBufferSize;
  if(m_buffer != NULL)
  {
    retVal = m_buffer;
    m_buffer = NULL;
  }
  else
  {
    retVal = new uint8_t[m_usedBufferSize];
    memcpy(retVal, m_constBuffer, m_usedBufferSize);
    m_constBuffer = NULL;
  }
  m_bufferSize = 0;
  m_usedBufferSize = 0;
  return retVal;
}

//-----------------------------------------------------------------------------
const uint8_t* UTIL::DU::buffer() const
//-----------------------------------------------------------------------------
{
  return (m_buffer != NULL) ? m_buffer : m_constBuffer;
}

//-----------------------------------------------------------------------------
size_t UTIL::DU::bufferSize() const
//-----------------------------------------------------------------------------
{
  return m_usedBufferSize;
}

//-----------------------------------------------------------------------------
const uint8_t& UTIL::DU::operator[](size_t p_bytePos) const
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // consistency checks
  if(p_bytePos > bufferSize())
  {
    throw UTIL::Exception("bytePos out of buffer");
  }
  return buffer()[p_bytePos];
}

//-----------------------------------------------------------------------------
uint8_t& UTIL::DU::operator[](size_t p_bytePos) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // consistency checks
  if(m_buffer == NULL)
  {
    throw UTIL::Exception("DU is configured for Read Only");
  }
  if(p_bytePos > bufferSize())
  {
    throw UTIL::Exception("bytePos out of buffer");
  }
  return m_buffer[p_bytePos];
}

//-----------------------------------------------------------------------------
//  1...this >  p_du
//  0...this == p_du
// -1...this <  p_du
int UTIL::DU::compare(const DU& p_du) const
//-----------------------------------------------------------------------------
{
  // performance optimization
  if(m_constBuffer == p_du.m_constBuffer)
  {
    if(m_usedBufferSize > p_du.m_usedBufferSize)
    {
      return 1;
    }
    if(m_usedBufferSize < p_du.m_usedBufferSize)
    {
      return -1;
    }
    return 0;
  }
  const uint8_t* thisBuffer = buffer();
  size_t thisBufferSize = bufferSize();
  const uint8_t* duBuffer = p_du.buffer();
  size_t duBufferSize = p_du.bufferSize();
  size_t minBufferSize = (thisBufferSize < duBufferSize) ? thisBufferSize
                                                         : duBufferSize;
  for(size_t i = 0; i < minBufferSize; i++)
  {
    const uint8_t& thisChar = thisBuffer[i];
    const uint8_t& duChar = duBuffer[i];
    if(thisChar > duChar)
    {
      return 1;
    }
    if(thisChar < duChar)
    {
      return -1;
    }
  }
  if(thisBufferSize > duBufferSize)
  {
    return 1;
  }
  if(thisBufferSize < duBufferSize)
  {
    return -1;
  }
  return 0;
}

//-----------------------------------------------------------------------------
std::string UTIL::DU::dumpStr(const char* p_prefix,
                              bool p_withAbsoluteAddress) const
//-----------------------------------------------------------------------------
{
  std::string retVal;
  if(p_prefix != NULL)
  {
    retVal += p_prefix;
    retVal += " = ";
  }
  size_t length = bufferSize();
  if(length == 0)
  {
    retVal += "EMPTY";
    return retVal;
  }
  const uint8_t* dataBuffer = buffer();
  // display only the first 64K bytes
  if(length > 65536)
  {
    length = 65536;
  }
  char dumpBuffer[11];   // temporary buffer for conversion from num to hex
  for(uint32_t i = 0; i < length; i += 16)
  {
    if(p_withAbsoluteAddress)
    {
      // the dump method is only for debugging purpose,
      // it is OK to limit the printed address to 8 hex digits (32 bit)
      uint32_t addr = (uint32_t) ((uint64_t) (dataBuffer + i));
      sprintf(dumpBuffer, "\n%08x ", addr);
    }
    else
    {
      sprintf(dumpBuffer, "\n%04x ", i);
    }
    retVal += ((const char*) dumpBuffer);
    std::string asciiData;
    uint8_t j = 0;
    for(; j < 16; j++)
    {
      uint32_t offset = i + j;
      if(offset >= length)
      {
        break;
      }
      const uint8_t& nextByte = *(dataBuffer + offset);
      sprintf(dumpBuffer, "%02x ", nextByte);
      retVal += ((const char*) dumpBuffer);
      if((nextByte < 32) || (nextByte > 127))
      {
        asciiData +=  ".";
      }
      else
      {
        sprintf(dumpBuffer, "%c", nextByte);
        asciiData += ((const char*) dumpBuffer);
      }
    }
    // fillup the space if the line was incomplete
    for(; j < 16; j++)
    {
      retVal += "   ";
    }
    // append the ASCII representation of the line
    retVal += asciiData;
  }
  return retVal;
}

//-----------------------------------------------------------------------------
void UTIL::DU::dump(const char* p_prefix,
                    bool p_withAbsoluteAddress) const
//-----------------------------------------------------------------------------
{
  std::cout << dumpStr(p_prefix, p_withAbsoluteAddress) << std::endl;
}

//-----------------------------------------------------------------------------
// extracts bits as numerical unsigned value
uint32_t UTIL::DU::getBits(size_t p_bitPos,
                           size_t p_bitLength) const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // performance optimizations:
  // - divide by 8 is replaced by >> 3 (performance)
  // - modulo 8 is replaced by & 7 (performance)
  // consistency checks
  if(p_bitLength == 0)
  {
    throw UTIL::Exception("invalid bitLength");
  }
  size_t lastBitPos = p_bitPos + p_bitLength - 1;
  size_t lastBytePos = lastBitPos >> 3;
  if(lastBytePos >= bufferSize())
  {
    throw UTIL::Exception("bitPos/bitLength out of buffer");
  }
  // accumulate the number starting with the first byte
  size_t bytePos = p_bitPos >> 3;
  uint8_t byte = buffer()[bytePos];
  // first byte: filter the highest bits that do not belong to the value
  uint8_t firstBitInBytePos = p_bitPos & 7;
  uint8_t bitFilter = (1 << (8 - firstBitInBytePos)) - 1;
  uint32_t value = byte & bitFilter;
  // next bytes...
  bytePos++;
  while(bytePos <= lastBytePos)
  {
    byte = buffer()[bytePos];
    value = (value << 8) + byte;
    bytePos++;
  }
  // last byte: remove the lowest bits that do not belong to the value
  uint8_t lastBitInBytePos = lastBitPos & 7;
  value >>= 7 - lastBitInBytePos;
  return value;
}

//-----------------------------------------------------------------------------
// sets bits as numerical unsigned value
void UTIL::DU::setBits(size_t p_bitPos,
                       size_t p_bitLength,
                       uint32_t p_value) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // performance optimizations:
  // - divide by 8 is replaced by >> 3 (performance)
  // - modulo 8 is replaced by & 7 (performance)
  // consistency checks
  if(m_buffer == NULL)
  {
    throw UTIL::Exception("DU is configured for Read Only");
  }
  if(p_bitLength == 0)
  {
    throw UTIL::Exception("invalid bitLength");
  }
  uint64_t maxValue = (1L << p_bitLength) - 1;
  if(p_value > maxValue)
  {
    throw UTIL::Exception("value out of range");
  }
  size_t lastBitPos = p_bitPos + p_bitLength - 1;
  size_t lastBytePos = lastBitPos >> 3;
  if(lastBytePos >= bufferSize())
  {
    throw UTIL::Exception("bitPos/bitLength out of buffer");
  }
  // set zero-bits in the buffer where the value aligns
  size_t firstBytePos = p_bitPos >> 3;
  uint8_t firstBitInBytePos = p_bitPos & 7;
  uint8_t lastBitInBytePos = lastBitPos & 7;
  size_t bytePos = firstBytePos;
  if(firstBytePos == lastBytePos)
  {
    m_buffer[bytePos] &= BIT_FILTER[firstBitInBytePos][lastBitInBytePos];
  }
  else
  {
    m_buffer[bytePos] &= BIT_FILTER[firstBitInBytePos][7];
    bytePos++;
    while(bytePos < lastBytePos)
    {
      m_buffer[bytePos] = 0;
      bytePos++;
    }
    m_buffer[bytePos] &= BIT_FILTER[0][lastBitInBytePos];
  }
  // fill value with trailing zero-bits to align with the position
  uint64_t value = p_value;
  value <<= 7 - lastBitInBytePos;
  // decompose the value and add it to the buffer
  // starting at bytePos, which is at the last byte
  while(bytePos >= firstBytePos)
  {
    uint8_t byte = value & 0xFF;
    m_buffer[bytePos] += byte;
    value >>= 8;
    if(bytePos == 0)
    {
      break;
    }
    bytePos--;
  }
}

//-----------------------------------------------------------------------------
uint32_t UTIL::DU::get(BitAccessor p_acc) const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return getBits(p_acc.bitPos, p_acc.bitLength);
}

//-----------------------------------------------------------------------------
void UTIL::DU::set(BitAccessor p_acc, uint32_t p_value) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  setBits(p_acc.bitPos, p_acc.bitLength, p_value);
}

//-----------------------------------------------------------------------------
// extract bytes
const uint8_t* UTIL::DU::getBytes(size_t p_bytePos,
                                  size_t p_byteLength)
  const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // consistency checks
  if(p_byteLength == 0)
  {
    throw UTIL::Exception("invalid byteLength");
  }
  if((p_bytePos + p_byteLength) > bufferSize())
  {
    throw UTIL::Exception("bytePos/byteLength out of buffer");
  }
  return (buffer() + p_bytePos);
}

//-----------------------------------------------------------------------------
// set bytes
void UTIL::DU::setBytes(size_t p_bytePos,
                        size_t p_byteLength,
                        const void* p_bytes) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // consistency checks
  if(m_buffer == NULL)
  {
    throw UTIL::Exception("DU is configured for Read Only");
  }
  if(p_byteLength == 0)
  {
    throw UTIL::Exception("invalid byteLength");
  }
  if((p_bytePos + p_byteLength) > bufferSize())
  {
    throw UTIL::Exception("bytePos/byteLength out of buffer");
  }
  memcpy(m_buffer + p_bytePos, p_bytes, p_byteLength);
}

//-----------------------------------------------------------------------------
const uint8_t* UTIL::DU::get(ByteAccessor p_acc) const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return getBytes(p_acc.bytePos, p_acc.byteLength);
}

//-----------------------------------------------------------------------------
void UTIL::DU::set(ByteAccessor p_acc, const void* p_bytes)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  setBytes(p_acc.bytePos, p_acc.byteLength, p_bytes);
}

//-----------------------------------------------------------------------------
// extracts a numerical unsigned value byte aligned
uint32_t UTIL::DU::getUnsigned(size_t p_bytePos,
                               size_t p_byteLength) const
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // consistency checks
  if((p_byteLength == 0) || (p_byteLength > 4))
  {
    throw UTIL::Exception("invalid byteLength");
  }
  size_t lastBytePos = p_bytePos + p_byteLength - 1;
  if(lastBytePos >= bufferSize())
  {
    throw UTIL::Exception("bytePos/byteLength out of buffer");
  }
  // accumulate the number starting with the first byte
  uint32_t value = 0;
  while(p_bytePos <= lastBytePos)
  {
    uint8_t byte = buffer()[p_bytePos];
    value = (value << 8) + byte;
    p_bytePos++;
  }
  return value;
}

//-----------------------------------------------------------------------------
// set a numerical unsigned value byte aligned
void UTIL::DU::setUnsigned(size_t p_bytePos,
                           size_t p_byteLength,
                           uint32_t p_value) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // consistency checks
  if(m_buffer == NULL)
  {
    throw UTIL::Exception("DU is configured for Read Only");
  }
  if((p_byteLength == 0) || (p_byteLength > 4))
  {
    throw UTIL::Exception("invalid byteLength");
  }
  if(((p_byteLength == 1) && (p_value > 255)) || 
     ((p_byteLength == 2) && (p_value > 65535)) || 
     ((p_byteLength == 3) && (p_value > 16777215)))
  {
    throw UTIL::Exception("value out of range");
  }
  if((p_bytePos + p_byteLength) > bufferSize())
  {
    throw UTIL::Exception("bytePos/byteLength out of buffer");
  }
  // decompose the value and add it to the buffer
  // starting at bytePos, which is at the last byte
  size_t firstBytePos = p_bytePos;
  p_bytePos = firstBytePos + p_byteLength - 1;
  while(p_bytePos >= firstBytePos)
  {
    uint8_t byte = (uint8_t) p_value & 0xFF;
    m_buffer[p_bytePos] = byte;
    p_value >>= 8;
    if(p_bytePos == 0)
    {
      break;
    }
    p_bytePos--;
  }
}

//-----------------------------------------------------------------------------
uint32_t UTIL::DU::get(UnsignedAccessor p_acc) const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return getUnsigned(p_acc.bytePos, p_acc.byteLength);
}

//-----------------------------------------------------------------------------
void UTIL::DU::set(UnsignedAccessor p_acc, uint32_t p_value)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  setUnsigned(p_acc.bytePos, p_acc.byteLength, p_value);
}

//-----------------------------------------------------------------------------
// extracts a numerical big unsigned value byte aligned
uint64_t UTIL::DU::getBigUnsigned(size_t p_bytePos,
                                  size_t p_byteLength) const
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // consistency checks
  if((p_byteLength == 0) || (p_byteLength > 8))
  {
    throw UTIL::Exception("invalid byteLength");
  }
  size_t lastBytePos = p_bytePos + p_byteLength - 1;
  if(lastBytePos >= bufferSize())
  {
    throw UTIL::Exception("bytePos/byteLength out of buffer");
  }
  // accumulate the number starting with the first byte
  uint64_t value = 0;
  while(p_bytePos <= lastBytePos)
  {
    uint8_t byte = buffer()[p_bytePos];
    value = (value << 8) + byte;
    p_bytePos++;
  }
  return value;
}

//-----------------------------------------------------------------------------
// set a numerical big unsigned value byte aligned
void UTIL::DU::setBigUnsigned(size_t p_bytePos,
                              size_t p_byteLength,
                              uint64_t p_value) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // consistency checks
  if(m_buffer == NULL)
  {
    throw UTIL::Exception("DU is configured for Read Only");
  }
  if((p_byteLength == 0) || (p_byteLength > 8))
  {
    throw UTIL::Exception("invalid byteLength");
  }
  if(((p_byteLength == 1) && (p_value > 255)) || 
     ((p_byteLength == 2) && (p_value > 65535)) || 
     ((p_byteLength == 3) && (p_value > 16777215)) ||
     ((p_byteLength == 4) && (p_value > 4294967295)) ||
     ((p_byteLength == 5) && (p_value > 1099511627775)) ||
     ((p_byteLength == 6) && (p_value > 281474976710655)) ||
     ((p_byteLength == 7) && (p_value > 72057594037927935)))
  {
    throw UTIL::Exception("value out of range");
  }
  if((p_bytePos + p_byteLength) > bufferSize())
  {
    throw UTIL::Exception("bytePos/byteLength out of buffer");
  }
  // decompose the value and add it to the buffer
  // starting at bytePos, which is at the last byte
  size_t firstBytePos = p_bytePos;
  p_bytePos = firstBytePos + p_byteLength - 1;
  while(p_bytePos >= firstBytePos)
  {
    uint8_t byte = (uint8_t) p_value & 0xFF;
    m_buffer[p_bytePos] = byte;
    p_value >>= 8;
    if(p_bytePos == 0)
    {
      break;
    }
    p_bytePos--;
  }
}

//-----------------------------------------------------------------------------
uint64_t UTIL::DU::get(BigUnsignedAccessor p_acc) const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return getBigUnsigned(p_acc.bytePos, p_acc.byteLength);
}

//-----------------------------------------------------------------------------
void UTIL::DU::set(BigUnsignedAccessor p_acc, uint64_t p_value)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  setBigUnsigned(p_acc.bytePos, p_acc.byteLength, p_value);
}

//-----------------------------------------------------------------------------
// set a fixed size string
std::string UTIL::DU::getString(size_t p_bytePos,
                                size_t p_byteLength) const
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // consistency checks
  if(p_byteLength == 0)
  {
    throw UTIL::Exception("invalid byteLength");
  }
  if((p_bytePos + p_byteLength) > bufferSize())
  {
    throw UTIL::Exception("bytePos/byteLength out of buffer");
  }
  // copy the bytes from the buffer into retString
  const char* str = (const char*) (m_buffer + p_bytePos);
  return std::string(str, p_byteLength);
}

//-----------------------------------------------------------------------------
// get a fixed sized string
void UTIL::DU::setString(size_t p_bytePos,
                         size_t p_byteLength,
                         const std::string& p_string) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // consistency checks
  if(m_buffer == NULL)
  {
    throw UTIL::Exception("DU is configured for Read Only");
  }
  if(p_byteLength == 0)
  {
    throw UTIL::Exception("invalid byteLength");
  }
  size_t stringSize = p_string.size();
  if(stringSize > p_byteLength)
  {
    throw UTIL::Exception("string size out of range");
  }
  if((p_bytePos + p_byteLength) > bufferSize())
  {
    throw UTIL::Exception("bytePos/byteLength out of buffer");
  }
  // copy the bytes from p_string
  size_t i = 0;
  for(; i < stringSize; i++)
  {
    uint8_t byte = (uint8_t) p_string[i];
    m_buffer[p_bytePos + i] = byte;
  }
  // fill up with null characters
  for(; i < p_byteLength; i++)
  {
    m_buffer[p_bytePos + i] = 0;
  }
}

//-----------------------------------------------------------------------------
std::string UTIL::DU::get(StringAccessor p_acc) const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return getString(p_acc.bytePos, p_acc.byteLength);
}

//-----------------------------------------------------------------------------
void UTIL::DU::set(StringAccessor p_acc, const std::string& p_string)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  setString(p_acc.bytePos, p_acc.byteLength, p_string);
}

//-----------------------------------------------------------------------------
UTIL::AbsTime UTIL::DU::getAbsTime(size_t, uint32_t) const
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  throw UTIL::Exception("UTIL::DU::getAbsTime must be overloaded in subclass");
}

//-----------------------------------------------------------------------------
void UTIL::DU::setAbsTime(size_t, uint32_t, const UTIL::AbsTime&)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  throw UTIL::Exception("UTIL::DU::setAbsTime must be overloaded in subclass");
}

//-----------------------------------------------------------------------------
UTIL::AbsTime UTIL::DU::get(AbsTimeAccessor p_acc) const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  return getAbsTime(p_acc.bytePos, p_acc.timeCode);
}

//-----------------------------------------------------------------------------
void UTIL::DU::set(AbsTimeAccessor p_acc, const UTIL::AbsTime& p_time)
  throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  setAbsTime(p_acc.bytePos, p_acc.timeCode, p_time);
}

//-----------------------------------------------------------------------------
UTIL::DU UTIL::operator+(const UTIL::DU& p_du1, const UTIL::DU& p_du2)
//-----------------------------------------------------------------------------
{
  UTIL::DU retVal(p_du1);
  retVal.append(p_du2);
  return retVal;
}

//-----------------------------------------------------------------------------
bool UTIL::operator==(const UTIL::DU& p_du1, const UTIL::DU& p_du2)
//-----------------------------------------------------------------------------
{
  return (p_du1.compare(p_du2) == 0);
}

//-----------------------------------------------------------------------------
bool UTIL::operator!=(const UTIL::DU& p_du1, const UTIL::DU& p_du2)
//-----------------------------------------------------------------------------
{
  return (p_du1.compare(p_du2) != 0);
}

//-----------------------------------------------------------------------------
bool UTIL::operator< (const UTIL::DU& p_du1, const UTIL::DU& p_du2)
//-----------------------------------------------------------------------------
{
  return (p_du1.compare(p_du2) < 0);
}

//-----------------------------------------------------------------------------
bool UTIL::operator> (const UTIL::DU& p_du1, const UTIL::DU& p_du2)
//-----------------------------------------------------------------------------
{
  return (p_du1.compare(p_du2) > 0);
}

//-----------------------------------------------------------------------------
bool UTIL::operator<=(const UTIL::DU& p_du1, const UTIL::DU& p_du2)
//-----------------------------------------------------------------------------
{
  return (p_du1.compare(p_du2) <= 0);
}

//-----------------------------------------------------------------------------
bool UTIL::operator>=(const UTIL::DU& p_du1, const UTIL::DU& p_du2)
//-----------------------------------------------------------------------------
{
  return (p_du1.compare(p_du2) >= 0);
}
