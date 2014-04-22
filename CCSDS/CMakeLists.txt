#******************************************************************************
# (C) 2014, Stefan Korner, Austria                                            *
#                                                                             *
# The Space C++ Library is free software; you can redistribute it and/or      *
# modify it under the terms of the GNU Lesser General Public License as       *
# published by the Free Software Foundation; either version 2.1 of the        *
# License, or (at your option) any later version.                             *
#                                                                             *
# The Space C++ Library is distributed in the hope that it will be useful,    *
# but WITHOUT ANY WARRANTY; without even the implied warranty of              *
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser     *
# General Public License for more details.                                    *
#******************************************************************************
# cmake configuration file                                                    *
#******************************************************************************

include_directories(src
  ../UTIL/src)

add_library(CCSDS
  src/CCSDS_PACKET.cpp
  src/CCSDS_TIME.cpp)

add_executable(test_CCSDS_TIME
  test/test_CCSDS_TIME.cpp)
target_link_libraries(test_CCSDS_TIME
  CCSDS
  UTIL)

