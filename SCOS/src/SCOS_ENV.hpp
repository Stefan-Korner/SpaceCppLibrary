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
#ifndef SCOS_ENV_hpp
#define SCOS_ENV_hpp

#include <string>

namespace SCOS
{
  namespace ENV
  {
    //-------------------------------------------------------------------------
    class Environment
    //-------------------------------------------------------------------------
    {
    public:
      // an instance of this class (or a derived class) shall
      // be created and destroyed in main()
      Environment(const char* p_runtimeRoot);
      virtual ~Environment();

      // Environment is a singleton
      static Environment* instance();

      // Get the MIB directory
      virtual std::string mibDir();

    protected:
      std::string m_runtimeRoot;

    private:
      Environment();
      Environment(const Environment& p_service);
      const Environment& operator=(const Environment& p_task);

      static Environment* s_instance;
    };
  }
}

#endif
