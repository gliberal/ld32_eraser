#Define vars
CXX = g++
FLAGS = -Wall -std=c++11
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 
EXEC = eraser

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

#Create the executable file
eraser : $(OBJ)
	$(CXX) $(FLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean: 
	rm -f $(OBJ) $(EXEC)


