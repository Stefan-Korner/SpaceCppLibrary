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

# keep the linking order of the libraries
LIBS = -L../lib -lPUS \
       -L../../CCSDS/lib -lCCSDS \
       -L../../UTIL/lib -lUTIL \
       -lpthread
LIB_PUS = ../lib/libPUS.a
LIB_CCSDS = ../../CCSDS/lib/libCCSDS.a
LIB_UTIL = ../../UTIL/lib/libUTIL.a
INCLUDES = -I. \
           -I../src \
           -I../../CCSDS/src \
           -I../../UTIL/src

all:	../bin/test_PUS_SERVICE1

clean:
	\rm -f ../bin/test_PUS_SERVICE1
	\rm -f *.o

tst_PUS_SERVICE1: ../bin/test_PUS_SERVICE1
	cd ../bin; ./test_PUS_SERVICE1

../bin/test_PUS_SERVICE1: test_PUS_SERVICE1.o
	${LINK} -otest_PUS_SERVICE1 \
	test_PUS_SERVICE1.o \
	${LIBS}
	mv test_PUS_SERVICE1 ../bin

test_PUS_SERVICE1.o: test_PUS_SERVICE1.cpp \
	${LIB_PUS} \
	${LIB_CCSDS} \
	${LIB_UTIL}
	${CPP} -otest_PUS_SERVICE1.o ${INCLUDES} \
	test_PUS_SERVICE1.cpp
