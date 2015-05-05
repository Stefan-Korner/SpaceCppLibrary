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
// Space Simulation - Space Data Definitions - Unit Tests                     *
//*****************************************************************************
#include "SPACE_DEF.hpp"

#include <iostream>
#include "SCOS_ENV.hpp"
#include "SCOS_MIB.hpp"
#include "SPACE_DEF.hpp"

using namespace std;

//-----------------------------------------------------------------------------
int main()
//-----------------------------------------------------------------------------
{
  SCOS::ENV::Environment env("../../scosii_homedir");
  SCOS::MIB::Manager mibManager;
  SPACE::DEF::Definitions definitions;
  try
  {
    SCOS::MIB::Manager::instance()->init();
    SPACE::DEF::Definitions::instance()->init();
    SPACE::DEF::Definitions::instance()->dumpDefinitions();
  }
  catch(const UTIL::Exception& ex)
  {
    cout << "Exception: " << ex.what() << endl;
    return -1;
  }
  return 0;
}
