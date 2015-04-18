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
			load_level(line);
		}	
		index_file.close();	
	}
	else
	{
		return false;
	}

	if(!levels[current_level].load(pRenderer))
	{
		std::cerr << "Cannot load bad level" << std::endl;
		return false;
	}

	return true;	
}

//Load the level description file and creates a Level
void LevelManager::load_level(std::string pId)
{
	std::string lvl_map = level_data_path + pId + "/" + LEVEL_MAP_FILENAME;
	levels.push_back(Level(lvl_map, level_asset_path));
}

//Display the current level
bool LevelManager::display(SDL_Renderer* pRenderer)
{
	if(!levels[current_level].is_loaded())
	{
		levels[current_level].load(pRenderer);
	}
	else
	{
		if(levels[current_level].is_finished())
		{
			if(!prepare_next_level(pRenderer))
			{
				reset_progress();
				return false;
			}
		}
	}

	if(!levels[current_level].render(pRenderer))
	{
		reset_progress();
		return false;
	}

	return true;
}

//Reset played levels
void LevelManager::reset_progress()
{
	for(int l=0; l<=current_level; l++)
	{
		levels[l].unfinish();
		levels[l].unload();
	}

	current_level = 0;
}

//Start the next level and return it
bool LevelManager::prepare_next_level(SDL_Renderer* pRenderer)
{
	int lvl_ind{0};
	for(auto &lvl : levels)
	{
		if(!lvl.is_finished())
		{
			if(!lvl.load(pRenderer))
			{
				return false;
			}
			current_level = lvl_ind;

			return true;
		}
		lvl_ind++;
	}
	return false;
}

//Event dispatcher
void LevelManager::on_event(SDL_Event* pEvent)
{
	levels[current_level].on_event(pEvent);
}
