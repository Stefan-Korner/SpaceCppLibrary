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
// Utilities - Time types                                                     *
//                                                                            *
// Type save distinction between absolute and relative time                   *
//*****************************************************************************
#ifndef UTIL_TIME_hpp
#define UTIL_TIME_hpp

#include <stdint.h>

namespace UTIL
{
  enum Sign {POSITIVE, NEGATIVE};

  // absolute time
  struct AbsTime
  {
    uint32_t m_sec;
    uint32_t m_micro;
    AbsTime(): m_sec(0), m_micro(0) {}
    AbsTime(uint32_t p_sec, uint32_t p_micro):
      m_sec(p_sec), m_micro(p_micro) {}
  };

  // relative time
  struct RelTime
  {
    Sign m_sign;
    uint32_t m_sec;
    uint32_t m_micro;
    RelTime(): m_sign(POSITIVE), m_sec(0), m_micro(0) {}
    RelTime(Sign p_sign, uint32_t p_sec, uint32_t p_micro):
      m_sign(p_sign), m_sec(p_sec), m_micro(p_micro) {}
  };
};

#endif
