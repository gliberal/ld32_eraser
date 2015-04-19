#include "arachne.h"

//Initialize texture
bool Arachne::init_texture(SDL_Renderer* pRenderer)
{
	arachne_texture = SDL_CreateTextureFromSurface(pRenderer, arachne_image);
	if(arachne_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(arachne_image);
	return true;
}

//Render the texture through given renderer
void Arachne::render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, arachne_texture, &sprite_rect, &arachne_rect);
}

//Switch spikes length
void Arachne::switch_position()
{
	switch(sprite_rect.x)
	{
		case 0:
			sprite_rect.x = 32;
			break;
		case 32:
			sprite_rect.x = 64;
			break;
		default:
			sprite_rect.x = 0;
			break;
	}
}
