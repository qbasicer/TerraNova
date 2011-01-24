

CFLAGS = -Wall -O2 -Iinclude `sdl-config --cflags` -pg -g
LDFLAGS=`sdl-config --libs` -L/usr/X11R6/lib -L/usr/local/lib -lGL -lGLU -lm -pg -g

COMPILE = $(CXX) $(CFLAGS) -c

OBJFILES := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))

all: terranova

terranova: $(OBJFILES) main.o
	$(CXX) -o terranova $(LDFLAGS) $(OBJFILES) main.o

main.o: main.cpp
	$(COMPILE) -o main.o main.cpp

%.o: %.cpp include/*.h
	$(COMPILE) -o $@ $<

.PHONY: clean

clean:
	rm -f *.o terranova src/*.o

