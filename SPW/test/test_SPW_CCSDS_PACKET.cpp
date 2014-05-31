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
// SpaceWire - CCSDS Packet - Unit Tests                                      *
//*****************************************************************************
#include "SPW_PACKET.hpp"

#include <iostream>
#include <memory>
#include <string.h>

using namespace std;

static const char* CCSDS_PACKET1 = "This is a simulated CCSDS packet.";
static const char* CCSDS_PACKET2 = "Simulated CCSDS packet 2.";

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  try
  {
    // *** SPW CCSDS packet 1 with ASCII string simulating the CCSDS packet ***
    size_t pktLen1 = strlen(CCSDS_PACKET1) + 1;
    SPW::PACKET::CCSDSpacket pkt1(0, pktLen1);
    pkt1.setCCSDSpacket(pktLen1, CCSDS_PACKET1);
    pkt1.dump("pkt1");
    // check if the CCSDS data are really in
    if(pkt1.getCCSDSpacketSize() != pktLen1)
    {
      cout << "Error: invalid CCSDS packet 1 size" << endl;
      return -1;
    }
    if(memcmp(pkt1.getCCSDSpacket(), CCSDS_PACKET1, pktLen1) != 0)
    {
      cout << "Error: invalid CCSDS packet 1" << endl;
      return -1;
    }
    // *** SPW CCSDS packet 2 with ASCII string simulating the CCSDS packet ***
    size_t pktLen2 = strlen(CCSDS_PACKET2) + 1;
    SPW::PACKET::CCSDSpacket pkt2(0, pktLen2);
    pkt2.setCCSDSpacket(pktLen2, CCSDS_PACKET2);
    pkt2.dump("pkt2");
    // check if the CCSDS data are really in
    if(pkt2.getCCSDSpacketSize() != pktLen2)
    {
      cout << "Error: invalid CCSDS packet 2 size" << endl;
      return -1;
    }
    if(memcmp(pkt2.getCCSDSpacket(), CCSDS_PACKET2, pktLen2) != 0)
    {
      cout << "Error: invalid CCSDS packet 2" << endl;
      return -1;
    }
    cout << "*** PASSED ***" << endl;
  }
  catch(const UTIL::Exception& ex)
  {
    cout << "Exception: " << ex.what() << endl;
    return -1;
  }
  return 0;
}
