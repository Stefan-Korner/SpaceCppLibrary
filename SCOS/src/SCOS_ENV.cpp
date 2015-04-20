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
// SCOS - Environment handling                                                *
//*****************************************************************************
#include "SCOS_ENV.hpp"

using namespace std;

/////////////////
// Environment //
/////////////////

// global variables
SCOS::ENV::Environment* SCOS::ENV::Environment::s_instance = NULL;

//-----------------------------------------------------------------------------
SCOS::ENV::Environment::Environment(const char* p_runtimeRoot):
  m_runtimeRoot(p_runtimeRoot)
//-----------------------------------------------------------------------------
{
  s_instance = this;
}

//-----------------------------------------------------------------------------
SCOS::ENV::Environment::~Environment()
//-----------------------------------------------------------------------------
{
  s_instance = NULL;
}

//-----------------------------------------------------------------------------
SCOS::ENV::Environment* SCOS::ENV::Environment::instance()
//-----------------------------------------------------------------------------
{
  return s_instance;
}

//-----------------------------------------------------------------------------
string SCOS::ENV::Environment::mibDir()
//-----------------------------------------------------------------------------
{
  return m_runtimeRoot + "/data/ASCII";
}
