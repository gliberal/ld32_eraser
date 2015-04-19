#include "game_window.h"

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#endif

//Initialize an 1024x768 SDL window
bool GameWindow::init()
{
	//Try to initailize all SDL component and check if it works
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_EVENTS) < 0)
	{
		return false;
	}

	//Create a window and check if it works
	display = SDL_CreateWindow("LD32 - Eraser",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		       	1024, 768, SDL_WINDOW_OPENGL);
	
	if(display == nullptr)
	{
		return false;
	}

	//Create the renderer
	renderer = SDL_CreateRenderer(display, -1, 0);
	if(renderer == nullptr)
	{
		return false;
	}

	//Initialize SDL_Mixer
	if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0)
	{
		return false;
	}

	//Initialize SDL_TTF
	if(TTF_Init() < 0)
	{
		return false;
	}

	//Initialize base path
	char* path = SDL_GetBasePath();
	if(path == nullptr)
	{
		base_path = SDL_strdup("./");
	}
	else
	{
		base_path = SDL_strdup(path);
		SDL_free(path);
	}
	
	return true;
}

bool GameWindow::run()
{
	is_running = init();
	if(is_running == false)
	{
		//Init phase fails
		return false;
	}

	if(!mouse.load(renderer, base_path))
	{
		return false;
	}

	if(!menu.load(renderer, base_path))
	{
		return false;
	}

	if(!lvl_manager.load_index(renderer, base_path))
	{
		return false;
	}

	SDL_Event lEvent;

	while(is_running)
	{
		SDL_RenderClear(renderer);

		if(!is_playing)
		{
			menu.display(renderer);
		}
		else
		{
			is_playing = lvl_manager.display(renderer);
		}

		if(SDL_PollEvent(&lEvent))
		{
			on_event(&lEvent);
			if(!is_playing)
			{
				int val = menu.check_event(&lEvent);
				switch(val)
				{
					case Menu::REQUIRE_NOTHING:
						is_playing = false;
						break;
					case Menu::REQUIRE_PLAY:
						is_playing = true;
						break;
					case Menu::REQUIRE_EXIT:
						is_running = false;
						break;
				}
			}
			else
			{
				lvl_manager.on_event(&lEvent);
			}
		}

		mouse.display(renderer);
		SDL_RenderPresent(renderer);
	
		//Slow down cycles
		SDL_Delay(16);
	}

	//Dispose menu and mouse memory
	mouse.dispose();
	menu.dispose();

	//Slow down cycles
	SDL_Delay(1800);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(display);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	return true;
}

//Handle SDL events 
void GameWindow::on_event(SDL_Event* pEvent)
{
	switch(pEvent->type)
	{
		case SDL_QUIT:
			is_running = false;
			break;
	}
}	

