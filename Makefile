#Define vars
CC = g++
FLAGS = -Wall -std=c++11
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 
EXEC = eraser

BASIC_OBJS = player.o menu.o menu_button.o door.o pencil.o mouse_cursor.o position.o
COMPLEX_OBJS = game_window.o level_manager.o level.o
DANGEROUS_OBJS = spike.o plantivorus.o arachne.o ghost.o
OBJ_FILES = main.o $(BASIC_OBJS) $(COMPLEX_OBJS) $(DANGEROUS_OBJS)

#Define the ALL scope (default)
all: clean game 

#Create the executable file
game : main
	$(CC) -o $(EXEC) $(LIBS) $(OBJ_FILES) 

main: complex_components
	$(CC) -c $(FLAGS) main.cpp

complex_components: dangerous_components
	$(CC) -c $(FLAGS) game_window.cpp level_manager.cpp level.cpp

dangerous_components: basic_components
	$(CC) -c $(FLAGS) spike.cpp plantivorus.cpp arachne.cpp ghost.cpp

basic_components: 
	$(CC) -c $(FLAGS) player.cpp menu.cpp menu_button.cpp door.cpp pencil.cpp mouse_cursor.cpp position.cpp

clean: 
	rm -f *.o $(EXEC)

