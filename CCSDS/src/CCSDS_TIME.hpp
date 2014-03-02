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

namespace CCSDS
{
  namespace CUC
  {
    struct Time
    {
      uint8_t m_pField;
      uint8_t m_tCoarse0;
      uint8_t m_tCoarse1;
      uint8_t m_tCoarse2;
      uint8_t m_tCoarse3;
      uint8_t m_tFine0;
      uint8_t m_tFine1;
      uint8_t m_tFine2;
    };

    // the data in the buffer must start with the P field,
    // no time correlation with a mission timeline is performed
    UTIL::AbsTime convert(const void* p_buffer);

    // the data in the buffer start with the P field,
    // no time correlation with a mission timeline is performed
    Time convert(const UTIL::AbsTime& p_time, uint8_t p_pField);
  }
}

#endif
