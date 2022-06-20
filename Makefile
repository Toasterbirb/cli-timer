CXX=g++
LIBS=notify
CXXFLAGS=-O3 -std=c++17
SRC=./main.cpp ./timer.cpp
BIN=./timer
INC=-I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/gdk-pixbuf-2.0

all:
	${CXX} ${CXXFLAGS} ${INC} -l${LIBS} ${SRC} -o ${BIN}

clean:
	rm ${BIN}
