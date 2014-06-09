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
// CCSDS - Packet - Unit Tests                                                *
//*****************************************************************************
#include "CCSDS_PACKET.hpp"

#include <iostream>
#include <string.h>

using namespace std;

static const UTIL::DU::VarByteAccessor VBYTE_ACC1 = {10};
static const UTIL::DU::VarStringAccessor VSTRING_ACC1 = {10};

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  try
  {
    const char* txt1 = "0123456789**********";
    CCSDS::PACKET::Packet packet(txt1, strlen(txt1), true);
    packet.dump("packet", true);
    string txt2 = "ABCD";
    packet.set(VSTRING_ACC1, txt2);
    packet.dump("packet", true);
    txt2 = packet.get(VSTRING_ACC1);
    cout << "txt2 = " << txt2 << endl;
    cout << "txt2.size() = " << txt2.size() << endl;
    txt2 = "------";
    packet.set(VSTRING_ACC1, txt2);
    packet.dump("packet", true);
    txt2 = packet.get(VSTRING_ACC1);
    cout << "txt2 = " << txt2 << endl;
    cout << "txt2.size() = " << txt2.size() << endl;
    UTIL::DU::VarByteHelper hlpr1 = packet.get(VBYTE_ACC1);
    UTIL::DU du(hlpr1.bytes, hlpr1.byteLength, false);
    du.dump("du", true);
    packet.set(VBYTE_ACC1, 4, "0000");
    packet.dump("packet", true);
  }
  catch(const UTIL::Exception& ex)
  {
    cout << "Exception: " << ex.what() << endl;
  }
  return 0;
}
