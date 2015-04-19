#include "ghost.h"

//Initialize texture
bool Ghost::init_texture(SDL_Renderer* pRenderer)
{
	ghost_texture = SDL_CreateTextureFromSurface(pRenderer, ghost_image);
	if(ghost_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(ghost_image);
	return true;
}

//Render the texture through given renderer
void Ghost::render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, ghost_texture, &sprite_rect, &ghost_rect);
}

//Switch position offset
void Ghost::switch_position()
{
	if(offset_required)
	{
		ghost_rect.y = ghost_rect.y + MOVE_OFFSET;	
	}
	else
	{
		ghost_rect.y = ghost_rect.y - MOVE_OFFSET;
	}
	offset_required = !offset_required;
}
