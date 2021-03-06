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
	../bin/test_UTIL_DU \
	../bin/test_UTIL_STRING \
	../bin/test_UTIL_VALUE \
	../bin/test_UTIL_VPP

clean:
	\rm -f ../bin/test_UTIL_CircBuffer
	\rm -f ../bin/test_UTIL_CRC
	\rm -f ../bin/test_UTIL_DU
	\rm -f ../bin/test_UTIL_STRING
	\rm -f ../bin/test_UTIL_VALUE
	\rm -f ../bin/test_UTIL_VPP
	\rm -f *.o

tst_UTIL_CircBuffer: ../bin/test_UTIL_CircBuffer
	cd ../bin; ./test_UTIL_CircBuffer

tst_UTIL_CRC: ../bin/test_UTIL_CRC
	cd ../bin; ./test_UTIL_CRC

tst_UTIL_DU: ../bin/test_UTIL_DU
	cd ../bin; ./test_UTIL_DU

tst_UTIL_STRING: ../bin/test_UTIL_STRING
	cd ../bin; ./test_UTIL_STRING

tst_UTIL_VALUE: ../bin/test_UTIL_VALUE
	cd ../bin; ./test_UTIL_VALUE

tst_UTIL_VPP: ../bin/test_UTIL_VPP
	cd ../bin; ./test_UTIL_VPP

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

../bin/test_UTIL_STRING: test_UTIL_STRING.o
	${LINK} -otest_UTIL_STRING \
	test_UTIL_STRING.o \
	${LIBS}
	mv test_UTIL_STRING ../bin

../bin/test_UTIL_VALUE: test_UTIL_VALUE.o
	${LINK} -otest_UTIL_VALUE \
	test_UTIL_VALUE.o \
	${LIBS}
	mv test_UTIL_VALUE ../bin

../bin/test_UTIL_VPP: test_UTIL_VPP.o
	${LINK} -otest_UTIL_VPP \
	test_UTIL_VPP.o \
	${LIBS}
	mv test_UTIL_VPP ../bin

test_UTIL_CircBuffer.o: test_UTIL_CircBuffer.cpp \
	${LIB_UTIL}
	${CPP} -otest_UTIL_CircBuffer.o ${INCLUDES} \
	test_UTIL_CircBuffer.cpp

test_UTIL_CRC.o: test_UTIL_CRC.cpp \
	${LIB_UTIL}
	${CPP} -otest_UTIL_CRC.o ${INCLUDES} \
	test_UTIL_CRC.cpp

test_UTIL_DU.o: test_UTIL_DU.cpp \
	${LIB_UTIL}
	${CPP} -otest_UTIL_DU.o ${INCLUDES} \
	test_UTIL_DU.cpp

test_UTIL_STRING.o: test_UTIL_STRING.cpp \
	${LIB_UTIL}
	${CPP} -otest_UTIL_STRING.o ${INCLUDES} \
	test_UTIL_STRING.cpp

test_UTIL_VALUE.o: test_UTIL_VALUE.cpp \
	${LIB_UTIL}
	${CPP} -otest_UTIL_VALUE.o ${INCLUDES} \
	test_UTIL_VALUE.cpp

test_UTIL_VPP.o: test_UTIL_VPP.cpp \
	${LIB_UTIL}
	${CPP} -otest_UTIL_VPP.o ${INCLUDES} \
	test_UTIL_VPP.cpp
