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
// Utilities - VALUE - Unit Tests                                             *
//*****************************************************************************
#include "UTIL_VALUE.hpp"

#include <iostream>

using namespace std;

#define TEST_VALUE(TXT, EXPR) \
{ \
  UTIL::Value EXPR; \
  value.dump(TXT); \
}

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  try
  {
    TEST_VALUE("value = ", value);
    TEST_VALUE("value(0) = ", value(0));
    TEST_VALUE("value(1) = ", value(1));
    TEST_VALUE("value(-1) = ", value(-1));
    TEST_VALUE("value(false) = ", value(false));
    TEST_VALUE("value(true) = ", value(true));
    TEST_VALUE("value(123.456) = ", value(123.456));
    TEST_VALUE("value(\"this is a text\") = ", value("this is a text"));
    TEST_VALUE("value(\"0123456789\", 10) = ", value("0123456789", 10));
  }
  catch(const UTIL::Exception& ex)
  {
    cout << "Exception: " << ex.what() << endl;
    return -1;
  }
}
