#ifndef GHOST_H
#define GHOST_H

#include "position.h"
#include <string>
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

class Ghost
{
	private:
		Position pos;
		SDL_Surface* ghost_image;	
		SDL_Texture* ghost_texture;
		SDL_Rect sprite_rect;
		SDL_Rect ghost_rect;
		bool offset_required = false;

	public:
		static const int MOVE_OFFSET = -50;
	
		//Constructor
		Ghost(std::string pGhostPath="", int pX=0, int pY=0)
		{
			pos = Position(pX, pY);

			ghost_image = IMG_Load(pGhostPath.c_str());

			sprite_rect.w = 64;
			sprite_rect.h = 64;
			sprite_rect.x = 0;
			sprite_rect.y = 0;

			ghost_rect.w = sprite_rect.w;
			ghost_rect.h = sprite_rect.h;
			ghost_rect.x = pos.get_x() * 64;
			ghost_rect.y = pos.get_y() * 64 - 32;
		}

		//Getter for ghost_rect (will be used for collsion)
		SDL_Rect* get_rect(){ return &ghost_rect; }

		//Switch position offset
		void switch_position();

		//Render the texture through given renderer
		void render(SDL_Renderer* pRenderer);

		//Initialize texture
		bool init_texture(SDL_Renderer* pRenderer);

		//Getter for door texture
		SDL_Texture* get_texture(){return ghost_texture;}
};

#endif
