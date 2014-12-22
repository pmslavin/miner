CXX	:= g++
CXXFLAGS:= -std=c++11 -g
WARN	:= -Wall
OBJECTS	:= Cell.o Mineral.o Iron.o Copper.o Gold.o Diamond.o Uranium.o Ground.o Surface.o Frame.o RoboMiner.o Base.o
LIBS	:= -lSDL2

all: main

main: ${OBJECTS} main.cpp
	${CXX} ${CXXFLAGS} ${WARN} main.cpp ${OBJECTS} -o main ${LIBS}

minerals: minerals.cpp
	${CXX} ${CXXFLAGS} ${WARN} minerals.cpp -o minerals -lSDL2

Cell.o: Cell.cpp Cell.h
	${CXX} ${CXXFLAGS} ${WARN} -c Cell.cpp

Mineral.o: Mineral.cpp Mineral.h
	${CXX} ${CXXFLAGS} ${WARN} -c Mineral.cpp

Iron.o: Iron.cpp Iron.h Mineral.h
	${CXX} ${CXXFLAGS} ${WARN} -c Iron.cpp

Copper.o: Copper.cpp Copper.h Mineral.h
	${CXX} ${CXXFLAGS} ${WARN} -c Copper.cpp

Gold.o: Gold.cpp Gold.h Mineral.h
	${CXX} ${CXXFLAGS} ${WARN} -c Gold.cpp

Diamond.o: Diamond.cpp Diamond.h Mineral.h
	${CXX} ${CXXFLAGS} ${WARN} -c Diamond.cpp

Uranium.o: Uranium.cpp Uranium.h Mineral.h
	${CXX} ${CXXFLAGS} ${WARN} -c Uranium.cpp

Ground.o: Ground.cpp Ground.h
	${CXX} ${CXXFLAGS} ${WARN} -c Ground.cpp

Surface.o: Surface.cpp Surface.h
	${CXX} ${CXXFLAGS} ${WARN} -c Surface.cpp

Frame.o: Frame.cpp Frame.h
	${CXX} ${CXXFLAGS} ${WARN} -c Frame.cpp

RoboMiner.o: RoboMiner.cpp RoboMiner.h
	${CXX} ${CXXFLAGS} ${WARN} -c RoboMiner.cpp

Base.o: Base.cpp Base.h
	${CXX} ${CXXFLAGS} ${WARN} -c Base.cpp

clean:
	-rm *.o main
