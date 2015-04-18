#ifndef SPIKE_H
#define SPIKE_H

#include "position.h"
#include <string>
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

using namespace std;

class Spike
{
	private:
		Position pos;
		SDL_Surface* spike_image;	
		SDL_Texture* spike_texture;
		SDL_Rect sprite_rect;
		SDL_Rect spike_rect;

	public:
		static const int POS_0 = 0;
		static const int POS_1 = 64;

		//Constructor
		Spike(string pSpikePath="", int pX=0, int pY=0)
		{
			pos = Position(pX, pY);

			spike_image = IMG_Load(pSpikePath.c_str());

			sprite_rect.w = 64;
			sprite_rect.h = 64;
			sprite_rect.x = 0;
			sprite_rect.y = 0;

			spike_rect.w = sprite_rect.w;
			spike_rect.h = sprite_rect.h;
			spike_rect.x = pos.get_x() * 64;
			spike_rect.y = pos.get_y() * 64;
		}

		//Getter for spike_rect (will be used for collsion)
		SDL_Rect* get_rect(){ return &spike_rect; }

		//Render the texture through given renderer
		void render(SDL_Renderer* pRenderer);

		//Switch spikes length
		void switch_spikes();

		//Initialize texture
		bool init_texture(SDL_Renderer* pRenderer);

		//Getter for door texture
		SDL_Texture* get_texture(){return spike_texture;}
};

#endif
