#include "menu_button.h"

bool MenuButton::load(SDL_Renderer* pRenderer, std::string pPath)
{	
	//Initialize background texture
	SDL_Surface* bg_image = IMG_Load(pPath.c_str());
	bg_texture = SDL_CreateTextureFromSurface(pRenderer, bg_image);
	if(bg_texture <= 0)
	{
		std::cerr << "Cannot load button background" << std::endl;
		return false;
	}
	SDL_FreeSurface(bg_image);
	
	return true;
}

void MenuButton::display(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, bg_texture, &bg_rect, &bg_pos_rect);
}

void MenuButton::dispose()
{
	SDL_DestroyTexture(bg_texture);
}
