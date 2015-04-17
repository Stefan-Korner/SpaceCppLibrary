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

LIB_SCOS = ../lib/libSCOS.a
INCLUDES = -I.

all: ${LIB_SCOS}

clean:
	\rm -f ../lib/libSCOS.so ../lib/libSCOS.a *.o

../lib/libSCOS.so: \
	SCOS_Dummy.o
	${LIB_DYNAMIC} -olibSCOS.so \
	SCOS_Dummy.o
	mv libSCOS.so ../lib

../lib/libSCOS.a: \
	SCOS_Dummy.o
	${LIB_STATIC} libSCOS.a \
	SCOS_Dummy.o
	mv libSCOS.a ../lib

SCOS_Dummy.o: SCOS_Dummy.cpp \
	SCOS_Dummy.hpp
	${CPP} -oSCOS_Dummy.o ${INCLUDES} \
	SCOS_Dummy.cpp
