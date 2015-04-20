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
// Space Simulation - Space Data Definitions                                  *
//*****************************************************************************
#ifndef SPACE_DEF_hpp
#define SPACE_DEF_hpp

namespace SPACE
{
  namespace DEF
  {
    //-------------------------------------------------------------------------
    class Definitions
    //-------------------------------------------------------------------------
    {
    public:
      // an instance of this class (or a derived class) shall
      // be created and destroyed in main()
      Definitions();
      virtual ~Definitions();

      // Definitions is a singleton
      static Definitions* instance();

    private:
      Definitions(const Definitions& p_service);
      const Definitions& operator=(const Definitions& p_task);

      static Definitions* s_instance;
    };
  }
}

#endif
