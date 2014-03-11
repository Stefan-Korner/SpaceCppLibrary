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
# Makefile                                                                    *
#******************************************************************************
include ../../Makefile.include

LIB_UTIL = ../lib/libUTIL.a
INCLUDES = -I.

all: ${LIB_UTIL}

clean:
	\rm -f ../lib/libUTIL.so ../lib/libUTIL.a *.o

../lib/libUTIL.so: \
	UTIL_CRC.o \
	UTIL_DU.o
	${LIB_DYNAMIC} -olibUTIL.so \
	UTIL_CRC.o \
	UTIL_DU.o
	mv libUTIL.so ../lib

../lib/libUTIL.a: \
	UTIL_CRC.o \
	UTIL_DU.o
	${LIB_STATIC} libUTIL.a \
	UTIL_CRC.o \
	UTIL_DU.o
	mv libUTIL.a ../lib

UTIL_CRC.o: UTIL_CRC.cpp \
	UTIL_CRC.hpp
	${CPP} -oUTIL_CRC.o ${INCLUDES} \
	UTIL_CRC.cpp

UTIL_DU.o: UTIL_DU.cpp \
	UTIL_DU.hpp \
	UTIL_EXCEPTION.hpp \
	UTIL_TIME.hpp
	${CPP} -oUTIL_DU.o ${INCLUDES} \
	UTIL_DU.cpp
