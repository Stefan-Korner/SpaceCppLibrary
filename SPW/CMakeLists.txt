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

add_library(SPW
  src/SPW_PACKET.cpp
	src/SPW_PACKET.hpp
  src/SPW_RMAP_MEMORY.cpp
  src/SPW_RMAP_MEMORY.hpp)

add_executable(test_SPW_RMAP_MEMORY
  test/test_SPW_RMAP_MEMORY.cpp)
target_link_libraries(test_SPW_RMAP_MEMORY
  SPW
  UTIL)

