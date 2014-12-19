CXX	:= g++
CXXFLAGS:= -std=c++11
WARN	:= -Wall
OBJECTS	:= Cell.o Mineral.o Iron.o Copper.o Gold.o Diamond.o Ground.o Surface.o Frame.o
LIBS	:= -lSDL2

all: main

main: ${OBJECTS} main.cpp
	${CXX} ${CXXFLAGS} ${WARN} main.cpp ${OBJECTS} -o main ${LIBS}

minerals: minerals.cpp
	${CXX} ${CXXFLAGS} ${WARN} minerals.cpp -o minerals -lSDL2

Cell.o: Cell.cpp Cell.h
	${CXX} ${CXXFLAGS} -c Cell.cpp

Mineral.o: Mineral.cpp Mineral.h
	${CXX} ${CXXFLAGS} -c Mineral.cpp

Iron.o: Iron.cpp Iron.h Mineral.h
	${CXX} ${CXXFLAGS} -c Iron.cpp

Copper.o: Copper.cpp Copper.h Mineral.h
	${CXX} ${CXXFLAGS} -c Copper.cpp

Gold.o: Gold.cpp Gold.h Mineral.h
	${CXX} ${CXXFLAGS} -c Gold.cpp

Diamond.o: Diamond.cpp Diamond.h Mineral.h
	${CXX} ${CXXFLAGS} -c Diamond.cpp

Ground.o: Ground.cpp Ground.h
	${CXX} ${CXXFLAGS} -c Ground.cpp

Surface.o: Surface.cpp Surface.h
	${CXX} ${CXXFLAGS} -c Surface.cpp

Frame.o: Frame.cpp Frame.h
	${CXX} ${CXXFLAGS} -c Frame.cpp

clean:
	-rm *.o main
