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

LIB_SPW = ../lib/libSPW.a
LIB_UTIL = ../../UTIL/lib/libUTIL.a
INCLUDES = -I. \
           -I../../UTIL/src

all: ${LIB_SPW}

clean:
	\rm -f ../lib/libSPW.so ../lib/libSPW.a *.o

../lib/libSPW.so: \
	SPW_PACKET.o
	${LIB_DYNAMIC} -olibSPW.so \
	SPW_PACKET.o
	mv libSPW.so ../lib

../lib/libSPW.a: \
	SPW_PACKET.o
	${LIB_STATIC} libSPW.a \
	SPW_PACKET.o
	mv libSPW.a ../lib

SPW_PACKET.o: SPW_PACKET.cpp \
	SPW_PACKET.hpp \
	${LIB_UTIL}
	${CPP} -oSPW_PACKET.o ${INCLUDES} \
	SPW_PACKET.cpp
