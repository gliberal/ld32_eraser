#include "menu.h"

// Menu - Load
bool Menu::load(SDL_Renderer* pRenderer, std::string pPath)
{	
	// Background - Init
	bg_image = IMG_Load((pPath + "assets/menu.png").c_str());
	bg_texture = SDL_CreateTextureFromSurface(pRenderer, bg_image);
	

	// Background - Verify 
	if(bg_texture <= 0)
	{
		// Background fails
		return false;
	}


	// Background - Clean
	SDL_FreeSurface(bg_image);
	

	// Buttons-
	bt_start.load(pRenderer, pPath + "assets/bt_sheet.png");
	bt_exit.load(pRenderer, pPath + "assets/bt_sheet.png");

	return true;
}

// Menu - Display
void Menu::display(SDL_Renderer* pRenderer)
{
	
	// Background
	SDL_RenderCopy(pRenderer, bg_texture, &bg_rect, &bg_rect);
	
	// Buttons
	bt_start.display(pRenderer);
	bt_exit.display(pRenderer);
}

// Menu - Dispose
void Menu::dispose()
{
	// Clean 
	SDL_DestroyTexture(bg_texture);
}


// Button - Event handler
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

// Menu - Check event
int Menu::check_event(SDL_Event* pEvent)
{
	// Event default : Nothing to do
	int ret_val = REQUIRE_NOTHING;
	
	// Event handler 
	switch(pEvent->type)
	{
		// Click
		case SDL_MOUSEBUTTONDOWN:
			
			// Click on button start
			if(check_bt_click(pEvent->motion.x, pEvent->motion.y, bt_start.get_rect()))
			{
				ret_val = REQUIRE_PLAY;
			}
			
			// Click on button quit
			if(check_bt_click(pEvent->motion.x, pEvent->motion.y, bt_exit.get_rect()))
			{
				ret_val = REQUIRE_EXIT;
			}

			break;
	}
	return ret_val;
}	
