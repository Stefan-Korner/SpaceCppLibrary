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
LIBS = -L../lib -lSPACE \
       -L../../SCOS/lib -lSCOS \
       -L../../UTIL/lib -lUTIL \
       -lpthread
LIB_SCOS = ../../SCOS/lib/libSCOS.a
LIB_SPACE = ../lib/libSPACE.a
LIB_UTIL = ../../UTIL/lib/libUTIL.a
INCLUDES = -I. \
           -I../src \
           -I../../SCOS/src \
           -I../../UTIL/src

all:	../bin/test_SPACE_DEF \
	../bin/test_SPACE_VPP

clean:
	\rm -f ../bin/test_SPACE_DEF
	\rm -f ../bin/test_SPACE_VPP
	\rm -f *.o

tst_SPACE_DEF: ../bin/test_SPACE_DEF
	cd ../bin; ./test_SPACE_DEF

tst_SPACE_VPP: ../bin/test_SPACE_VPP
	cd ../bin; ./test_SPACE_VPP

../bin/test_SPACE_DEF: test_SPACE_DEF.o
	${LINK} -otest_SPACE_DEF \
	test_SPACE_DEF.o \
	${LIBS}
	mv test_SPACE_DEF ../bin

../bin/test_SPACE_VPP: test_SPACE_VPP.o
	${LINK} -otest_SPACE_VPP \
	test_SPACE_VPP.o \
	${LIBS}
	mv test_SPACE_VPP ../bin

test_SPACE_DEF.o: test_SPACE_DEF.cpp \
	${LIB_SCOS} \
	${LIB_SPACE} \
	${LIB_UTIL}
	${CPP} -otest_SPACE_DEF.o ${INCLUDES} \
	test_SPACE_DEF.cpp

test_SPACE_VPP.o: test_SPACE_VPP.cpp \
	${LIB_SCOS} \
	${LIB_SPACE} \
	${LIB_UTIL}
	${CPP} -otest_SPACE_VPP.o ${INCLUDES} \
	test_SPACE_VPP.cpp
