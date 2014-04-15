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
#ifndef SPW_RMAP_MEMORY_hpp
#define SPW_RMAP_MEMORY_hpp

#include "SPW_PACKET.hpp"
#include "UTIL_DU.hpp"

namespace SPW
{
  namespace RMAP
  {
    class Memory
    {
    public:
      // constructors and destructur
      Memory(size_t p_memorySize);
      virtual ~Memory();

      // access methods
      virtual size_t getMemorySize() const;
      virtual UTIL::DU& buffer();
      virtual void setMemoryPointer(size_t p_pos) throw(UTIL::Exception);
      virtual size_t getMemoryPointer() const;

      // performs RMAP memory access - reply shall be deleted by the caller
      virtual SPW::PACKET::RMAPreply* execute(
        const SPW::PACKET::RMAPcommand& p_command);

    private:
      // object has reference semantic
      Memory(const Memory& p_memory);
      const Memory& operator=(const Memory& p_du);

      UTIL::DU m_buffer;
      size_t m_memoryPointer;
    };
  }
}

#endif
