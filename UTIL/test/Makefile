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
LIBS = -L../lib -lUTIL \
       -lpthread
LIB_UTIL = ../lib/libUTIL.a
INCLUDES = -I. -I../src

all:	../bin/test_UTIL_CircBuffer \
	../bin/test_UTIL_CRC \
	../bin/test_UTIL_DU

clean:
	\rm -f ../bin/test_UTIL_CircBuffer
	\rm -f ../bin/test_UTIL_CRC
	\rm -f ../bin/test_UTIL_DU
	\rm -f *.o

tst_UTIL_CircBuffer: ../bin/test_UTIL_CircBuffer
	cd ../bin; ./test_UTIL_CircBuffer

tst_UTIL_CRC: ../bin/test_UTIL_CRC
	cd ../bin; ./test_UTIL_CRC

tst_UTIL_DU: ../bin/test_UTIL_DU
	cd ../bin; ./test_UTIL_DU

../bin/test_UTIL_CircBuffer: test_UTIL_CircBuffer.o
	${LINK} -otest_UTIL_CircBuffer \
	test_UTIL_CircBuffer.o \
	${LIBS}
	mv test_UTIL_CircBuffer ../bin

../bin/test_UTIL_CRC: test_UTIL_CRC.o
	${LINK} -otest_UTIL_CRC \
	test_UTIL_CRC.o \
	${LIBS}
	mv test_UTIL_CRC ../bin

../bin/test_UTIL_DU: test_UTIL_DU.o
	${LINK} -otest_UTIL_DU \
	test_UTIL_DU.o \
	${LIBS}
	mv test_UTIL_DU ../bin

test_UTIL_CircBuffer.o: test_UTIL_CircBuffer.cpp \
	${LIB_UTIL}
	${CPP} -otest_UTIL_Circbuffer.o ${INCLUDES} \
	test_UTIL_CircBuffer.cpp

test_UTIL_CRC.o: test_UTIL_CRC.cpp \
	${LIB_UTIL}
	${CPP} -otest_UTIL_CRC.o ${INCLUDES} \
	test_UTIL_CRC.cpp

test_UTIL_DU.o: test_UTIL_DU.cpp \
	${LIB_UTIL}
	${CPP} -otest_UTIL_DU.o ${INCLUDES} \
	test_UTIL_DU.cpp
