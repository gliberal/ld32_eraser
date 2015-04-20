#include "level_manager.h"
#include <fstream>

#ifdef __APPLE__
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

//Init paths
void LevelManager::init_paths(string pPath)
{
	level_base_path = pPath;
	level_data_path = level_base_path + "data/";
	level_asset_path = level_base_path + "assets/";
	index_path = level_data_path + INDEX_FILENAME;
}

//Load the lvl_index file
bool LevelManager::load_index(SDL_Renderer* pRenderer, string pPath)
{
	init_paths(pPath);
	ifstream index_file(index_path);
	if(index_file.is_open())
	{
		string line;
		while(getline(index_file, line))
		{
			level_ids.push_back(line);
		}	
		index_file.close();	
	}
	else
	{
		return false;
	}

	return true;	
}

//Display the current level
bool LevelManager::display(SDL_Renderer* pRenderer)
{
	if(current_level_id > -1)
	{
		if(current_level.is_finished())
		{
			//Load next level
			if(!prepare_next_level(pRenderer))
			{
				current_level_id = -1;
				return false;
			}
		}
	}
	else
	{
		//Load the first level
		if(!prepare_next_level(pRenderer))
		{
			current_level_id = -1;
			return false;
		}
	}

	if(start_time == -1)
	{
		start_time = SDL_GetTicks();
	}

	if(!current_level.render(pRenderer))
	{
		current_level.unload();
		current_level_id = -1;
		return false;
	}

	return true;
}

//Start the next level and return it
bool LevelManager::prepare_next_level(SDL_Renderer* pRenderer)
{
	if(current_level_id > -1)
	{
		std::cout << "Unloading previous level" << std::endl;
		current_level.unload();
	}
	
	current_level_id++;
	if(current_level_id == (int)level_ids.size())
	{
		display_happy_ending(pRenderer);
		return false;
	}
	std::string lvl_map = level_data_path + level_ids[current_level_id] + "/" + LEVEL_MAP_FILENAME;
	std::string lvl_bg_path = level_data_path + level_ids[current_level_id] + "/" + LEVEL_BG_FILENAME;
	current_level = Level(lvl_map, lvl_bg_path, level_asset_path);

	if(!current_level.load(pRenderer))
	{
		return false;
	}

	return true;
}

//Display ending stats
void LevelManager::display_stats(SDL_Renderer* pRenderer, int pElapsedTime)
{
	TTF_Font* txt_font = TTF_OpenFont((level_asset_path + "ThinPencilHandwriting.ttf").c_str(), 40);
	if(!txt_font)
	{
		std::cerr << "Cannot load the font" << std::endl;
	}
	else
	{
		SDL_Color txt_color = {0, 0, 0};
		std::string text = "Congratulations !\n\nYou have used " + to_string(level_ids.size()) + " sheets in " + to_string(pElapsedTime) + " seconds."; 
	
		SDL_Surface* txt_image = TTF_RenderText_Blended_Wrapped(txt_font, text.c_str(), txt_color, 400);
		SDL_Texture* txt_texture = SDL_CreateTextureFromSurface(pRenderer, txt_image);
		SDL_FreeSurface(txt_image);

		int lWidth{0};
		int lHeight{0};
		SDL_QueryTexture(txt_texture, nullptr, nullptr, &lWidth, &lHeight);
		
		SDL_Rect text_rect;		
		text_rect.w = lWidth;
		text_rect.h = lHeight;
		text_rect.x = 0;
		text_rect.y = 0;

		SDL_Rect text_pos_rect;
		text_pos_rect.w = lWidth;
		text_pos_rect.h = lHeight;
		text_pos_rect.x = 30;
		text_pos_rect.y = 250;

		SDL_RenderCopy(pRenderer, txt_texture, &text_rect, &text_pos_rect);

		TTF_CloseFont(txt_font);
	}
}

//Display an happy ending message
void LevelManager::display_happy_ending(SDL_Renderer* pRenderer)
{
	//Elapsed time since the first level (s)
	int elapsed_time = (SDL_GetTicks() - start_time)/1000; 
	
	SDL_RenderClear(pRenderer);	
	
	SDL_Surface* end_image = IMG_Load((level_asset_path + "pic_end.png").c_str());
	SDL_Texture* end_texture = SDL_CreateTextureFromSurface(pRenderer, end_image);
	if(end_texture > 0)
	{
		SDL_FreeSurface(end_image);
		SDL_RenderCopy(pRenderer, end_texture, nullptr, nullptr);
		display_stats(pRenderer, elapsed_time);
		
		SDL_RenderPresent(pRenderer);

		//Slow down cycles
		SDL_Delay(3500);
	}
}

//Event dispatcher
void LevelManager::on_event(SDL_Event* pEvent)
{
	if(current_level_id > -1)
	{
		current_level.on_event(pEvent);
	}
}
