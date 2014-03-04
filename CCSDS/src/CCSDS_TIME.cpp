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

static double CUCFINE3_TO_MICRO =  1000000.0 / 16777216.0;
static double CUCFINE2_TO_MICRO =  1000000.0 /    65536.0;
static double CUCFINE1_TO_MICRO =  1000000.0 /      256.0;
static double MICRO_TO_CUCFINE3 = 16777216.0 /  1000000.0;
static double MICRO_TO_CUCFINE2 =    65536.0 /  1000000.0;
static double MICRO_TO_CUCFINE1 =      256.0 /  1000000.0;

//-----------------------------------------------------------------------------
UTIL::AbsTime CCSDS::CUC::convert(const void* p_buffer) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  UTIL::AbsTime retVal;
  const uint8_t* cucTime = (const uint8_t*) p_buffer;
  double timeMicro = 0;
  if((cucTime[0] == L1_TIME_4_3) || (cucTime[0] == L2_TIME_4_3))
  {
    uint32_t cucTimeFine = (cucTime[5] * 0x010000) +
                           (cucTime[6] * 0x000100) +
                           (cucTime[7] * 0x000001);
    timeMicro = cucTimeFine * CUCFINE3_TO_MICRO;
  }
  else if((cucTime[0] == L1_TIME_4_2) || (cucTime[0] == L2_TIME_4_2))
  {
    uint32_t cucTimeFine = (cucTime[5] * 0x0100) +
                           (cucTime[6] * 0x0001);
    timeMicro = cucTimeFine * CUCFINE2_TO_MICRO;
  }
  else if((cucTime[0] == L1_TIME_4_1) || (cucTime[0] == L2_TIME_4_1))
  {
    uint32_t cucTimeFine = cucTime[5];
    timeMicro = cucTimeFine * CUCFINE1_TO_MICRO;
  }
  else if((cucTime[0] != L1_TIME_4_0) && (cucTime[0] != L2_TIME_4_0))
  {
    throw UTIL::Exception("invalid time code for CUC time");
  }
  retVal.m_sec = (cucTime[1] * 0x01000000) +
                 (cucTime[2] * 0x00010000) +
                 (cucTime[3] * 0x00000100) +
                 (cucTime[4] * 0x00000001);
  retVal.m_micro = (uint32_t) timeMicro;
  return retVal;
}

//-----------------------------------------------------------------------------
CCSDS::CUC::Time CCSDS::CUC::convert(const UTIL::AbsTime& p_time,
                                     TimeCode p_pField) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  CCSDS::CUC::Time retVal;
  if((p_pField == L1_TIME_4_3) || (p_pField == L2_TIME_4_3))
  {
    uint32_t cucTimeFine = (uint32_t) (p_time.m_micro * MICRO_TO_CUCFINE3);
    retVal.m_tFine2 = (uint8_t) (cucTimeFine & 0xFF);
    cucTimeFine >>= 8;
    retVal.m_tFine1 = (uint8_t) (cucTimeFine & 0xFF);
    cucTimeFine >>= 8;
    retVal.m_tFine0 = (uint8_t) cucTimeFine;
  }
  else if((p_pField == L1_TIME_4_2) || (p_pField == L2_TIME_4_2))
  {
    uint32_t cucTimeFine = (uint32_t) (p_time.m_micro * MICRO_TO_CUCFINE2);
    retVal.m_tFine1 = (uint8_t) (cucTimeFine & 0xFF);
    cucTimeFine >>= 8;
    retVal.m_tFine0 = (uint8_t) cucTimeFine;
  }
  else if((p_pField == L1_TIME_4_1) || (p_pField == L2_TIME_4_1))
  {
    uint32_t cucTimeFine = (uint32_t) (p_time.m_micro * MICRO_TO_CUCFINE1);
    retVal.m_tFine0 = (uint8_t) cucTimeFine;
  }
  else if((p_pField != L1_TIME_4_0) && (p_pField != L2_TIME_4_0))
  {
    throw UTIL::Exception("invalid time code for CUC time");
  }
  uint32_t cucTimeCoarse = p_time.m_sec;
  retVal.m_tCoarse3 = (uint8_t) (cucTimeCoarse & 0xFF);
  cucTimeCoarse >>= 8;
  retVal.m_tCoarse2 = (uint8_t) (cucTimeCoarse & 0xFF);
  cucTimeCoarse >>= 8;
  retVal.m_tCoarse1 = (uint8_t) (cucTimeCoarse & 0xFF);
  cucTimeCoarse >>= 8;
  retVal.m_tCoarse0 = (uint8_t) cucTimeCoarse;
  retVal.m_pField = p_pField;
  return retVal;
}
