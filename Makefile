# Variables
CXX = g++
CXXFLAGS = -std=c++14 -Wall -m64 -I include -I C:/SDL2-w64/include
LDFLAGS = -L C:/SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Debug target
debug: CXXFLAGS += -g
debug: bin/debug/main

# Release target
release: CXXFLAGS += -O3
release: bin/release/main

bin/debug/main: $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS) && start cmd /c bin\debug\main

bin/release/main: $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)
