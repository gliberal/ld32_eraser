#include "plantivorus.h"

//Initialize texture
bool Plantivorus::init_texture(SDL_Renderer* pRenderer)
{
	plantivorus_texture = SDL_CreateTextureFromSurface(pRenderer, plantivorus_image);
	if(plantivorus_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(plantivorus_image);
	return true;
}

//Render the texture through given renderer
void Plantivorus::render(SDL_Renderer* pRenderer)
{
	if(current_direction == RIGHT)
	{
		SDL_RenderCopy(pRenderer, plantivorus_texture, &sprite_rect, &plantivorus_rect);
	}
	else
	{
		SDL_RenderCopyEx(pRenderer, plantivorus_texture, &sprite_rect, &plantivorus_rect, 0, nullptr, SDL_FLIP_HORIZONTAL);
	}
}

//Switch spikes length
void Plantivorus::switch_position()
{
	switch(sprite_rect.x)
	{
		case 0:
			sprite_rect.x = 64;
			break;
		case 64:
			sprite_rect.x = 128;
			break;
		default:
			sprite_rect.x = 0;
			break;
	}

	//Switching direction, more dangerous :D
	if(current_direction == LEFT)
	{
		current_direction = RIGHT;
	}
	else
	{
		current_direction = LEFT;
	}		
}
