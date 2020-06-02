#ifndef MENU_H
#define MENU_H

#include <string>
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

#include "menu_button.h"

/**
 * \class Menu
 * \brief Game menu
 **/
class Menu
{
	private:
		SDL_Surface* bg_image;
		SDL_Texture* bg_texture;
		SDL_Rect bg_rect;

		MenuButton bt_start;
		MenuButton bt_exit;

	public:
		static const int REQUIRE_NOTHING = 0;
		static const int REQUIRE_PLAY = 1;
		static const int REQUIRE_EXIT = 2;

		Menu()
		{
			bg_rect.w = 1024;
			bg_rect.h = 768;
			bg_rect.x = 0;
			bg_rect.y = 0;
		
			bt_start = MenuButton(2*bg_rect.w/3, bg_rect.h/2, 1);
			bt_exit = MenuButton(2*bg_rect.w/3, 2*bg_rect.h/3, 0);
		}

		//Create the texture from surface
		bool load(SDL_Renderer* pRenderer, std::string pPath);

		//Unload the menu
		void dispose();

		//Display the menu
		void display(SDL_Renderer* pRenderer);

		//Check if the given button has been clicked
		bool check_bt_click(int pMouseX, int pMouseY, SDL_Rect* pBtRect);

		//On event
		int check_event(SDL_Event* pEvent);
};

#endif
