CXX = g++
CXXFLAGS = -Wall -g

SRC_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main: $(OBJ_FILES)
	$(CXX) -o $@ $^

clean:
	rm -rf $(OBJ_FILES) main

all: main
