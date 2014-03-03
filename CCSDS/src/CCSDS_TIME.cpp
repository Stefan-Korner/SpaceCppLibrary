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
#include "CCSDS_TIME.hpp"

//-----------------------------------------------------------------------------
UTIL::AbsTime CCSDS::CUC::convert(const void* p_buffer) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  UTIL::AbsTime retVal;
  double fine = 0;
  const uint8_t* cucTime = (const uint8_t*) p_buffer;
  switch(cucTime[0])
  {
  case L1_TIME_4_3:
  case L2_TIME_4_3:
    fine += cucTime[7] / 0.16777216; 
  case L1_TIME_4_2:
  case L2_TIME_4_2:
    fine += cucTime[6] / 0.65535; 
  case L1_TIME_4_1:
  case L2_TIME_4_1:
    fine += cucTime[5] / 0.256; 
  case L1_TIME_4_0:
  case L2_TIME_4_0:
    break;
  default:
    throw UTIL::Exception("invalid time code for CUC time");
  }
  retVal.m_sec = (cucTime[1] * 0x01000000) +
                 (cucTime[2] * 0x00010000) +
                 (cucTime[3] * 0x00000100) +
                 (cucTime[4] * 0x00000001);
  retVal.m_micro = (uint32_t) (fine * 1000000);
  return retVal;
}

//-----------------------------------------------------------------------------
CCSDS::CUC::Time CCSDS::CUC::convert(const UTIL::AbsTime& p_time,
                                     TimeCode p_pField) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  CCSDS::CUC::Time retVal;
  double fine = p_time.m_micro;
  switch(p_pField)
  {
  case L1_TIME_4_3:
  case L2_TIME_4_3:
    fine *= (256.0 / 1000000); // convert from micro seconds to sec and shift
    retVal.m_tFine2 = (uint8_t) fine;
    fine -= retVal.m_tFine2;
  case L1_TIME_4_2:
  case L2_TIME_4_2:
    fine *= 256.0;
    retVal.m_tFine1 = (uint8_t) fine;
    fine -= retVal.m_tFine1;
  case L1_TIME_4_1:
  case L2_TIME_4_1:
    fine *= 256.0;
    retVal.m_tFine0 = (uint8_t) fine;
  case L1_TIME_4_0:
  case L2_TIME_4_0:
    break;
  default:
    throw UTIL::Exception("invalid time code for CUC time");
  }
  uint32_t coarse = p_time.m_sec;
  retVal.m_tCoarse3 = (uint8_t) (coarse & 0xFF);
  coarse >>= 8;
  retVal.m_tCoarse2 = (uint8_t) (coarse & 0xFF);
  coarse >>= 8;
  retVal.m_tCoarse1 = (uint8_t) (coarse & 0xFF);
  coarse >>= 8;
  retVal.m_tCoarse0 = (uint8_t) (coarse & 0xFF);
  retVal.m_pField = p_pField;
  return retVal;
}
