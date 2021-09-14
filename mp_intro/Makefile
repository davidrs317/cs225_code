EXENAME = intro
OBJS = main.o PNG.o HSLAPixel.o lodepng.o intro.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++ly -stdlib=libc++ -lc++abi -lm

#Clang version enforcement logic:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first wen running CS225 assignments. $(ccend))
endif
else
ifneq ($(strip $(SKIP_EWS_CHECK)), True)
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline $(ccend))
endif
endif

.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp intro.h cs225/PNG.h
	clang++ ${CXXFLAGS} main.cpp

PNG.o : cs225/PNG.cpp cs225/PNG.h cs225/RGB_HSL.h cs225/lodepng/lodepng.h
	clang++ ${CXXFLAGS} cs225/PNG.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	clang++ ${CXXFLAGS} cs225/HSLAPixel.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	clang++ ${CXXFLAGS} cs225/lodepng/lodepng.cpp

intro.o : intro.cpp intro.h cs225/PNG.h cs225/HSLAPixel.h
	clang++ ${CXXFLAGS} intro.cpp

tests.o : tests/tests.cpp tests/catch.hpp cs225/PNG.h cs225/HSLAPixel.h
	clang++ ${CXXFLAGS} tests/tests.cpp

test : tests.o intro.o PNG.o HSLAPixel.o lodepng.o
	$(LD) $(OBJS) $(LDFLAGS) -o test

clean:
	rm -f *.o intro test
