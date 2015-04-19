#include "menu.h"

bool Menu::load(SDL_Renderer* pRenderer, std::string pPath)
{	
	//Initialize background texture
	bg_image = IMG_Load((pPath + "assets/menu.png").c_str());
	bg_texture = SDL_CreateTextureFromSurface(pRenderer, bg_image);
	if(bg_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(bg_image);

	bt_start.load(pRenderer, pPath + "assets/bt_sheet.png");
	bt_exit.load(pRenderer, pPath + "assets/bt_sheet.png");

	return true;
}

void Menu::display(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, bg_texture, &bg_rect, &bg_rect);
	bt_start.display(pRenderer);
	bt_exit.display(pRenderer);
}

void Menu::dispose()
{
	SDL_DestroyTexture(bg_texture);
}

//Check if the given button has been clicked
bool Menu::check_bt_click(int pMouseX, int pMouseY, SDL_Rect* pBtRect)
{
	SDL_Rect mouse_rect;
	mouse_rect.w = 32;
	mouse_rect.h = 32;
	mouse_rect.x = pMouseX;
	mouse_rect.y = pMouseY;

	if(SDL_HasIntersection(&mouse_rect, pBtRect))
	{
		return true;
	}
	return false;
}

//Handle SDL events 
int Menu::check_event(SDL_Event* pEvent)
{
	int ret_val = REQUIRE_NOTHING;
	switch(pEvent->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			if(check_bt_click(pEvent->motion.x, pEvent->motion.y, bt_start.get_rect()))
			{
				ret_val = REQUIRE_PLAY;
			}
			
			if(check_bt_click(pEvent->motion.x, pEvent->motion.y, bt_exit.get_rect()))
			{
				ret_val = REQUIRE_EXIT;
			}

			break;
	}
	return ret_val;
}	
