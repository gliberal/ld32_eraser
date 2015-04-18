#include "mouse_cursor.h"

bool MouseCursor::load(SDL_Renderer* pRenderer, std::string pPath)
{	
	//Initialize background texture
	SDL_Surface* mouse_image = IMG_Load((pPath + "assets/eraser.png").c_str());
	mouse_texture = SDL_CreateTextureFromSurface(pRenderer, mouse_image);
	if(mouse_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(mouse_image);

	//Hide the cursor
	SDL_ShowCursor(SDL_DISABLE);

	return true;
}

void MouseCursor::display(SDL_Renderer* pRenderer)
{
	//Update position x/y
	SDL_GetMouseState(&mouse_pos_rect.x, &mouse_pos_rect.y);

	//Display the cursor
	SDL_RenderCopy(pRenderer, mouse_texture, &mouse_rect, &mouse_pos_rect);	
}

void MouseCursor::dispose()
{
	//Show the sys cursor
	SDL_ShowCursor(SDL_ENABLE);

	//Cleanup Texture
	SDL_DestroyTexture(mouse_texture);
}

