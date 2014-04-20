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
// PUS Services - Services Module                                             *
//*****************************************************************************
#include "PUS_SERVICES.hpp"

#include <memory>

using namespace std;

//////////////
// Service1 //
//////////////

// global variables
PUS::SERVICES::Service1* PUS::SERVICES::Service1::s_instance = NULL;

//-----------------------------------------------------------------------------
PUS::SERVICES::Service1::Service1():
  m_tcHeaderPos(PUS::SERVICES::S1::DEFAULT_TC_HEADER_BYTE_POS)
//-----------------------------------------------------------------------------
{
  m_tmPacketSizes[1] = PUS::SERVICES::S1::DEFAULT_TM_1_1_BYTE_SIZE;
  m_tmPacketSizes[2] = PUS::SERVICES::S1::DEFAULT_TM_1_2_BYTE_SIZE;
  m_tmPacketSizes[3] = PUS::SERVICES::S1::DEFAULT_TM_1_3_BYTE_SIZE;
  m_tmPacketSizes[4] = PUS::SERVICES::S1::DEFAULT_TM_1_4_BYTE_SIZE;
  m_tmPacketSizes[5] = PUS::SERVICES::S1::DEFAULT_TM_1_5_BYTE_SIZE;
  m_tmPacketSizes[6] = PUS::SERVICES::S1::DEFAULT_TM_1_6_BYTE_SIZE;
  m_tmPacketSizes[7] = PUS::SERVICES::S1::DEFAULT_TM_1_7_BYTE_SIZE;
  m_tmPacketSizes[8] = PUS::SERVICES::S1::DEFAULT_TM_1_8_BYTE_SIZE;
  s_instance = this;
}

//-----------------------------------------------------------------------------
PUS::SERVICES::Service1::~Service1()
//-----------------------------------------------------------------------------
{
  s_instance = NULL;
}

//-----------------------------------------------------------------------------
PUS::SERVICES::Service1* PUS::SERVICES::Service1::instance()
//-----------------------------------------------------------------------------
{
  return s_instance;
}

//-----------------------------------------------------------------------------
PUS::PACKET::TMpacket*
PUS::SERVICES::Service1::respond(const PUS::PACKET::TCpacket& p_tcPkt,
                                 uint8_t p_subType) throw(UTIL::Exception)
//-----------------------------------------------------------------------------
{
  if(p_tcPkt.bufferSize() < 6)
  {
    throw UTIL::Exception("TC packet size is too small");
  }
  if((p_subType < 1)| (p_subType > 8))
  {
    throw UTIL::Exception("Service sub type has invalid value");
  }
  uint32_t tcPacketID = p_tcPkt.getUnsigned(0, 2);
  uint32_t tcPacketSCC = p_tcPkt.sequenceControlCount();
  size_t tmPacketSize = m_tmPacketSizes[p_subType];
  auto_ptr<PUS::PACKET::TMpacket>
    tmPacket(new PUS::PACKET::TMpacket(tmPacketSize));
  tmPacket->serviceType(1);
  tmPacket->serviceSubType(p_subType);
  tmPacket->setUnsigned(m_tcHeaderPos, 2, tcPacketID);
  tmPacket->setUnsigned(m_tcHeaderPos + 2, 2, tcPacketSCC);
  // move the ownership to the caller
  return tmPacket.release();
}

//-----------------------------------------------------------------------------
void PUS::SERVICES::Service1::setTcHeaderPos(size_t p_tcHeaderPos)
//-----------------------------------------------------------------------------
{
  m_tcHeaderPos = p_tcHeaderPos;
}

//-----------------------------------------------------------------------------
void PUS::SERVICES::Service1::setTM_1_1_ByteSize(size_t p_byteSize)
//-----------------------------------------------------------------------------
{
  m_tmPacketSizes[1] = p_byteSize;
}

//-----------------------------------------------------------------------------
void PUS::SERVICES::Service1::setTM_1_2_ByteSize(size_t p_byteSize)
//-----------------------------------------------------------------------------
{
  m_tmPacketSizes[2] = p_byteSize;
}

//-----------------------------------------------------------------------------
void PUS::SERVICES::Service1::setTM_1_3_ByteSize(size_t p_byteSize)
//-----------------------------------------------------------------------------
{
  m_tmPacketSizes[3] = p_byteSize;
}

//-----------------------------------------------------------------------------
void PUS::SERVICES::Service1::setTM_1_4_ByteSize(size_t p_byteSize)
//-----------------------------------------------------------------------------
{
  m_tmPacketSizes[4] = p_byteSize;
}

//-----------------------------------------------------------------------------
void PUS::SERVICES::Service1::setTM_1_5_ByteSize(size_t p_byteSize)
//-----------------------------------------------------------------------------
{
  m_tmPacketSizes[5] = p_byteSize;
}

//-----------------------------------------------------------------------------
void PUS::SERVICES::Service1::setTM_1_6_ByteSize(size_t p_byteSize)
//-----------------------------------------------------------------------------
{
  m_tmPacketSizes[6] = p_byteSize;
}

//-----------------------------------------------------------------------------
void PUS::SERVICES::Service1::setTM_1_7_ByteSize(size_t p_byteSize)
//-----------------------------------------------------------------------------
{
  m_tmPacketSizes[7] = p_byteSize;
}

//-----------------------------------------------------------------------------
void PUS::SERVICES::Service1::setTM_1_8_ByteSize(size_t p_byteSize)
//-----------------------------------------------------------------------------
{
  m_tmPacketSizes[8] = p_byteSize;
}

