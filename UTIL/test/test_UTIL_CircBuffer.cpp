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
// Utilities - Circular Buffer - Unit Tests                                   *
//*****************************************************************************
#include "UTIL_CircBuffer.hpp"

#include <iostream>
using namespace std;

//-----------------------------------------------------------------------------
void dump(const UTIL::CircBuffer& p_buffer)
//-----------------------------------------------------------------------------
{
  cout << "--- Circular Buffer ---" << endl;
  cout << "size() = " << p_buffer.size() << endl;
  cout << "freeSize() = " << p_buffer.freeSize() << endl;
  for(size_t i = 0; i < p_buffer.size(); i++)
  {
    cout << "p_buffer[" << i << "] = " << ((int) p_buffer[i]) << endl;
  }
}

//-----------------------------------------------------------------------------
void dump(const uint8_t* p_buffer, size_t p_bufferSize)
//-----------------------------------------------------------------------------
{
  cout << "--- Linear Buffer ---" << endl;
  cout << "p_bufferSize = " << p_bufferSize << endl;
  for(size_t i = 0; i < p_bufferSize; i++)
  {
    cout << "p_buffer[" << i << "] = " << ((int) p_buffer[i]) << endl;
  }
}

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  UTIL::CircBuffer cBuffer(10);
  uint8_t lBuffer[10];
  cout << "*** empty buffer ***" << endl;
  cBuffer.front(lBuffer, cBuffer.size());
  dump(cBuffer);
  dump(lBuffer, cBuffer.size());
  cout << "*** pushBack(\"0123\") ***" << endl;
  cBuffer.pushBack("0123", 4);
  cBuffer.front(lBuffer, cBuffer.size());
  dump(cBuffer);
  dump(lBuffer, cBuffer.size());
  cout << "*** popFront(2) ***" << endl;
  cBuffer.popFront(2);
  cBuffer.front(lBuffer, cBuffer.size());
  dump(cBuffer);
  dump(lBuffer, cBuffer.size());
  cout << "*** pushBack(\"456\") ***" << endl;
  cBuffer.pushBack("456", 3);
  cBuffer.front(lBuffer, cBuffer.size());
  dump(cBuffer);
  dump(lBuffer, cBuffer.size());
  cout << "*** pushBack(\"789A\") ***" << endl;
  cBuffer.pushBack("789A", 4);
  cBuffer.front(lBuffer, cBuffer.size());
  dump(cBuffer);
  dump(lBuffer, cBuffer.size());
  return 0;
}
