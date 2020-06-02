#include "plantivorus.h"

/**
 * init_texture
 * \brief Initialize plantivorus texture
 * \return boolean : init texture plantivorus status
 **/
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

/**
 * render
 * \param pRenderer : Game renderer
 * \brief Render the texture through given renderer
 * \return void
 **/
void Plantivorus::render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, plantivorus_texture, &sprite_rect, &plantivorus_rect);
}

/**
 * switch_position
 * \brief Switch spikes length
 * \return void
 **/
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
