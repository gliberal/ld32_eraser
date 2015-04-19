#include "time_bonus.h"

//Initialize texture
bool TimeBonus::init_texture(SDL_Renderer* pRenderer)
{
	time_bonus_texture = SDL_CreateTextureFromSurface(pRenderer, time_bonus_image);
	if(time_bonus_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(time_bonus_image);
	return true;
}

//Render the texture through given renderer
void TimeBonus::render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, time_bonus_texture, &sprite_rect, &time_bonus_rect);
}
