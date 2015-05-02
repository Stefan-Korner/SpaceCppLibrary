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
#include "UTIL_VALUE.hpp"

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define FORCE_UINT64(VAL) *reinterpret_cast<const uint64_t*>(&VAL)
#define FORCE_DOUBLE(VAL) *reinterpret_cast<const double*>(&VAL)

//-----------------------------------------------------------------------------
UTIL::Value::Value(): m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::Value::Value(const UTIL::Value& p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  operator=(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(UTIL::ValueType p_valueType):
  m_valueType(p_valueType), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
UTIL::Value::Value(bool p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(int8_t p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(int16_t p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(int32_t p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(int64_t p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(uint8_t p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(uint16_t p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(uint32_t p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(uint64_t p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(float p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(double p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(const char* p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(const string& p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(const void* p_buffer, size_t p_size):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_buffer, p_size);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(const UTIL::AbsTime& p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
UTIL::Value::Value(const UTIL::RelTime& p_value):
  m_valueType(UTIL::NO_VALUE), m_number(0), m_buffer(NULL)
//-----------------------------------------------------------------------------
{
  set(p_value);
}

//-----------------------------------------------------------------------------
const UTIL::Value& UTIL::Value::operator=(const UTIL::Value& p_value)
//-----------------------------------------------------------------------------
{
  if(&p_value != this)
  {
    // delete the old contents
    set();
    // copy the new contents
    m_valueType = p_value.m_valueType;
    m_number = p_value.m_number;
    if(p_value.m_buffer != NULL)
    {
      m_buffer = new uint8_t[m_number];
      memcpy(m_buffer, p_value.m_buffer, m_number);
    }
  }
  return *this;
}

//-----------------------------------------------------------------------------
UTIL::Value::~Value()
//-----------------------------------------------------------------------------
{
  // delete contents
  set();
}

//-----------------------------------------------------------------------------
UTIL::ValueType UTIL::Value::getValueType() const
//-----------------------------------------------------------------------------
{
  return m_valueType;
}

//-----------------------------------------------------------------------------
void UTIL::Value::setValueType(UTIL::ValueType p_valueType)
//-----------------------------------------------------------------------------
{
  // delete contents
  set();
  // set value type
  m_valueType = p_valueType;
}

//-----------------------------------------------------------------------------
string UTIL::Value::dumpStr(const char* p_prefix) const
//-----------------------------------------------------------------------------
{
  ostringstream ostr;
  if(p_prefix != NULL)
  {
    ostr << p_prefix;
  }
  switch(m_valueType)
  {
  case NO_VALUE:
    ostr << "NO_VALUE";
    break;
  case BOOLEAN:
    ostr << "BOOLEAN(" << (getBoolean() ? "true" : "false") << ")";
    break;
  case INT8:
    ostr << "INT8(" << int16_t(getInt8()) << ")";
    break;
  case INT16:
    ostr << "INT16(" << getInt16() << ")";
    break;
  case INT32:
    ostr << "INT32(" << getInt32() << ")";
    break;
  case INT64:
    ostr << "INT64(" << getInt64() << ")";
    break;
  case UINT8:
    ostr << "UINT8(" << uint16_t(getUInt8()) << ")";
    break;
  case UINT16:
    ostr << "UINT16(" << getUInt16() << ")";
    break;
  case UINT32:
    ostr << "UINT32(" << getUInt32() << ")";
    break;
  case UINT64:
    ostr << "UINT64(" << getUInt64() << ")";
    break;
  case FLOAT:
    ostr << "FLOAT(" << getFloat() << ")";
    break;
  case DOUBLE:
    ostr << "DOUBLE(" << getDouble() << ")";
    break;
  case ASCII_STRING:
    ostr << "ASCII_STRING(\"" << getAsciiString() << "\")";
    break;
  case OCTET_STRING:
    ostr << "OCTET_STRING(" << m_number << ", ...)";
    break;
  case ABS_TIME:
    {
      uint32_t micro = uint32_t(m_number % 1000000);
      uint32_t sec = uint32_t(m_number / 1000000);
      ostr << "ABS_TIME(" << sec << ", " << micro << ")";
    }
    break;
  case REL_TIME:
    {
      int64_t relTimeVal = int64_t(m_number);
      if(relTimeVal >=0)
      {
        uint32_t micro = uint32_t(relTimeVal % 1000000);
        uint32_t sec = uint32_t(relTimeVal / 1000000);
        ostr << "REL_TIME(+ " << sec << ", " << micro << ")";
      }
      else
      {
        relTimeVal = -relTimeVal;
        uint32_t micro = uint32_t(relTimeVal % 1000000);
        uint32_t sec = uint32_t(relTimeVal / 1000000);
        ostr << "REL_TIME(- " << sec << ", " << micro << ")";
      }
    }
    break;
  }
  return ostr.str();
}

//-----------------------------------------------------------------------------
void UTIL::Value::dump(const char* p_prefix) const
//-----------------------------------------------------------------------------
{
  if(p_prefix != NULL)
  {
    cout << p_prefix;
  }
  switch(m_valueType)
  {
  case NO_VALUE:
    cout << "NO_VALUE";
    break;
  case BOOLEAN:
    cout << "BOOLEAN(" << (getBoolean() ? "true" : "false") << ")";
    break;
  case INT8:
    cout << "INT8(" << int16_t(getInt8()) << ")";
    break;
  case INT16:
    cout << "INT16(" << getInt16() << ")";
    break;
  case INT32:
    cout << "INT32(" << getInt32() << ")";
    break;
  case INT64:
    cout << "INT64(" << getInt64() << ")";
    break;
  case UINT8:
    cout << "UINT8(" << uint16_t(getUInt8()) << ")";
    break;
  case UINT16:
    cout << "UINT16(" << getUInt16() << ")";
    break;
  case UINT32:
    cout << "UINT32(" << getUInt32() << ")";
    break;
  case UINT64:
    cout << "UINT64(" << getUInt64() << ")";
    break;
  case FLOAT:
    cout << "FLOAT(" << getFloat() << ")";
    break;
  case DOUBLE:
    cout << "DOUBLE(" << getDouble() << ")";
    break;
  case ASCII_STRING:
    cout << "ASCII_STRING(\"" << getAsciiString() << "\")";
    break;
  case OCTET_STRING:
    cout << "OCTET_STRING(" << m_number << ", ...)";
    break;
  case ABS_TIME:
    {
      uint32_t micro = uint32_t(m_number % 1000000);
      uint32_t sec = uint32_t(m_number / 1000000);
      cout << "ABS_TIME(" << sec << ", " << micro << ")";
    }
    break;
  case REL_TIME:
    {
      int64_t relTimeVal = int64_t(m_number);
      if(relTimeVal >=0)
      {
        uint32_t micro = uint32_t(relTimeVal % 1000000);
        uint32_t sec = uint32_t(relTimeVal / 1000000);
        cout << "REL_TIME(+ " << sec << ", " << micro << ")";
      }
      else
      {
        relTimeVal = -relTimeVal;
        uint32_t micro = uint32_t(relTimeVal % 1000000);
        uint32_t sec = uint32_t(relTimeVal / 1000000);
        cout << "REL_TIME(- " << sec << ", " << micro << ")";
      }
    }
    break;
  }
  cout << endl;
}

//-----------------------------------------------------------------------------
void UTIL::Value::set()
//-----------------------------------------------------------------------------
{
  // delete the old contents
  if(m_buffer != NULL)
  {
   delete[] m_buffer;
  }
  // set the new contents
  m_valueType = UTIL::NO_VALUE;
  m_number = 0;
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(bool p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::BOOLEAN;
  m_number = p_value;
  m_buffer = NULL;
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(int8_t p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::INT8;
  m_number = uint64_t(int64_t(p_value));
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(int16_t p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::INT16;
  m_number = uint64_t(int64_t(p_value));
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(int32_t p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::INT32;
  m_number = uint64_t(int64_t(p_value));
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(int64_t p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::INT64;
  m_number = uint64_t(p_value);
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(uint8_t p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::UINT8;
  m_number = p_value;
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(uint16_t p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::UINT16;
  m_number = p_value;
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(uint32_t p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::UINT32;
  m_number = p_value;
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(uint64_t p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::UINT64;
  m_number = p_value;
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(float p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::FLOAT;
  double doubleVal = p_value;
  m_number = FORCE_UINT64(doubleVal);
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(double p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::DOUBLE;
  m_number = FORCE_UINT64(p_value);
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(const char* p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::ASCII_STRING;
  size_t size = strlen(p_value);
  m_number = uint64_t(size);
  m_buffer = new uint8_t[size];
  memcpy(m_buffer, p_value, size);
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(const string& p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::ASCII_STRING;
  size_t size = p_value.size();
  m_number = uint64_t(size);
  m_buffer = new uint8_t[size];
  memcpy(m_buffer, &p_value[0], size);
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(const void* p_buffer, size_t p_size)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set the new contents
  m_valueType = UTIL::OCTET_STRING;
  m_number = uint64_t(p_size);
  m_buffer = new uint8_t[p_size];
  memcpy(m_buffer, p_buffer, p_size);
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(const UTIL::AbsTime& p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set new contents
  m_valueType = UTIL::ABS_TIME;
  m_number = p_value.m_micro + 1000000 * p_value.m_sec;;
}

//-----------------------------------------------------------------------------
void UTIL::Value::set(const UTIL::RelTime& p_value)
//-----------------------------------------------------------------------------
{
  // delete the old contents
  set();
  // set new contents
  m_valueType = UTIL::REL_TIME;
  int64_t relTimeVal;
  if(p_value.m_sign == UTIL::POSITIVE)
  {
    relTimeVal = p_value.m_micro + 1000000 * p_value.m_sec;
  }
  else
  {
    relTimeVal = p_value.m_micro + 1000000 * p_value.m_sec;
    relTimeVal = -relTimeVal;
  }
  m_number = uint64_t(relTimeVal);
}

//-----------------------------------------------------------------------------
bool UTIL::Value::getBoolean() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(m_valueType != UTIL::BOOLEAN)
  {
    throw UTIL::Exception("UTIL::Value does not contain an boolean");
  }
  return (m_number != 0);
}

//-----------------------------------------------------------------------------
int8_t UTIL::Value::getInt8() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(m_valueType != UTIL::INT8)
  {
    throw UTIL::Exception("UTIL::Value does not contain an int8 number");
  }
  return int8_t(m_number);
}

//-----------------------------------------------------------------------------
int16_t UTIL::Value::getInt16() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if((m_valueType != UTIL::INT16) && (m_valueType != UTIL::INT8))
  {
    throw UTIL::Exception("UTIL::Value does not contain an int16 number");
  }
  return int16_t(m_number);
}

//-----------------------------------------------------------------------------
int32_t UTIL::Value::getInt32() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if((m_valueType != UTIL::INT32) && (m_valueType != UTIL::INT16) &&
     (m_valueType != UTIL::INT8))
  {
    throw UTIL::Exception("UTIL::Value does not contain an int32 number");
  }
  return int32_t(m_number);
}

//-----------------------------------------------------------------------------
int64_t UTIL::Value::getInt64() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if((m_valueType != UTIL::INT64) && (m_valueType != UTIL::INT32) &&
     (m_valueType != UTIL::INT16) && (m_valueType != UTIL::INT8))
  {
    throw UTIL::Exception("UTIL::Value does not contain an int64 number");
  }
  return int64_t(m_number);
}

//-----------------------------------------------------------------------------
uint8_t UTIL::Value::getUInt8() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(m_valueType != UTIL::UINT8)
  {
    throw UTIL::Exception("UTIL::Value does not contain an uint8 number");
  }
  return uint8_t(m_number);
}

//-----------------------------------------------------------------------------
uint16_t UTIL::Value::getUInt16() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if((m_valueType != UTIL::UINT16) && (m_valueType != UTIL::UINT8))
  {
    throw UTIL::Exception("UTIL::Value does not contain an uint16 number");
  }
  return uint16_t(m_number);
}

//-----------------------------------------------------------------------------
uint32_t UTIL::Value::getUInt32() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if((m_valueType != UTIL::UINT32) && (m_valueType != UTIL::UINT16) &&
     (m_valueType != UTIL::UINT8))
  {
    throw UTIL::Exception("UTIL::Value does not contain an uint32 number");
  }
  return uint32_t(m_number);
}

//-----------------------------------------------------------------------------
uint64_t UTIL::Value::getUInt64() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if((m_valueType != UTIL::UINT64) && (m_valueType != UTIL::UINT32) &&
     (m_valueType != UTIL::UINT16) && (m_valueType != UTIL::UINT8))
  {
    throw UTIL::Exception("UTIL::Value does not contain an uint64 number");
  }
  return m_number;
}

//-----------------------------------------------------------------------------
float UTIL::Value::getFloat() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(m_valueType != UTIL::FLOAT)
  {
    throw UTIL::Exception("UTIL::Value does not contain a float number");
  }
  return float(FORCE_DOUBLE(m_number));
}

//-----------------------------------------------------------------------------
double UTIL::Value::getDouble() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if((m_valueType != UTIL::DOUBLE) && (m_valueType != UTIL::FLOAT))
  {
    throw UTIL::Exception("UTIL::Value does not contain a double number");
  }
  return FORCE_DOUBLE(m_number);
}

//-----------------------------------------------------------------------------
string UTIL::Value::getAsciiString() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(m_valueType != UTIL::ASCII_STRING)
  {
    throw UTIL::Exception("UTIL::Value does not contain an ascii string");
  }
  return string((const char*) m_buffer, size_t(m_number));
}

//-----------------------------------------------------------------------------
const uint8_t* UTIL::Value::getOctetString() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(m_valueType != UTIL::OCTET_STRING)
  {
    throw UTIL::Exception("UTIL::Value does not contain an octet string");
  }
  return m_buffer;
}

//-----------------------------------------------------------------------------
size_t UTIL::Value::getOctetStringLength() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(m_valueType != UTIL::OCTET_STRING)
  {
    throw UTIL::Exception("UTIL::Value does not contain an octet string");
  }
  return size_t(m_number);
}

//-----------------------------------------------------------------------------
UTIL::AbsTime UTIL::Value::getAbsTime() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(m_valueType != UTIL::ABS_TIME)
  {
    throw UTIL::Exception("UTIL::Value does not contain an absolute time");
  }
  UTIL::AbsTime retVal;
  retVal.m_micro = uint32_t(m_number % 1000000);
  retVal.m_sec = uint32_t(m_number / 1000000);
  return retVal;  
}

//-----------------------------------------------------------------------------
UTIL::RelTime UTIL::Value::getRelTime() const throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(m_valueType != UTIL::REL_TIME)
  {
    throw UTIL::Exception("UTIL::Value does not contain a relative time");
  }
  UTIL::RelTime retVal;
  int64_t relTimeVal = int64_t(m_number);
  if(relTimeVal >=0)
  {
    retVal.m_sign = UTIL::POSITIVE;
    retVal.m_micro = uint32_t(relTimeVal % 1000000);
    retVal.m_sec = uint32_t(relTimeVal / 1000000);
  }
  else
  {
    retVal.m_sign = UTIL::NEGATIVE;
    relTimeVal = -relTimeVal;
    retVal.m_micro = uint32_t(relTimeVal % 1000000);
    retVal.m_sec = uint32_t(relTimeVal / 1000000);
  }
  return retVal;  
}
