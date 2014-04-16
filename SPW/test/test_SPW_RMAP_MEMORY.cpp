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
// SpaceWire - RMAP Memory - Unit Tests                                       *
//*****************************************************************************
#include "SPW_PACKET.hpp"
#include "SPW_RMAP_MEMORY.hpp"

#include <iostream>

using namespace std;

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  try
  {
    // memory with 1000 bytes
    SPW::RMAP::Memory memory(1000);
    // command for setting one byte
    uint8_t instruction = SPW::PACKET::RMAPpacket::instruction(
      true,
      SPW::PACKET::RMAPpacket::BYTES_0,
      SPW::PACKET::RMAPpacket::CMD_WRITE_SINGLE_ADDR);
    SPW::PACKET::RMAPcommand command(0, instruction, 2);
    command.setDataByte(0, 0x5A);
/*
    command.setHeaderCRC();
    command.setDataCRC();
*/
    command.dump("command");
/*
    // execute the command
    SPW::PACKET::RMAPreply* reply = memory.execute(command);
    memory.buffer().dump("memory");
    // dump the reply if there is one
    if(reply != NULL)
    {
      reply->dump("reply");
    }
*/
  }
  catch(UTIL::Exception ex)
  {
    cout << "Exception: " << ex.what() << endl;
  }
  return 0;
}
