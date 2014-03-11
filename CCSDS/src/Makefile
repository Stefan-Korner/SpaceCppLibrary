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

LIB_CCSDS = ../lib/libCCSDS.a
LIB_UTIL = ../../UTIL/lib/libUTIL.a
INCLUDES = -I. \
           -I../../UTIL/src

all: ${LIB_CCSDS}

clean:
	\rm -f ../lib/libCCSDS.so ../lib/libCCSDS.a *.o

../lib/libCCSDS.so: \
	CCSDS_PACKET.o \
	CCSDS_TIME.o
	${LIB_DYNAMIC} -olibCCSDS.so \
	CCSDS_PACKET.o \
	CCSDS_TIME.o
	mv libCCSDS.so ../lib

../lib/libCCSDS.a: \
	CCSDS_PACKET.o \
	CCSDS_TIME.o
	${LIB_STATIC} libCCSDS.a \
	CCSDS_PACKET.o \
	CCSDS_TIME.o
	mv libCCSDS.a ../lib

CCSDS_PACKET.o: CCSDS_PACKET.cpp \
	CCSDS_PACKET.hpp \
	CCSDS_TIME.hpp \
	${LIB_UTIL}
	${CPP} -oCCSDS_PACKET.o ${INCLUDES} \
	CCSDS_PACKET.cpp

CCSDS_TIME.o: CCSDS_TIME.cpp \
	CCSDS_TIME.hpp \
	${LIB_UTIL}
	${CPP} -oCCSDS_TIME.o ${INCLUDES} \
	CCSDS_TIME.cpp
