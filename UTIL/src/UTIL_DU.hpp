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
#include "UTIL_TIME.hpp"

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
    struct VarByteAccessor
    {
      size_t bytePos;
    };
    struct UnsignedAccessor
    {
      size_t bytePos;
      size_t byteLength;
    };
    struct BigUnsignedAccessor
    {
      size_t bytePos;
      size_t byteLength;
    };
    struct StringAccessor
    {
      size_t bytePos;
      size_t byteLength;
    };
    struct VarStringAccessor
    {
      size_t bytePos;
    };
    struct AbsTimeAccessor
    {
      size_t bytePos;
      uint32_t timeCode;
    };

    // helper for variable byte array access
    struct VarByteHelper
    {
      size_t byteLength;
      const uint8_t* bytes;
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
    virtual bool bufferIsReadonly() const;
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
    uint32_t get(BitAccessor p_acc) const throw(UTIL::Exception);
    void set(BitAccessor p_acc, uint32_t p_value) throw(UTIL::Exception);

    // byte aligned access
    virtual const uint8_t* getBytes(size_t p_bytePos,
                                    size_t p_byteLength) const
      throw(UTIL::Exception);
    virtual void setBytes(size_t p_bytePos,
                          size_t p_byteLength,
                          const void* p_bytes) throw(UTIL::Exception);
    const uint8_t* get(ByteAccessor p_acc) const throw(UTIL::Exception);
    void set(ByteAccessor p_acc, const void* p_bytes) throw(UTIL::Exception);

    // variable byte array access
    // shall be overloaded in derived class (this impl. raises an exception)
    virtual VarByteHelper getVarBytes(size_t p_bytePos) const
      throw(UTIL::Exception);
    // shall be overloaded in derived class (this impl. raises an exception)
    virtual void setVarBytes(size_t p_bytePos,
                             size_t p_byteLength,
                             const void* p_bytes) throw(UTIL::Exception);
    VarByteHelper get(VarByteAccessor p_acc) const throw(UTIL::Exception);
    void set(VarByteAccessor p_acc, size_t p_byteLength, const void* p_bytes)
      throw(UTIL::Exception);

    // unsigned integer access
    virtual uint32_t getUnsigned(size_t p_bytePos,
                                 size_t p_byteLength)
      const throw(UTIL::Exception);
    virtual void setUnsigned(size_t p_bytePos,
                             size_t p_byteLength,
                             uint32_t p_value) throw(UTIL::Exception);
    uint32_t get(UnsignedAccessor p_acc) const throw(UTIL::Exception);
    void set(UnsignedAccessor p_acc, uint32_t p_value) throw(UTIL::Exception);

    // big unsigned integer access
    virtual uint64_t getBigUnsigned(size_t p_bytePos,
                                    size_t p_byteLength) const
      throw(UTIL::Exception);
    virtual void setBigUnsigned(size_t p_bytePos,
                                size_t p_byteLength,
                                uint64_t p_value) throw(UTIL::Exception);
    uint64_t get(BigUnsignedAccessor p_acc) const throw(UTIL::Exception);
    void set(BigUnsignedAccessor p_acc, uint64_t p_value)
      throw(UTIL::Exception);

    // fixed size string access
    // smaller sized strings may be passed with setString() and set(),
    // in this case the remaining bytes are filled up null characters
    virtual std::string getString(size_t p_bytePos,
                                  size_t p_byteLength) const
      throw(UTIL::Exception);
    virtual void setString(size_t p_bytePos,
                           size_t p_byteLength,
                           const std::string& p_string)
      throw(UTIL::Exception);
    std::string get(StringAccessor p_acc) const throw(UTIL::Exception);
    void set(StringAccessor p_acc, const std::string& p_string)
      throw(UTIL::Exception);

    // variable size string access
    // shall be overloaded in derived class (this impl. raises an exception)
    virtual std::string getVarString(size_t p_bytePos) const
      throw(UTIL::Exception);
    // shall be overloaded in derived class (this impl. raises an exception)
    virtual void setVarString(size_t p_bytePos, const std::string& p_string)
      throw(UTIL::Exception);
    std::string get(VarStringAccessor p_acc) const throw(UTIL::Exception);
    void set(VarStringAccessor p_acc, const std::string& p_string)
      throw(UTIL::Exception);

    // absolute time access
    // shall be overloaded in derived class (this impl. raises an exception)
    virtual UTIL::AbsTime getAbsTime(size_t p_bytePos,
                                     uint32_t p_timeCode) const
      throw(UTIL::Exception);
    // shall be overloaded in derived class (this impl. raises an exception)
    virtual void setAbsTime(size_t p_bytePos,
                            uint32_t p_timeCode,
                            const UTIL::AbsTime& p_time)
      throw(UTIL::Exception);
    UTIL::AbsTime get(AbsTimeAccessor p_acc) const throw(UTIL::Exception);
    void set(AbsTimeAccessor p_acc, const UTIL::AbsTime& p_time)
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
