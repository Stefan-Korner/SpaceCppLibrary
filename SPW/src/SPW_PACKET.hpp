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
// SpaceWire - SpaceWire Packet Module                                        *
//*****************************************************************************
#ifndef CCSDS_DU_hpp
#define CCSDS_DU_hpp

#include "UTIL_DU.hpp"

namespace SPW
{
  namespace PACKET
  {
    //-------------------------------------------------------------------------
    class Packet: public UTIL::DU
    //-------------------------------------------------------------------------
    {
    public:
      // constructors and destructur
      Packet();
      Packet(size_t p_bufferSize);
      Packet(void* p_buffer, size_t p_bufferSize);
      Packet(const void* p_buffer, size_t p_bufferSize, bool p_copyBuffer);
      Packet(const Packet& p_du);
      const Packet& operator=(const Packet& p_du);
      virtual ~Packet();
    };
  }
}

#endif
