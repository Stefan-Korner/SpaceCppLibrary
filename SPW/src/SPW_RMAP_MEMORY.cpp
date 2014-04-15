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
// SpaceWire - RMAP Memory                                                    *
//*****************************************************************************
#include "SPW_RMAP_MEMORY.hpp"

//-----------------------------------------------------------------------------
SPW::RMAP::Memory::Memory(size_t p_memorySize): m_buffer(p_memorySize)
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
SPW::RMAP::Memory::~Memory()
//-----------------------------------------------------------------------------
{}

//-----------------------------------------------------------------------------
size_t SPW::RMAP::Memory::getMemorySize() const
//-----------------------------------------------------------------------------
{
  return m_buffer.bufferSize();
}

//-----------------------------------------------------------------------------
UTIL::DU& SPW::RMAP::Memory::buffer()
//-----------------------------------------------------------------------------
{
  return m_buffer;
}

//-----------------------------------------------------------------------------
SPW::PACKET::RMAPreply* SPW::RMAP::Memory::execute(
  const SPW::PACKET::RMAPcommand& p_command) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  // check the CRC of the header
  if(!p_command.checkHeaderCRC())
  {
    throw UTIL::Exception("Invalid command header CRC");
  }
  // check if the command contains the correct instruction
  uint8_t instruction = p_command.getInstruction();
  if(!SPW::PACKET::RMAPpacket::isCommand(instruction))
  {
    throw UTIL::Exception("Passed SPW packet is not a command");
  }
  // check the CRC of the data
  if(SPW::PACKET::RMAPpacket::verifyDataBeforeWrite(instruction))
  {
    if(!p_command.checkDataCRC())
    {
      throw UTIL::Exception("Invalid command data CRC");
    }
  }
  // access to memory is performed without considering
  // the extended memory address
  SPW::PACKET::RMAPreply* reply = NULL;
  size_t memoryPos = p_command.getMemoryAddr();
  // check the command code
  SPW::PACKET::RMAPpacket::CommandCode commandCode =
    SPW::PACKET::RMAPpacket::commandCode(instruction);
  switch(commandCode)
  {
  case SPW::PACKET::RMAPpacket::CMD_INVALID:
    throw UTIL::Exception("Invalid command code");
  case SPW::PACKET::RMAPpacket::CMD_READ_SINGLE_ADDR:
  case SPW::PACKET::RMAPpacket::CMD_READ_INCR_ADDR:
    {
      // incrementation is ignored, reply only single byte (with CRC)
      uint8_t readByte = m_buffer[memoryPos];
      reply = new SPW::PACKET::RMAPreply(p_command, 2);
      reply->setStatus(SPW::PACKET::RMAPpacket::CMD_OK);
      reply->setDataByte(0, readByte);
      reply->setDataCRC();
    }
    break;
  case SPW::PACKET::RMAPpacket::CMD_READ_MOD_WRITE_INCR_ADDR:
    break;
  case SPW::PACKET::RMAPpacket::CMD_WRITE_SINGLE_ADDR:
  case SPW::PACKET::RMAPpacket::CMD_WRITE_INCR_ADDR:
  case SPW::PACKET::RMAPpacket::CMD_WRITE_SINGLE_ADDR_VERIF:
  case SPW::PACKET::RMAPpacket::CMD_WRITE_INCR_ADDR_VERIF:
    {
      // incrementation is ignored, skip CRC, don't reply 
      size_t dataSize = p_command.getDataSize();
      if(dataSize < 2)
      {
        throw UTIL::Exception("Missing data for write operation");
      }
      m_buffer.setBytes(memoryPos, dataSize - 1, p_command.getData());
    }
    break;
  case SPW::PACKET::RMAPpacket::CMD_WRITE_SINGLE_ADDR_RPLY:
  case SPW::PACKET::RMAPpacket::CMD_WRITE_INCR_ADDR_RPLY:
  case SPW::PACKET::RMAPpacket::CMD_WRITE_SINGLE_ADDR_VERIF_RPLY:
  case SPW::PACKET::RMAPpacket::CMD_WRITE_INCR_ADDR_VERIF_RPLY:
    {
      // incrementation is ignored, skip CRC, reply status
      size_t dataSize = p_command.getDataSize();
      if(dataSize < 2)
      {
        throw UTIL::Exception("Missing data for write operation");
      }
      m_buffer.setBytes(memoryPos, dataSize - 1, p_command.getData());
      reply = new SPW::PACKET::RMAPreply(p_command, 0);    
      reply->setStatus(SPW::PACKET::RMAPpacket::CMD_OK);
    }
    break;
  }
  if(reply != NULL)
  {
    reply->setHeaderCRC();
  }
  return reply;
}
