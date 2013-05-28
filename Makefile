CC=gcc
CXX=g++
CFLAGS=-fPIC
ZXING=../..
CXXFLAGS=-ansi -pedantic -O0 -g3 -ggdb -Wall -Wextra -Werror -fPIC
INCLUDE =$(shell php-config --includes)
INCLUDE +=-I. -I$(ZXING)/cpp/core/src

LIB=qrcode_detect.so
OBJS=obj/qrcode_detect_impl.o obj/qrcode_detect_wrap.o obj/ImageReaderSource.o obj/jpgd.o obj/lodepng.o
#swig -php qrcode_detect.i

$(LIB) : $(OBJS)
	@echo $(OBJS)
	$(CXX) -shared -o $@ $? ../build/libzxing.a

clean:
	rm -f *.so
	rm -f obj/*.o
	rm -f core.*

install: $(LIB)
	install -m 0755 $(LIB) `php-config --extension-dir`

obj/%.o : %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

obj/%.o : %.c
	$(CC) -o $@ -c $<  $(CFLAGS) $(shell php-config --includes)
