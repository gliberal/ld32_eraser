#include "level_manager.h"
#include <fstream>

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

//Display an happy ending message
void LevelManager::display_happy_ending(SDL_Renderer* pRenderer)
{
	//TODO display game time (add global timer) + qty of paper sheets
	SDL_RenderClear(pRenderer);	
	SDL_Surface* end_image = IMG_Load((level_asset_path + "pic_end.png").c_str());
	SDL_Texture* end_texture = SDL_CreateTextureFromSurface(pRenderer, end_image);
	if(end_texture > 0)
	{
		SDL_FreeSurface(end_image);
		SDL_RenderCopy(pRenderer, end_texture, nullptr, nullptr);
		SDL_RenderPresent(pRenderer);

		//Slow down cycles
		SDL_Delay(200);
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
