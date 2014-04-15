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
LIBS = -L../lib -lSPW \
       -L../../UTIL/lib -lUTIL \
       -lpthread
LIB_SPW = ../lib/libSPW.a
LIB_UTIL = ../../UTIL/lib/libUTIL.a
INCLUDES = -I. \
           -I../src \
           -I../../UTIL/src

all:	../bin/test_SPW_RMAP_MEMORY

clean:
	\rm -f ../bin/test_SPW_RMAP_MEMORY
	\rm -f *.o

tst_SPW_RMAP_MEMORY: ../bin/test_SPW_RMAP_MEMORY
	cd ../bin; ./test_SPW_RMAP_MEMORY

../bin/test_SPW_RMAP_MEMORY: test_SPW_RMAP_MEMORY.o
	${LINK} -otest_SPW_RMAP_MEMORY \
	test_SPW_RMAP_MEMORY.o \
	${LIBS}
	mv test_SPW_RMAP_MEMORY ../bin

test_SPW_RMAP_MEMORY.o: test_SPW_RMAP_MEMORY.cpp \
	${LIB_SPW} \
	${LIB_UTIL}
	${CPP} -otest_SPW_RMAP_MEMORY.o ${INCLUDES} \
	test_SPW_RMAP_MEMORY.cpp
