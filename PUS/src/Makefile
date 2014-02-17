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

LIB_UTIL = ../../UTIL/lib/libUTIL.a
LIB_CCSDS = ../../CCSDS/lib/libCCSDS.a
LIB_PUS = ../lib/libPUS.a
INCLUDES = -I. \
           -I../../CCSDS/src \
           -I../../UTIL/src

all: ${LIB_PUS}

clean:
	\rm -f ../lib/libPUS.so ../lib/libPUS.a *.o

../lib/libPUS.so: \
	PUS_PACKET.o
	${LIB_DYNAMIC} -olibPUS.so \
	PUS_PACKET.o
	mv libPUS.so ../lib

../lib/libPUS.a: \
	PUS_PACKET.o
	${LIB_STATIC} libPUS.a \
	PUS_PACKET.o
	mv libPUS.a ../lib

PUS_PACKET.o: PUS_PACKET.cpp \
	PUS_PACKET.hpp \
	${LIB_CCSDS} \
	${LIB_UTIL}
	${CPP} -oPUS_PACKET.o ${INCLUDES} \
	PUS_PACKET.cpp
