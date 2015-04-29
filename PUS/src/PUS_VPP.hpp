//*****************************************************************************
// (C) 2015, Stefan Korner, Austria                                           *
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
// PUS Services - Variable Packet Module                                      *
//*****************************************************************************
#ifndef PUS_VPP_hpp
#define PUS_VPP_hpp

#include "PUS_PACKET.hpp"
#include "UTIL_VPP.hpp"

namespace PUS
{
  namespace VPP
  {
    //-------------------------------------------------------------------------
    class TMpacket: public PUS::PACKET::TMpacket
    //-------------------------------------------------------------------------
    {
    public:
      // constructors and destructur
      TMpacket();
      TMpacket(size_t p_bufferSize);
      TMpacket(void* p_buffer, size_t p_bufferSize);
      TMpacket(const void* p_buffer, size_t p_bufferSize, bool p_copyBuffer);
      TMpacket(const TMpacket& p_du);
      const TMpacket& operator=(const TMpacket& p_du);
      virtual ~TMpacket();

      virtual void setParameterRootType(const UTIL::VPP::NodeDef* p_rootType);

    protected:
      UTIL::VPP::Node* m_parameters;
    };

    //-------------------------------------------------------------------------
    class TCpacket: public PUS::PACKET::TCpacket
    //-------------------------------------------------------------------------
    {
    public:
      // constructors and destructur
      TCpacket();
      TCpacket(size_t p_bufferSize);
      TCpacket(void* p_buffer, size_t p_bufferSize);
      TCpacket(const void* p_buffer, size_t p_bufferSize, bool p_copyBuffer);
      TCpacket(const TCpacket& p_du);
      const TCpacket& operator=(const TCpacket& p_du);
      virtual ~TCpacket();

      virtual void setParameterRootType(const UTIL::VPP::NodeDef* p_rootType);

    protected:
      UTIL::VPP::Node* m_parameters;
    };
  }
}

#endif
