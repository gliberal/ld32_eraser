#Define vars
CC = g++
FLAGS = -Wall -std=c++11
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 
EXEC = eraser

BASIC_OBJS = player.o menu.o menu_button.o door.o pencil.o mouse_cursor.o position.o
COMPLEX_OBJS = game_window.o level_manager.o level.o
INTERACTIVE_OBJS = spike.o plantivorus.o arachne.o ghost.o monster.o time_bonus.o
OBJ_FILES = main.o $(BASIC_OBJS) $(COMPLEX_OBJS) $(INTERACTIVE_OBJS)

#Define the ALL scope (default)
all: clean game 

#Create the executable file
game : main
	$(CC) -o $(EXEC) $(LIBS) $(OBJ_FILES) 

main: complex_components
	$(CC) -c $(FLAGS) main.cpp

complex_components: interactive_components
	$(CC) -c $(FLAGS) game_window.cpp level_manager.cpp level.cpp

interactive_components: basic_components
	$(CC) -c $(FLAGS) spike.cpp plantivorus.cpp arachne.cpp ghost.cpp monster.cpp time_bonus.cpp

basic_components: 
	$(CC) -c $(FLAGS) player.cpp menu.cpp menu_button.cpp door.cpp pencil.cpp mouse_cursor.cpp position.cpp

clean: 
	rm -f *.o $(EXEC)

