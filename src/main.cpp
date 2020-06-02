/**
 * Main file for LD32 game Eraser
 */

#include <iostream>
#include <cstdlib>
#include "game_window.h"
#undef main

/**
 * Main program
 * \brief Eraser - SDL2 Game
 **/
int main()
{
	// Windows instanciation
	GameWindow lWindow;
	
	// If local window does not run
	if(lWindow.run() == false)
	{
		// Output error message 
		std::cerr << "An error has occured while loading game !\nPlease take a look on the previous messages." << std::endl;
		
		// Exit failing program
		return EXIT_FAILURE;
	} 
	
	// Exit working program 
	return EXIT_SUCCESS;
}
