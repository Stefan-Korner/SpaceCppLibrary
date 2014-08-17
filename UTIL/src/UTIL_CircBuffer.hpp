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
#ifndef UTIL_CircBuffer_hpp
#define UTIL_CircBuffer_hpp

#include <stddef.h>
#include <stdint.h>

namespace UTIL
{
  //---------------------------------------------------------------------------
  class CircBuffer
  //---------------------------------------------------------------------------
  {
  public:
    // constructors and destructur
    CircBuffer(size_t p_bufferSize = 256);
    CircBuffer(const CircBuffer& p_other);
    const CircBuffer& operator=(const CircBuffer& p_other);
    virtual ~CircBuffer();

    // buffer access
    virtual size_t size() const;
    virtual size_t freeSize() const;
    virtual bool pushBack(const void* p_data, size_t p_dataSize);
    virtual bool popFront(size_t p_dataSize);
    virtual uint8_t operator[](size_t p_index) const;
  private:
    uint8_t* m_buffer;
    size_t m_bufferSize;
    size_t m_firstPos;
    size_t m_freePos;
  };
}

#endif
