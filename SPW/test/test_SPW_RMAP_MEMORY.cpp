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
#include <memory>

using namespace std;

static const size_t MEMORY_BUFFER_SIZE = 256;
static const uint8_t TESTBYTE1 = 0x5A;
static const uint32_t TESTLONGWORD1 = 0x1234CDEF;
static const uint32_t TESTLONGMASK1 = 0x00FFFFFF;
static const uint32_t CHECKLONGWORD1 = 0x5A000000;

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  try
  {
    // memory with MEMORY_BUFFER_SIZE bytes
    SPW::RMAP::Memory memory(MEMORY_BUFFER_SIZE);
    UTIL::DU& memoryBuffer = memory.buffer();
    memoryBuffer.dump("empty memory");
    // check the memory
    for(size_t i = 0; i < MEMORY_BUFFER_SIZE; i++)
    {
      if(memoryBuffer[i] != 0)
      {
        cout << "Error: buffer not empty" << endl;
        return -1;
      }
    }
    // *** command for setting one byte ***
    uint8_t instruction = SPW::PACKET::RMAPpacket::instruction(
      SPW::PACKET::RMAPpacket::CMD_WRITE_SINGLE_ADDR);
    SPW::PACKET::RMAPcommand writeCmd(0, instruction, 1);
    writeCmd.setDataByte(0, TESTBYTE1);
    writeCmd.setHeaderCRC();
    writeCmd.setDataCRC();
    writeCmd.dump("writeCmd");
    // execute the command
    auto_ptr<SPW::PACKET::RMAPreply> writeReply(memory.execute(writeCmd));
    memoryBuffer.dump("memory");
    // check the memory
    if(memoryBuffer[0] != TESTBYTE1)
    {
      cout << "Error: invalid byte in buffer" << endl;
      return -1;
    }
    // check if there is an empty reply
    if(writeReply.get() != NULL)
    {
      cout << "Error: non empty reply" << endl;
      return -1;
    }
    // *** command for reading one byte ***
    instruction = SPW::PACKET::RMAPpacket::instruction(
      SPW::PACKET::RMAPpacket::CMD_READ_SINGLE_ADDR);
    SPW::PACKET::RMAPcommand readCmd(0, instruction, 1);
    readCmd.setHeaderCRC();
    readCmd.dump("readCmd");
    // execute the command
    auto_ptr<SPW::PACKET::RMAPreply> readReply(memory.execute(readCmd));
    memoryBuffer.dump("memory");
    // check if there is an empty reply
    if(readReply.get() == NULL)
    {
      cout << "Error: empty reply" << endl;
      return -1;
    }
    readReply->dump("readReply");
    // check if the reply contains the proper data
    uint8_t readByte = readReply->getDataByte(0);
    if(readByte != TESTBYTE1)
    {
      cout << "Error: invalid data in reply" << endl;
      return -1;
    }
    // *** command for read-modify-write a long word ***
    instruction = SPW::PACKET::RMAPpacket::instruction(
      SPW::PACKET::RMAPpacket::CMD_READ_MOD_WRITE_INCR_ADDR);
    SPW::PACKET::RMAPcommand readModWriteCmd(0, instruction, 8);
    readModWriteCmd.setDataLongWord(0, TESTLONGWORD1);
    readModWriteCmd.setDataLongWord(4, TESTLONGMASK1);
    readModWriteCmd.setHeaderCRC();
    readModWriteCmd.setDataCRC();
    readModWriteCmd.dump("readModWriteCmd");
    // execute the command
    auto_ptr<SPW::PACKET::RMAPreply> readModWriteReply(
      memory.execute(readModWriteCmd));
    memoryBuffer.dump("memory");
    // check if there is an empty reply
    if(readModWriteReply.get() == NULL)
    {
      cout << "Error: empty reply" << endl;
      return -1;
    }
    readModWriteReply->dump("readModWriteReply");
    // check if the reply contains the proper data
    uint32_t readLongWord = readModWriteReply->getDataLongWord(0);
    if(readLongWord != CHECKLONGWORD1)
    {
      cout << "Error: invalid data in reply" << endl;
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
