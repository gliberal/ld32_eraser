#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

class MenuButton
{
	private:
		//BT vars
		SDL_Rect bg_rect;
		SDL_Rect bg_pos_rect;		
		SDL_Texture* bg_texture;

	public:
		MenuButton(){};
		MenuButton(int pX, int pY, int pOffset)
		{
			bg_rect.w = 161; 
			bg_rect.h = 84;
			bg_rect.x = 0 + pOffset*bg_rect.w;
			bg_rect.y = 0;

			bg_pos_rect.w = bg_rect.w;
			bg_pos_rect.h = bg_rect.h;
			bg_pos_rect.x = pX + bg_rect.w/2;
			bg_pos_rect.y = pY - bg_rect.h/3;
		}

		//Create the texture from surface
		bool load(SDL_Renderer* pRenderer, std::string pPath);

		//Return rect
		SDL_Rect* get_rect(){return &bg_pos_rect;}

		//Unload the menu
		void dispose();

		//Display the menu
		void display(SDL_Renderer* pRenderer);
};

#endif
