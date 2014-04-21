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
// PUS Services - Unit Tests                                                  *
//*****************************************************************************
#include "PUS_SERVICES.hpp"

#include <iostream>
#include <memory>

using namespace std;

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  try
  {
    PUS::SERVICES::Service1 service1;
    // telecommand: 6 Byte CCSDS header, 3 Byte PUS header, 2 Byte CRC
    PUS::PACKET::TCpacket tcPacket(11);
    tcPacket.applicationProcessId(1234);
    tcPacket.sequenceControlCount(123);
    tcPacket.serviceType(8);
    tcPacket.serviceSubType(1);
    tcPacket.setChecksum();
    tcPacket.dump("tcPacket");
    // create PUS service 1.1 responses
    auto_ptr<PUS::PACKET::TMpacket>
      ack_1_1(PUS::SERVICES::Service1::instance()->respond(tcPacket, 1));
    if(ack_1_1.get() == NULL)
    {
      cout << "Error: empty ack(1.1)" << endl;
      return -1;
    }
    ack_1_1->dump("ack_1_1");
    cout << "*** PASSED ***" << endl;
  }
  catch(const UTIL::Exception& ex)
  {
    cout << "Exception: " << ex.what() << endl;
    return -1;
  }
  return 0;
}
