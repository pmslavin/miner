CXX	:= g++
CXXFLAGS:= -std=c++11
WARN	:= -Wall
OBJECTS	:= Cell.o Mineral.o Iron.o Copper.o Ground.o
LIBS	:=

all: main

main: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${WARN} main.cpp ${OBJECTS} -o main ${LIBS}

Cell.o: Cell.cpp Cell.h
	${CXX} ${CXXFLAGS} -c Cell.cpp

Mineral.o: Mineral.cpp Mineral.h
	${CXX} ${CXXFLAGS} -c Mineral.cpp

Iron.o: Iron.cpp Iron.h Mineral.h
	${CXX} ${CXXFLAGS} -c Iron.cpp

Copper.o: Copper.cpp Copper.h Mineral.h
	${CXX} ${CXXFLAGS} -c Copper.cpp

Ground.o: Ground.cpp Ground.h
	${CXX} ${CXXFLAGS} -c Ground.cpp

clean:
	-rm *.o main
