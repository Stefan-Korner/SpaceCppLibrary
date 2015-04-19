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

# keep the linking order of the libraries
LIBS = -L../lib -lSCOS \
       -L../../UTIL/lib -lUTIL \
       -lpthread
LIB_SCOS = ../lib/libSCOS.a
LIB_UTIL = ../../UTIL/lib/libUTIL.a
INCLUDES = -I. \
           -I../src \
           -I../../UTIL/src

all:	../bin/test_SCOS_MIB

clean:
	\rm -f ../bin/test_SCOS_MIB
	\rm -f *.o

tst_SCOS_MIB: ../bin/test_SCOS_MIB
	cd ../bin; ./test_SCOS_MIB

../bin/test_SCOS_MIB: test_SCOS_MIB.o
	${LINK} -otest_SCOS_MIB \
	test_SCOS_MIB.o \
	${LIBS}
	mv test_SCOS_MIB ../bin

test_SCOS_MIB.o: test_SCOS_MIB.cpp \
	${LIB_SCOS} \
	${LIB_UTIL}
	${CPP} -otest_SCOS_MIB.o ${INCLUDES} \
	test_SCOS_MIB.cpp
