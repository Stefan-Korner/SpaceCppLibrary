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
LIBS = -L../lib -lCCSDS \
       -L../../UTIL/lib -lUTIL \
       -lpthread
LIB_CCSDS = ../lib/libCCSDS.a
LIB_UTIL = ../../UTIL/lib/libUTIL.a
INCLUDES = -I. \
           -I../src \
           -I../../UTIL/src

all:	../bin/test_CCSDS_PACKET \
	../bin/test_CCSDS_TIME

clean:
	\rm -f ../bin/test_CCSDS_PACKET
	\rm -f ../bin/test_CCSDS_TIME
	\rm -f *.o

tst_CCSDS_PACKET: ../bin/test_CCSDS_PACKET
	cd ../bin; ./test_CCSDS_PACKET

tst_CCSDS_TIME: ../bin/test_CCSDS_TIME
	cd ../bin; ./test_CCSDS_TIME

../bin/test_CCSDS_PACKET: test_CCSDS_PACKET.o
	${LINK} -otest_CCSDS_PACKET \
	test_CCSDS_PACKET.o \
	${LIBS}
	mv test_CCSDS_PACKET ../bin

../bin/test_CCSDS_TIME: test_CCSDS_TIME.o
	${LINK} -otest_CCSDS_TIME \
	test_CCSDS_TIME.o \
	${LIBS}
	mv test_CCSDS_TIME ../bin

test_CCSDS_PACKET.o: test_CCSDS_PACKET.cpp \
	${LIB_CCSDS} \
	${LIB_UTIL}
	${CPP} -otest_CCSDS_PACKET.o ${INCLUDES} \
	test_CCSDS_PACKET.cpp

test_CCSDS_TIME.o: test_CCSDS_TIME.cpp \
	${LIB_CCSDS} \
	${LIB_UTIL}
	${CPP} -otest_CCSDS_TIME.o ${INCLUDES} \
	test_CCSDS_TIME.cpp
