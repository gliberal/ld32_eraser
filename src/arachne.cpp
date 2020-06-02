#include "arachne.h"

/**
 * init_texture
 * \param SDL_Renderer* pRenderer : Game renderer
 * \brief Init texture for arachne enemy
 * \return boolean : Texture creation status
 * */
bool Arachne::init_texture(SDL_Renderer* pRenderer)
{
	// Create texture from surface
	// Surface : renderer & image
	arachne_texture = SDL_CreateTextureFromSurface(pRenderer, arachne_image);
	if(arachne_texture <= 0)
	{
		// Arachne texture failed
		return false;
	}
	
	// Arachne texture - clean
	SDL_FreeSurface(arachne_image);
	return true;
}

/** 
 * render
 * \param SDL_Renderer* pRenderer : Game renderer
 * \brief Render arachne enemy
 * \return void
 **/
void Arachne::render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, arachne_texture, &sprite_rect, &arachne_rect);
}

/**
 * switch_position
 * \brief Set the width according to sprite rect position x
 * \return void
 **/
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
