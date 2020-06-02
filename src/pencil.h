#ifndef PENCIL_H
#define PENCIL_H

#include "position.h"
#include <string>
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

/**
 * \class Pencil
 * \brief Pencil game object
 **/
class Pencil
{
	private:
		Position pos;
		SDL_Surface* pencil_image;	
		SDL_Texture* pencil_texture;
		SDL_Rect sprite_rect;
		SDL_Rect pencil_rect;

	public:
		//Constructor
		Pencil(std::string pPencilPath="", int pX=0, int pY=0)
		{
			pos = Position(pX, pY);

			pencil_image = IMG_Load(pPencilPath.c_str());

			sprite_rect.w = 32;
			sprite_rect.h = 112;
			sprite_rect.x = 0;
			sprite_rect.y = 0;

			pencil_rect.w = sprite_rect.w;
			pencil_rect.h = sprite_rect.h;
			pencil_rect.x = pos.get_x() * 64;
			pencil_rect.y = pos.get_y() * 64-48;
		}

		//Getter for pencil_rect (will be used for collsion)
		SDL_Rect* get_rect(){ return &pencil_rect; }

		//Render the texture through given renderer
		void render(SDL_Renderer* pRenderer);

		//Initialize texture
		bool init_texture(SDL_Renderer* pRenderer);

		//Getter for door texture
		SDL_Texture* get_texture(){return pencil_texture;}
};

#endif
