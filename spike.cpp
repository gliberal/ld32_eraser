#include "spike.h"

//Initialize texture
bool Spike::init_texture(SDL_Renderer* pRenderer)
{
	spike_texture = SDL_CreateTextureFromSurface(pRenderer, spike_image);
	if(spike_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(spike_image);
	return true;
}

//Render the texture through given renderer
void Spike::render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, spike_texture, &sprite_rect, &spike_rect);
}

//Switch spikes length
void Spike::switch_spikes()
{
	if(sprite_rect.x == 0)
	{
		sprite_rect.x = 64;
	}
	else
	{
		sprite_rect.x = 0;
	}
}
