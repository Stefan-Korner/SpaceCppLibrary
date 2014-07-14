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

static const UTIL::DU::VarByteAccessor VBYTE_ACC1 = {16};
static const UTIL::DU::VarStringAccessor VSTRING_ACC1 = {16};

//-----------------------------------------------------------------------------
void testPacket(CCSDS::PACKET::Packet& p_packet, const char* p_packetName)
//-----------------------------------------------------------------------------
{
  try
  {
    p_packet.dump(p_packetName, true);
    string txt = "ABCD";
    p_packet.set(VSTRING_ACC1, txt);
    p_packet.dump(p_packetName, true);
    txt = p_packet.get(VSTRING_ACC1);
    cout << "txt = " << txt << endl;
    cout << "txt.size() = " << txt.size() << endl;
    txt = "------";
    p_packet.set(VSTRING_ACC1, txt);
    p_packet.dump(p_packetName, true);
    txt = p_packet.get(VSTRING_ACC1);
    cout << "txt = " << txt << endl;
    cout << "txt.size() = " << txt.size() << endl;
    UTIL::DU::VarByteHelper hlpr1 = p_packet.get(VBYTE_ACC1);
    UTIL::DU du(hlpr1.bytes, hlpr1.byteLength, false);
    du.dump("du", true);
    p_packet.set(VBYTE_ACC1, 8, "01234567");
    p_packet.dump(p_packetName, true);
  }
  catch(const UTIL::Exception& ex)
  {
    cout << "Exception: " << ex.what() << endl;
  }
}

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  const char* tmInit = "____LL________________";
  CCSDS::PACKET::TMpacket tmPacket(tmInit, strlen(tmInit), true);
  testPacket(tmPacket, "tmPacket");
  cout << endl;
  const char* tcInit = "____LL________________";
  CCSDS::PACKET::TCpacket tcPacket(tcInit, strlen(tcInit), true);
  testPacket(tcPacket, "tcPacket");
  return 0;
}
