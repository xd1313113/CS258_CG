SHELL = /bin/sh
#prefix = /usr/lib/i386-linux-gnu
prefix = ./lib
CC = gcc
C++ = g++
GLUT_LIBS = $(prefix)/libglut.so
X_LIBADD =  -lXmu -lXext -lXi -lX11
INCLUDES = -Iinclude -I/usr/include  
LDADD = $(GLUT_LIBS) $(prefix)/libGLU.so $(prefix)/libGL.so  -lm
CFLAGS = -g -O2 -Wall -fomit-frame-pointer -ffast-math -fexpensive-optimizations -D_REENTRANT
COMPILE = $(C++) $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
LINK = $(C++) $(CFLAGS) $(LDFLAGS) -o $@

.SUFFIXES:
.SUFFIXES: .cpp .c .o 

.c.o:
	$(COMPILE) -c $<

.cpp.o:
	$(C++) $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS) -c $<

all: main

CLI_OBJECTS=main.o Dispatcher.o CMDColor.o CMDDraw.o CMDMove.o CMDRead.o

main: $(CLI_OBJECTS)
	$(LINK) $(CLI_OBJECTS) $(LDADD) $(LIBS)

clean:
	-rm -f *.o $(PROGRAMS)

