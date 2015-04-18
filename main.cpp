/**
 * Main file for LD32 game Eraser
 */

#include <iostream>

#include "game_window.h"
#undef main

using namespace std;

int main()
{
	GameWindow lWindow;
	if(lWindow.run() == false)
	{
		cerr << "An error has occured while loading game !\nPlease take a look on the previous messages." << endl;
	}

	return 0;
}
