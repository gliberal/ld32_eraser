#include "door.h"

/**
 *init_texture
 *\param pRenderer : Game renderer
 *\brief init door texture
 *\return boolean : init texture status
 **/
bool Door::init_texture(SDL_Renderer* pRenderer)
{
	door_texture = SDL_CreateTextureFromSurface(pRenderer, door_image);
	if(door_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(door_image);
	return true;
}

/*
 *render
 *\param pRenderer : Game renderer
 *\brief render door
 *\return void
 **/
void Door::render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, door_texture, &sprite_rect, &door_rect);
}
