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
// Utilities - Exception type                                                 *
//                                                                            *
// Compatible with std::exception                                             *
//*****************************************************************************
#ifndef UTIL_EXCEPTION_hpp
#define UTIL_EXCEPTION_hpp

#include <string>
#include <exception>

namespace UTIL
{
  class Exception: public std::exception
  {
    std::string m_what;
  public:
    Exception() throw() {}
    Exception(const Exception& p_ex) throw(): std::exception(p_ex) {}
    Exception(const char* p_what) throw(): m_what(p_what) {}
    const Exception& operator=(const Exception& p_ex) throw()
    {
      if(&p_ex != this) {m_what = p_ex.m_what;}
      return *this;
    }
    virtual ~Exception() throw() {}
    virtual const char* what() const throw()
    {
      return m_what.c_str();
    }
  };
};

#endif
