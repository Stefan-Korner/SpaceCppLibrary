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
#ifndef UTIL_DU_hpp
#define UTIL_DU_hpp

#include <stdint.h>
#include <string>
#include "UTIL_EXCEPTION.hpp"

namespace UTIL
{
  //---------------------------------------------------------------------------
  class DU
  //---------------------------------------------------------------------------
  {
  public:
    // accessors for different types
    struct BitAccessor
    {
      size_t bitPos;
      size_t bitLength;
    };
    struct ByteAccessor
    {
      size_t bytePos;
      size_t byteLength;
    };
    struct UnsignedAccessor
    {
      size_t bytePos;
      size_t byteLength;
    };

    // constructors and destructur
    DU();
    DU(size_t p_bufferSize);
    DU(void* p_buffer, size_t p_bufferSize);
    DU(const void* p_buffer, size_t p_bufferSize, bool p_copyBuffer);
    DU(const DU& p_du);
    const DU& operator=(const DU& p_du);
    virtual ~DU();

    // buffer access
    virtual void init(size_t p_bufferSize);
    virtual void init(void* p_buffer, size_t p_bufferSize);
    virtual void init(const void* p_buffer,
                      size_t p_bufferSize,
                      bool p_copyBuffer);
    virtual void init(const DU& p_du);
    virtual void append(const DU& p_du);
    virtual void clear();
    virtual void resize(size_t p_bufferSize) throw(UTIL::Exception);
    virtual uint8_t* release(size_t& p_bufferSize);
    virtual const uint8_t* buffer() const;
    virtual size_t bufferSize() const;
    virtual const uint8_t& operator[](size_t p_bytePos) const
      throw(UTIL::Exception);
    virtual uint8_t& operator[](size_t p_bytePos) throw(UTIL::Exception);

    // helpers
    virtual int compare(const DU& p_du) const;
    virtual std::string dumpStr(const char* p_prefix = NULL,
                                bool p_withAbsoluteAddress = false) const;
    virtual void dump(const char* p_prefix = NULL,
                      bool p_withAbsoluteAddress = false) const;

    // bit aligned access
    virtual uint32_t getBits(size_t p_bitPos,
                             size_t p_bitLength) const throw(UTIL::Exception);
    virtual void setBits(size_t p_bitPos,
                         size_t p_bitLength,
                         uint32_t p_value) throw(UTIL::Exception);
    virtual uint32_t get(BitAccessor p_acc) const throw(UTIL::Exception);
    virtual void set(BitAccessor p_acc, uint32_t p_value)
      throw(UTIL::Exception);

    // bit aligned access
    virtual const uint8_t* getBytes(size_t p_bytePos,
                                    size_t p_byteLength) const
      throw(UTIL::Exception);
    virtual void setBytes(size_t p_bytePos,
                          size_t p_byteLength,
                          const void* p_bytes) throw(UTIL::Exception);
    virtual const uint8_t* get(ByteAccessor p_acc) const
      throw(UTIL::Exception);
    virtual void set(ByteAccessor p_acc, const void* p_bytes)
      throw(UTIL::Exception);

    // unsigned integer access
    virtual uint32_t getUnsigned(size_t p_bytePos,
                                 size_t p_byteLength)
      const throw(UTIL::Exception);
    virtual void setUnsigned(size_t p_bytePos,
                             size_t p_byteLength,
                             uint32_t p_value) throw(UTIL::Exception);
    virtual uint32_t get(UnsignedAccessor p_acc) const throw(UTIL::Exception);
    virtual void set(UnsignedAccessor p_acc, uint32_t p_value)
      throw(UTIL::Exception);

  private:
    uint8_t* m_buffer;
    const uint8_t* m_constBuffer;
    size_t m_bufferSize;
    size_t m_usedBufferSize;
  };

  // add operator
  DU operator+(const DU& p_du1, const DU& p_du2);

  // compare operators
  bool operator==(const DU& p_du1, const DU& p_du2);
  bool operator!=(const DU& p_du1, const DU& p_du2);
  bool operator< (const DU& p_du1, const DU& p_du2);
  bool operator> (const DU& p_du1, const DU& p_du2);
  bool operator<=(const DU& p_du1, const DU& p_du2);
  bool operator>=(const DU& p_du1, const DU& p_du2);
}

#endif
