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
// Utilities - Cyclic Redundancy Check (CRC)                                  *
//*****************************************************************************
#include "UTIL_CRC.hpp"

//-----------------------------------------------------------------------------
// calculates the CRC from the byte array
uint16_t UTIL::CRC::calculate(const void* p_buffer, size_t p_bufferSize)
//-----------------------------------------------------------------------------
{
  // typed buffer
  const uint8_t* byteArray = (const uint8_t*) p_buffer;
  // 32 bit shift register for CRC generation
  // D0  - D15  :CRC shift register
  // D16        : MSB after shift
  // D17 - D31  : not used
  // shift register preset with all ones
  uint32_t shiftReg = 0x0000FFFF;
  // generator polynom D0-D15: X^16 + X^12 + X^5 + X^0
  uint32_t polynom = 0x00001021;
  for(size_t i = 0; i < p_bufferSize; i++)
  {
    const uint8_t& nextByte = byteArray[i];
    // loop over 8 bit
    for(int8_t bitNo = 7; bitNo >= 0; bitNo--)
    {
      // evaluate bit in data string
      uint8_t mask = (1 << bitNo);
      // set D16 in help var. EXOR with shift
      uint32_t h = ((nextByte & mask) > 0) ? 0x00010000 : 0;
      // clock the shift register
      shiftReg <<= 1;
      // evaluate the bit that falls out of the shift register,
      // simultaneously add the input data bit (rightmost + in diagram),
      // this covers the X^16 term
      if((h ^ (shiftReg & 0x00010000)) > 0)
      {
        // check D16 in shift and then here, the level behind GATE A is one
        // add (i.e. XOR) the X^0 + X^5 + X^12 polynome to the shift register
        shiftReg ^= polynom;
      }
      // the else branch is empty, as the level behind gate A is 0
      // and XORing with zero has no effect
    }
  }
  return ((uint16_t) (shiftReg & 0x0000FFFF));
}
