#ifndef TIME_BONUS_H
#define TIME_BONUS_H

#include "position.h"
#include <string>
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

/**
 *\class TimeBonus
 *\brief time expansion colletible
 **/
class TimeBonus
{
	private:
		Position pos;
		SDL_Surface* time_bonus_image;	
		SDL_Texture* time_bonus_texture;
		SDL_Rect sprite_rect;
		SDL_Rect time_bonus_rect;

	public:
		//Constructor
		TimeBonus(std::string pTimeBonusPath="", int pX=0, int pY=0)
		{
			pos = Position(pX, pY);

			time_bonus_image = IMG_Load(pTimeBonusPath.c_str());

			sprite_rect.w = 64;
			sprite_rect.h = 64;
			sprite_rect.x = 0;
			sprite_rect.y = 0;

			time_bonus_rect.w = sprite_rect.w;
			time_bonus_rect.h = sprite_rect.h;
			time_bonus_rect.x = pos.get_x() * 64;
			time_bonus_rect.y = pos.get_y() * 64;
		}

		//Getter for time_bonus_rect (will be used for collsion)
		SDL_Rect* get_rect(){ return &time_bonus_rect; }

		//Render the texture through given renderer
		void render(SDL_Renderer* pRenderer);

		//Initialize texture
		bool init_texture(SDL_Renderer* pRenderer);

		//Getter for time_bonus texture
		SDL_Texture* get_texture(){return time_bonus_texture;}
};

#endif
