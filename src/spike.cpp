#include "spike.h"

/**
 * init_texture
 * \param pRenderer : Game renderer
 * \brief Initialize spike texture
 * \return boolean : init spike texture status
 **/
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

/**
 * render
 * \param pRenderer : Game renderer
 * \brief Render the spike texture through given renderer
 * \return void
 **/
void Spike::render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, spike_texture, &sprite_rect, &spike_rect);
}

/**
 * switch spikes
 * \brief Switch spikes length
 * \return void
 **/
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
