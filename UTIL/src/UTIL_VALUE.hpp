//*****************************************************************************
// (C) 2015, Stefan Korner, Austria                                           *
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
// Utilities - Generic Value                                                  *
//*****************************************************************************
#ifndef UTIL_VALUE_hpp
#define UTIL_VALUE_hpp

#include <stdint.h>
#include <string>
#include "UTIL_EXCEPTION.hpp"
#include "UTIL_TIME.hpp"

namespace UTIL
{
  //---------------------------------------------------------------------------
  enum ValueType
  //---------------------------------------------------------------------------
  {
    NO_VALUE,
    BOOLEAN,
    INT8,
    INT16,
    INT32,
    INT64,
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    FLOAT,
    DOUBLE,
    ASCII_STRING,
    OCTET_STRING,
    ABS_TIME,
    REL_TIME
  };
  
  //---------------------------------------------------------------------------
  class Value
  //---------------------------------------------------------------------------
  {
  public:
    // constructors and destructur
    Value();
    Value(const Value& p_value);
    Value(ValueType p_valueType);
    Value(bool p_value);
    Value(int8_t p_value);
    Value(int16_t p_value);
    Value(int32_t p_value);
    Value(int64_t p_value);
    Value(uint8_t p_value);
    Value(uint16_t p_value);
    Value(uint32_t p_value);
    Value(uint64_t p_value);
    Value(float p_value);
    Value(double p_value);
    Value(const char* p_value);
    Value(const std::string& p_value);
    Value(const void* p_buffer, size_t p_size);
    Value(const AbsTime& p_value);
    Value(const RelTime& p_value);
    const Value& operator=(const Value& p_value);
    ~Value();

    // helpers
    ValueType getValueType() const;
    void setValueType(ValueType p_valueType);
    std::string dumpStr(const char* p_prefix = NULL) const;
    void dump(const char* p_prefix = NULL) const;

    // setters / getters
    void set();
    void set(bool p_value);
    void set(int8_t p_value);
    void set(int16_t p_value);
    void set(int32_t p_value);
    void set(int64_t p_value);
    void set(uint8_t p_value);
    void set(uint16_t p_value);
    void set(uint32_t p_value);
    void set(uint64_t p_value);
    void set(float p_value);
    void set(double p_value);
    void set(const char* p_value);
    void set(const std::string& p_value);
    void set(const void* p_buffer, size_t p_size);
    void set(const AbsTime& p_value);
    void set(const RelTime& p_value);
    bool getBoolean() const throw(UTIL::Exception);
    int8_t getInt8() const throw(Exception);
    int16_t getInt16() const throw(Exception);
    int32_t getInt32() const throw(Exception);
    int64_t getInt64() const throw(Exception);
    uint8_t getUInt8() const throw(Exception);
    uint16_t getUInt16() const throw(Exception);
    uint32_t getUInt32() const throw(Exception);
    uint64_t getUInt64() const throw(Exception);
    float getFloat() const throw(Exception);
    double getDouble() const throw(Exception);
    std::string getAsciiString() const throw(Exception);
    const uint8_t* getOctetString() const throw(Exception);
    size_t getOctetStringLength() const throw(Exception);
    AbsTime getAbsTime() const throw(Exception);
    RelTime getRelTime() const throw(Exception);

  private:
    ValueType m_valueType;
    uint64_t m_number;
    uint8_t* m_buffer;
  };
}

#endif
