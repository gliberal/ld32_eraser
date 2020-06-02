#ifndef MOUSE_CURSOR_H
#define MOUSE_CURSOR_H

#include <string>
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

/**
 * \class MouseCursor
 * \brief Game mouse cursor (it helps to detect mouse actions)
 **/
class MouseCursor
{
	private:
		SDL_Surface* mouse_image;
		SDL_Texture* mouse_texture;
		SDL_Rect mouse_rect;
		SDL_Rect mouse_pos_rect;

	public:
		MouseCursor()
		{
			mouse_rect.w = 57;
			mouse_rect.h = 39;
			mouse_rect.x = 0*mouse_rect.w;
			mouse_rect.y = 0;

			mouse_pos_rect.w = mouse_rect.w;
			mouse_pos_rect.h = mouse_rect.h;
			mouse_pos_rect.x = 0;
			mouse_pos_rect.y = 0;
		}

		//Create the texture from surface
		bool load(SDL_Renderer* pRenderer, std::string pPath);

		//Unload the menu
		void dispose();

		//Display the menu
		void display(SDL_Renderer* pRenderer);
};

#endif
