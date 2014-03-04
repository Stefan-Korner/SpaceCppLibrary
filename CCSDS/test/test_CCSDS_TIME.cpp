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
// CCSDS - Time - Unit Tests                                                  *
//*****************************************************************************
#include "CCSDS_TIME.hpp"

#include <iostream>
#include "CCSDS_TIME.hpp"
#include "UTIL_DU.hpp"

using namespace std;

//-----------------------------------------------------------------------------
CCSDS::CUC::Time printAsCUCtime(const UTIL::AbsTime& p_absTime,
                                CCSDS::CUC::TimeCode p_timeCode,
                                const char* p_prefix)
//-----------------------------------------------------------------------------
{
  CCSDS::CUC::Time cucTime;
  try
  {
    cucTime = CCSDS::CUC::convert(p_absTime, p_timeCode);
    UTIL::DU du(&cucTime, 8, false);
    du.dump(p_prefix);
  }
  catch(UTIL::Exception ex)
  {
    cout << "Exception: " << ex.what() << endl;
  }
  return cucTime;
}

//-----------------------------------------------------------------------------
void printAsAbsTime(const CCSDS::CUC::Time& p_cucTime,
                    const char* p_prefix)
//-----------------------------------------------------------------------------
{
  try
  {
    UTIL::AbsTime absTime = CCSDS::CUC::convert(&p_cucTime);
    cout << p_prefix << " = " << absTime.m_sec << "." << absTime.m_micro
         << endl;
  }
  catch(UTIL::Exception ex)
  {
    cout << "Exception: " << ex.what() << endl;
  }
}

//-----------------------------------------------------------------------------
void printTimes(const UTIL::AbsTime& p_absTime)
//-----------------------------------------------------------------------------
{
  cout << endl << p_absTime.m_sec << "." << p_absTime.m_micro << endl;
  CCSDS::CUC::Time cucTime0 =
    printAsCUCtime(p_absTime, CCSDS::CUC::L1_TIME_4_0, "du(4_0)");
  CCSDS::CUC::Time cucTime1 =
    printAsCUCtime(p_absTime, CCSDS::CUC::L1_TIME_4_1, "du(4_1)");
  CCSDS::CUC::Time cucTime2 =
    printAsCUCtime(p_absTime, CCSDS::CUC::L1_TIME_4_2, "du(4_2)");
  CCSDS::CUC::Time cucTime3 =
    printAsCUCtime(p_absTime, CCSDS::CUC::L1_TIME_4_3, "du(4_3)");
  printAsAbsTime(cucTime0, "du(4_0)");
  printAsAbsTime(cucTime1, "du(4_1)");
  printAsAbsTime(cucTime2, "du(4_2)");
  printAsAbsTime(cucTime3, "du(4_3)");
}

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  try
  {
    UTIL::AbsTime absTime;
    absTime.m_sec = 1;
    absTime.m_micro = 500000;
    printTimes(absTime);
    absTime.m_sec = 2;
    absTime.m_micro = 250000;
    printTimes(absTime);
    absTime.m_sec = 4;
    absTime.m_micro = 125000;
    printTimes(absTime);
    absTime.m_sec = 8;
    absTime.m_micro = 62500;
    printTimes(absTime);
    absTime.m_sec = 16;
    absTime.m_micro = 31250;
    printTimes(absTime);
    absTime.m_sec = 32;
    absTime.m_micro = 15625;
    printTimes(absTime);
    absTime.m_sec = 64;
    absTime.m_micro = 15625;
    printTimes(absTime);
    absTime.m_sec = 128;
    absTime.m_micro = 15625;
    printTimes(absTime);
    absTime.m_sec = 256;
    absTime.m_micro = 7813;
    printTimes(absTime);
    absTime.m_sec = 512;
    absTime.m_micro = 3907;
    printTimes(absTime);
    absTime.m_sec = 1024;
    absTime.m_micro = 1954;
    printTimes(absTime);
    absTime.m_sec = 2048;
    absTime.m_micro = 977;
    printTimes(absTime);
    absTime.m_sec = 4096;
    absTime.m_micro = 489;
    printTimes(absTime);
    absTime.m_sec = 8192;
    absTime.m_micro = 245;
    printTimes(absTime);
    absTime.m_sec = 16384;
    absTime.m_micro = 123;
    printTimes(absTime);
    absTime.m_sec = 32768;
    absTime.m_micro = 62;
    printTimes(absTime);
    absTime.m_sec = 65536;
    absTime.m_micro = 31;
    printTimes(absTime);
    absTime.m_sec = 131072;
    absTime.m_micro = 16;
    printTimes(absTime);
    absTime.m_sec = 262144;
    absTime.m_micro = 8;
    printTimes(absTime);
    absTime.m_sec = 1048576;
    absTime.m_micro = 4;
    printTimes(absTime);
    absTime.m_sec = 4194304;
    absTime.m_micro = 2;
    printTimes(absTime);
    absTime.m_sec = 16777216;
    absTime.m_micro = 1;
    printTimes(absTime);
  }
  catch(UTIL::Exception ex)
  {
    cout << "Exception: " << ex.what() << endl;
  }
  return 0;
}
