#include "pencil.h"

//Initialize texture
bool Pencil::init_texture(SDL_Renderer* pRenderer)
{
	pencil_texture = SDL_CreateTextureFromSurface(pRenderer, pencil_image);
	if(pencil_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(pencil_image);
	return true;
}

//Render the texture through given renderer
void Pencil::render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, pencil_texture, &sprite_rect, &pencil_rect);
}
