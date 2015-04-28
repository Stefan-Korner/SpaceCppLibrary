#******************************************************************************
# (C) 2015, Stefan Korner, Austria                                            *
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

LIB_SCOS = ../../SCOS/lib/libSCOS.a
LIB_SPACE = ../lib/libSPACE.a
LIB_UTIL = ../../UTIL/lib/libUTIL.a
INCLUDES = -I. \
           -I../../SCOS/src \
           -I../../UTIL/src

all: ${LIB_SPACE}

clean:
	\rm -f ../lib/libSPACE.so ../lib/libSPACE.a *.o

../lib/libSPACE.so: \
	SPACE_DEF.o \
	SPACE_VPP.o
	${LIB_DYNAMIC} -olibSPACE.so \
	SPACE_DEF.o \
	SPACE_VPP.o
	mv libSPACE.so ../lib

../lib/libSPACE.a: \
	SPACE_DEF.o \
	SPACE_VPP.o
	${LIB_STATIC} libSPACE.a \
	SPACE_DEF.o \
	SPACE_VPP.o
	mv libSPACE.a ../lib

SPACE_DEF.o: SPACE_DEF.cpp \
	SPACE_DEF.hpp \
	${LIB_SCOS} \
	${LIB_UTIL}
	${CPP} -oSPACE_DEF.o ${INCLUDES} \
	SPACE_DEF.cpp

SPACE_VPP.o: SPACE_VPP.cpp \
	SPACE_VPP.hpp \
	${LIB_SCOS} \
	${LIB_UTIL}
	${CPP} -oSPACE_VPP.o ${INCLUDES} \
	SPACE_VPP.cpp
