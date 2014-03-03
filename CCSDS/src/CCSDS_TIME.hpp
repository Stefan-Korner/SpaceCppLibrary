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
// CCSDS TIME - Conversion                                                    *
//*****************************************************************************
#ifndef CCSDS_TIME_hpp
#define CCSDS_TIME_hpp

#include "UTIL_TIME.hpp"
#include "UTIL_EXCEPTION.hpp"

namespace CCSDS
{
  namespace CUC
  {
    typedef uint8_t TimeCode;
    // supported time codes
    static const TimeCode L1_TIME_4_0 = 0x1C; // epoch: 1.1.1958, 0 fine byte
    static const TimeCode L1_TIME_4_1 = 0x1D; // epoch: 1.1.1958, 1 fine byte
    static const TimeCode L1_TIME_4_2 = 0x1E; // epoch: 1.1.1958, 2 fine bytes
    static const TimeCode L1_TIME_4_3 = 0x1F; // epoch: 1.1.1958, 3 fine bytes
    static const TimeCode L2_TIME_4_0 = 0x2C; // epoch: agency-def., 0 fine b.
    static const TimeCode L2_TIME_4_1 = 0x2D; // epoch: agency-def., 1 fine b.
    static const TimeCode L2_TIME_4_2 = 0x2E; // epoch: agency-def., 2 fine b.
    static const TimeCode L2_TIME_4_3 = 0x2F; // epoch: agency-def., 3 fine b.

    struct Time
    {
      TimeCode m_pField;
      uint8_t m_tCoarse0;
      uint8_t m_tCoarse1;
      uint8_t m_tCoarse2;
      uint8_t m_tCoarse3;
      uint8_t m_tFine0;
      uint8_t m_tFine1;
      uint8_t m_tFine2;
      Time(): m_pField(0),
              m_tCoarse0(0), m_tCoarse1(0), m_tCoarse2(0), m_tCoarse3(0),
              m_tFine0(0), m_tFine1(0), m_tFine2(0) {}
      Time(TimeCode p_pField,
           uint8_t p_tCoarse0,
           uint8_t p_tCoarse1,
           uint8_t p_tCoarse2,
           uint8_t p_tCoarse3,
           uint8_t p_tFine0,
           uint8_t p_tFine1,
           uint8_t p_tFine2):
        m_pField(p_pField),
        m_tCoarse0(p_tCoarse0),
        m_tCoarse1(p_tCoarse1),
        m_tCoarse2(p_tCoarse2),
        m_tCoarse3(p_tCoarse3),
        m_tFine0(p_tFine0),
        m_tFine1(p_tFine1),
        m_tFine2(p_tFine2) {}
    };

    // the data in the buffer must start with the P field,
    // no time correlation with a mission timeline is performed
    UTIL::AbsTime convert(const void* p_buffer) throw(UTIL::Exception);

    // the data in the buffer start with the P field,
    // no time correlation with a mission timeline is performed
    Time convert(const UTIL::AbsTime& p_time, TimeCode p_pField)
      throw(UTIL::Exception);
  }
}

#endif
