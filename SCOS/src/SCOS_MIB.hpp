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
#ifndef SCOS_MIB_hpp
#define SCOS_MIB_hpp

namespace SCOS
{
  namespace MIB
  {
    //-------------------------------------------------------------------------
    class Manager
    //-------------------------------------------------------------------------
    {
    public:
      // the manager (or a derived class) shall
      // be created and destroyed in main()
      Manager();
      virtual ~Manager();

      // the manager is a singleton
      static Manager* instance();

    private:
      Manager(const Manager& p_service);
      const Manager& operator=(const Manager& p_task);

      static Manager* s_instance;
    };
  }
}

#endif
