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
  SPW::PACKET::RMAPreply* reply = NULL;
  size_t memoryPos = p_command.getMemoryAddr();
  size_t dataLength = p_command.getDataLength();
  if(dataLength == 0)
  {
    throw UTIL::Exception("Empty data for command not supported");
  }
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
      // incrementation is ignored
      const uint8_t* readBytes = m_buffer.getBytes(memoryPos, dataLength);
      // add CRC to data
      reply = new SPW::PACKET::RMAPreply(p_command);
      reply->setStatus(SPW::PACKET::RMAPpacket::CMD_OK);
      reply->setData(dataLength, readBytes);
      reply->setDataCRC();
    }
    break;
  case SPW::PACKET::RMAPpacket::CMD_READ_MOD_WRITE_INCR_ADDR:
    {
      // incrementation is ignored
      if(dataLength == 2)
      {
        // read modify write byte
        uint32_t memoryData = m_buffer.getUnsigned(memoryPos, 1);
        uint32_t packetData = p_command.getDataByte(0);
        uint32_t packetMask = p_command.getDataByte(1);
        uint32_t writeData = (packetData & packetMask) | 
                            (memoryData & ~packetMask);
        m_buffer.setUnsigned(memoryPos, 1, writeData);
        reply = new SPW::PACKET::RMAPreply(p_command);
        reply->setDataByte(0, (uint8_t) memoryData);
      }
      else if(dataLength == 4)
      {
        // read modify write word
        uint32_t memoryData = m_buffer.getUnsigned(memoryPos, 2);
        uint32_t packetData = p_command.getDataWord(0);
        uint32_t packetMask = p_command.getDataWord(2);
        uint32_t writeData = (packetData & packetMask) | 
                            (memoryData & ~packetMask);
        m_buffer.setUnsigned(memoryPos, 2, writeData);
        reply = new SPW::PACKET::RMAPreply(p_command);
        reply->setDataWord(0, (uint16_t) memoryData);
      }
      else if(dataLength == 6)
      {
        // read modify write 3 bytes
        uint32_t memoryData = m_buffer.getUnsigned(memoryPos, 3);
        uint32_t packetData = p_command.getData3Bytes(0);
        uint32_t packetMask = p_command.getData3Bytes(3);
        uint32_t writeData = (packetData & packetMask) | 
                            (memoryData & ~packetMask);
        m_buffer.setUnsigned(memoryPos, 3, writeData);
        reply = new SPW::PACKET::RMAPreply(p_command);
        reply->setData3Bytes(0, memoryData);
      }
      else if(dataLength == 8)
      {
        // read modify write long word
        uint32_t memoryData = m_buffer.getUnsigned(memoryPos, 4);
        uint32_t packetData = p_command.getDataLongWord(0);
        uint32_t packetMask = p_command.getDataLongWord(4);
        uint32_t writeData = (packetData & packetMask) | 
                            (memoryData & ~packetMask);
        m_buffer.setUnsigned(memoryPos, 4, writeData);
        reply = new SPW::PACKET::RMAPreply(p_command);
        reply->setDataLongWord(0, memoryData);
      }
      else
      {
        throw UTIL::Exception("Invalid data length for read-modify-write");
      }
      reply->setStatus(SPW::PACKET::RMAPpacket::CMD_OK);
      reply->setDataCRC();
    }
    break;
  case SPW::PACKET::RMAPpacket::CMD_WRITE_SINGLE_ADDR:
  case SPW::PACKET::RMAPpacket::CMD_WRITE_INCR_ADDR:
  case SPW::PACKET::RMAPpacket::CMD_WRITE_SINGLE_ADDR_VERIF:
  case SPW::PACKET::RMAPpacket::CMD_WRITE_INCR_ADDR_VERIF:
    {
      // incrementation is ignored, don't reply
      m_buffer.setBytes(memoryPos, dataLength, p_command.getData());
    }
    break;
  case SPW::PACKET::RMAPpacket::CMD_WRITE_SINGLE_ADDR_RPLY:
  case SPW::PACKET::RMAPpacket::CMD_WRITE_INCR_ADDR_RPLY:
  case SPW::PACKET::RMAPpacket::CMD_WRITE_SINGLE_ADDR_VERIF_RPLY:
  case SPW::PACKET::RMAPpacket::CMD_WRITE_INCR_ADDR_VERIF_RPLY:
    {
      // incrementation is ignored, reply status
      m_buffer.setBytes(memoryPos, dataLength, p_command.getData());
      reply = new SPW::PACKET::RMAPreply(p_command);    
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
