#ifndef ARACHNE_H
#define ARACHNE_H

#include "position.h"
#include <string>
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

class Arachne
{
	private:
		Position pos;
		SDL_Surface* arachne_image;	
		SDL_Texture* arachne_texture;
		SDL_Rect sprite_rect;
		SDL_Rect arachne_rect;

	public:
		static const int POS_0 = 0;
		static const int POS_1 = 32;
		static const int POS_2 = 64;

		//Constructor
		Arachne(std::string pArachnePath="", int pX=0, int pY=0)
		{
			pos = Position(pX, pY);

			arachne_image = IMG_Load(pArachnePath.c_str());

			sprite_rect.w = 32;
			sprite_rect.h = 64;
			sprite_rect.x = 0;
			sprite_rect.y = 0;

			arachne_rect.w = sprite_rect.w;
			arachne_rect.h = sprite_rect.h;
			arachne_rect.x = pos.get_x() * 64;
			arachne_rect.y = pos.get_y() * 64 - 48;
		}

		//Getter for arachne_rect (will be used for collsion)
		SDL_Rect* get_rect(){ return &arachne_rect; }

		//Render the texture through given renderer
		void render(SDL_Renderer* pRenderer);

		//Switch spikes length
		void switch_position();

		//Initialize texture
		bool init_texture(SDL_Renderer* pRenderer);

		//Getter for door texture
		SDL_Texture* get_texture(){return arachne_texture;}
};

#endif
