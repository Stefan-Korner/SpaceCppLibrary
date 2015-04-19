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
// Utilities - string routines                                                *
//*****************************************************************************
#ifndef UTIL_STRING_hpp
#define UTIL_STRING_hpp

#include <list>
#include <string>
#include <vector>
#include "UTIL_EXCEPTION.hpp"

namespace UTIL
{
  //---------------------------------------------------------------------------
  namespace STRING
  //---------------------------------------------------------------------------
  {
    std::string str(int p_val);
    int asInt(const char* p_string);
    int asInt(const std::string& p_string);
    void split(const char* p_text,
               const char* p_seperator,
               std::vector<std::string>& p_tokens);
    void split(const std::string& p_text,
               const char* p_seperator,
               std::vector<std::string>& p_tokens);
    void readTextFile(const char* p_filePath, std::list<std::string>& p_lines)
      throw(UTIL::Exception);
  }
}

#endif
