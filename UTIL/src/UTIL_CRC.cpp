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

// The local look-up table used to calculate the updated CRC 8 byte
// from the intermediate CRC byte and the input byte.
static const uint8_t CRC8_TABLE[] =
{
  0x00, 0x91, 0xe3, 0x72, 0x07, 0x96, 0xe4, 0x75,
  0x0e, 0x9f, 0xed, 0x7c, 0x09, 0x98, 0xea, 0x7b,
  0x1c, 0x8d, 0xff, 0x6e, 0x1b, 0x8a, 0xf8, 0x69,
  0x12, 0x83, 0xf1, 0x60, 0x15, 0x84, 0xf6, 0x67,
  0x38, 0xa9, 0xdb, 0x4a, 0x3f, 0xae, 0xdc, 0x4d,
  0x36, 0xa7, 0xd5, 0x44, 0x31, 0xa0, 0xd2, 0x43,
  0x24, 0xb5, 0xc7, 0x56, 0x23, 0xb2, 0xc0, 0x51,
  0x2a, 0xbb, 0xc9, 0x58, 0x2d, 0xbc, 0xce, 0x5f,
  0x70, 0xe1, 0x93, 0x02, 0x77, 0xe6, 0x94, 0x05,
  0x7e, 0xef, 0x9d, 0x0c, 0x79, 0xe8, 0x9a, 0x0b,
  0x6c, 0xfd, 0x8f, 0x1e, 0x6b, 0xfa, 0x88, 0x19,
  0x62, 0xf3, 0x81, 0x10, 0x65, 0xf4, 0x86, 0x17,
  0x48, 0xd9, 0xab, 0x3a, 0x4f, 0xde, 0xac, 0x3d,
  0x46, 0xd7, 0xa5, 0x34, 0x41, 0xd0, 0xa2, 0x33,
  0x54, 0xc5, 0xb7, 0x26, 0x53, 0xc2, 0xb0, 0x21,
  0x5a, 0xcb, 0xb9, 0x28, 0x5d, 0xcc, 0xbe, 0x2f,
  0xe0, 0x71, 0x03, 0x92, 0xe7, 0x76, 0x04, 0x95,
  0xee, 0x7f, 0x0d, 0x9c, 0xe9, 0x78, 0x0a, 0x9b,
  0xfc, 0x6d, 0x1f, 0x8e, 0xfb, 0x6a, 0x18, 0x89,
  0xf2, 0x63, 0x11, 0x80, 0xf5, 0x64, 0x16, 0x87,
  0xd8, 0x49, 0x3b, 0xaa, 0xdf, 0x4e, 0x3c, 0xad,
  0xd6, 0x47, 0x35, 0xa4, 0xd1, 0x40, 0x32, 0xa3,
  0xc4, 0x55, 0x27, 0xb6, 0xc3, 0x52, 0x20, 0xb1,
  0xca, 0x5b, 0x29, 0xb8, 0xcd, 0x5c, 0x2e, 0xbf,
  0x90, 0x01, 0x73, 0xe2, 0x97, 0x06, 0x74, 0xe5,
  0x9e, 0x0f, 0x7d, 0xec, 0x99, 0x08, 0x7a, 0xeb,
  0x8c, 0x1d, 0x6f, 0xfe, 0x8b, 0x1a, 0x68, 0xf9,
  0x82, 0x13, 0x61, 0xf0, 0x85, 0x14, 0x66, 0xf7,
  0xa8, 0x39, 0x4b, 0xda, 0xaf, 0x3e, 0x4c, 0xdd,
  0xa6, 0x37, 0x45, 0xd4, 0xa1, 0x30, 0x42, 0xd3,
  0xb4, 0x25, 0x57, 0xc6, 0xb3, 0x22, 0x50, 0xc1,
  0xba, 0x2b, 0x59, 0xc8, 0xbd, 0x2c, 0x5e, 0xcf
};

//-----------------------------------------------------------------------------
// calculates the CRC-8 from the byte array
uint8_t UTIL::CRC::calculate8(const void* p_buffer, size_t p_bufferSize)
//-----------------------------------------------------------------------------
{
  // typed buffer
  const uint8_t* byteArray = (const uint8_t*) p_buffer;
  // calculation loop
  uint8_t crc = 0;
  for(size_t i = 0; i < p_bufferSize; i++)
  {
    const uint8_t& nextByte = byteArray[i];
    // generator polynom is: X^8 + X^2 + X^1 + X^0
    crc = CRC8_TABLE[crc ^ nextByte];
  }
  return crc;
}

//-----------------------------------------------------------------------------
// calculates the CRC-16 from the byte array
uint16_t UTIL::CRC::calculate16(const void* p_buffer, size_t p_bufferSize)
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
