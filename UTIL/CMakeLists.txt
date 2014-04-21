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

include_directories(src)

add_library(UTIL
  src/UTIL_CRC.cpp
  src/UTIL_DU.cpp)

add_executable(test_UTIL_CRC
  test/test_UTIL_CRC.cpp)
target_link_libraries(test_UTIL_CRC
  UTIL)

add_executable(test_UTIL_DU
  test/test_UTIL_DU.cpp)
target_link_libraries(test_UTIL_DU
  UTIL)

