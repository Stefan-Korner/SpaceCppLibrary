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
       -lpthread
LIB_SCOS = ../lib/libSCOS.a
INCLUDES = -I. -I../src

all:	../bin/test_SCOS_Dummy

clean:
	\rm -f ../bin/test_SCOS_Dummy
	\rm -f *.o

tst_SCOS_Dummy: ../bin/test_SCOS_Dummy
	cd ../bin; ./test_SCOS_Dummy

../bin/test_SCOS_Dummy: test_SCOS_Dummy.o
	${LINK} -otest_SCOS_Dummy \
	test_SCOS_Dummy.o \
	${LIBS}
	mv test_SCOS_Dummy ../bin

test_SCOS_Dummy.o: test_SCOS_Dummy.cpp \
	${LIB_UTIL}
	${CPP} -otest_SCOS_Dummy.o ${INCLUDES} \
	test_SCOSL_Dummy.cpp
