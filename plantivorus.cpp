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
	SDL_RenderCopy(pRenderer, plantivorus_texture, &sprite_rect, &plantivorus_rect);
}

//Switch spikes length
void Plantivorus::switch_position()
{
	switch(sprite_rect.x)
	{
		case 0:
			sprite_rect.x = 96;
			break;
		case 96:
			sprite_rect.x = 192;
			break;
		default:
			sprite_rect.x = 0;
			break;
	}
}
