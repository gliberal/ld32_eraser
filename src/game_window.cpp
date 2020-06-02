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

/**
 *init
 *\brief GameWindow inits itself
 **/
bool GameWindow::init()
{
	// SDL components - Init status 
	// 0 : Correct
	// <0 : Incorrect
	if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_EVENTS) < 0)
	{
		// SDL failed
		return false;
	}

	// SDL Window - Init 
	// Window size  :1024 * 768
	display = SDL_CreateWindow("LD32 - Eraser",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		       	1024, 768, SDL_WINDOW_OPENGL);
	
	// SDL Window - Verify
	if(display == nullptr)
	{
		// WINDOW
		// Display failed
		return false;
	}

	// SDL Renderer - Init and verify
	renderer = SDL_CreateRenderer(display, -1, 0);	
	if(renderer == nullptr)
	{
		// WINDOW 
		// Renderer failed
		return false;
	}

	// SDL_Mixer - Init and verify
	if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0)
	{
		return false;
	}

	// SDL_TTF - Init and verify
	if(TTF_Init() < 0)
	{
		return false;
	}

	// SDL Base path
	char* path = SDL_GetBasePath();
	if(path == nullptr)
	{
		// SDL - get pointer for new path 
		base_path = SDL_strdup("./");
	}
	else
	{
		// SDL - get pointer for fetched path
		base_path = SDL_strdup(path);
		
		// SDL - Free path pointer
		SDL_free(path);
	}
	
	return true;
}

/**
 *run 
 *\brief GameWindow runs the game
 *\return boolean : GameWindow run status
 **/ 
bool GameWindow::run()
{
	// Is it running ?--
	// Working : true
	// Failing : false
	is_running = init();
	if(is_running == false)
	{
		return false;
	}
	
	// Loading game objects--
	// Mouse
	if(!mouse.load(renderer, base_path))
	{
		return false;
	}

	// Menu
	if(!menu.load(renderer, base_path))
	{
		return false;
	}
	
	// Level manager
	if(!lvl_manager.load_index(renderer, base_path))
	{
		return false;
	}
		

	// SDL Event listener--
	SDL_Event lEvent;
	
	// Play 
	while(is_running)
	{
		// Begin 
		// (with cleaned render)
		SDL_RenderClear(renderer);

		// Not playing ? 
		if(!is_playing)
		{
			// Show menu
			menu.display(renderer);
		}

		// Playing ?
		else
		{
			// Show level
			is_playing = lvl_manager.display(renderer);
		}
		

		// Event listener
		if(SDL_PollEvent(&lEvent))
		{
			// There is an event
			on_event(&lEvent);

			// It does not play
			if(!is_playing)
			{
				// Menu - Event handler
				int val = menu.check_event(&lEvent);
				switch(val)
				{
					// Loop will continues 
					case Menu::REQUIRE_NOTHING:
						is_playing = false;
						break;
					// Play
					case Menu::REQUIRE_PLAY:
						is_playing = true;
						break;
					// Exit
					case Menu::REQUIRE_EXIT:
						is_running = false;
						break;
				}
			}
			else
			{
				// Level Manager - Get event
				lvl_manager.on_event(&lEvent);
			}
		}
		
		// Mouse displaying 
		// (in renderer)
		mouse.display(renderer);
		
		// Renderer showing 
		// (in current window)
		SDL_RenderPresent(renderer);
	
		//Slow down cycles
		SDL_Delay(16);
	}

	//Dispose menu and mouse memory
	mouse.dispose();
	menu.dispose();

	//Display the ending screen
	SDL_RenderClear(renderer);	
	std::string end_image_path = base_path + "assets/pic_quit.png";
	
	// On game
	if(is_playing)
	{
		// End screen image path
		end_image_path = base_path + "assets/pic_exit.png";
	}
	
	// End screen - Init
	SDL_Surface* end_image = IMG_Load(end_image_path.c_str());
	SDL_Texture* end_texture = SDL_CreateTextureFromSurface(renderer, end_image);
	
	// End sreen - Verify
	if(end_texture > 0)
	{
		// End screen 
		SDL_FreeSurface(end_image);
		SDL_RenderCopy(renderer, end_texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);

		//Slow down cycles (2sec)
		SDL_Delay(2000);
	}
	
	// Clean game objects--
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(display);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	
	// EXIT_SUCCESS
	return true;
}

/**
 * on_event (GameWindow)
 * \brief GameWindow SDL events handler
 * \return void
 **/
void GameWindow::on_event(SDL_Event* pEvent)
{
	switch(pEvent->type)
	{
		case SDL_QUIT:
			is_running = false;
			break;
	}
}	

