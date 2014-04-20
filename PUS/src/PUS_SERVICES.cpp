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

//////////////
// Service1 //
//////////////

// global variables
PUS::SERVICES::Service1* PUS::SERVICES::Service1::s_instance = NULL;

//-----------------------------------------------------------------------------
PUS::SERVICES::Service1::Service1():
  m_timePos(10), m_timeCode(CCSDS::CUC::L2_TIME_4_3), m_tcHeaderPos(16)
//-----------------------------------------------------------------------------
{
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
                                 uint8_t p_subType)
//-----------------------------------------------------------------------------
{
  return NULL;
}
