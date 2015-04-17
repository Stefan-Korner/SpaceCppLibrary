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
// SCOS - Mission Database (MIB) handling                                     *
//*****************************************************************************
#include "SCOS_MIB.hpp"

#include <iostream>

using namespace std;

/////////////
// Manager //
/////////////

// global variables
SCOS::MIB::Manager* SCOS::MIB::Manager::s_instance = NULL;

//-----------------------------------------------------------------------------
SCOS::MIB::Manager::Manager()
//-----------------------------------------------------------------------------
{
  s_instance = this;
}

//-----------------------------------------------------------------------------
SCOS::MIB::Manager::~Manager()
//-----------------------------------------------------------------------------
{
  s_instance = NULL;
}

//-----------------------------------------------------------------------------
SCOS::MIB::Manager* SCOS::MIB::Manager::instance()
//-----------------------------------------------------------------------------
{
  return s_instance;
}
