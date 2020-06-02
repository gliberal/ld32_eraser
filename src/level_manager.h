#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "level.h"
#include <string>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

/**
 * \class LevelManager
 * \brief Game object that handles levels 
 **/
class LevelManager
{
	private:
		const std::string INDEX_FILENAME = "lvl_index";
		const std::string LEVEL_MAP_FILENAME = "lvl_map";
		const std::string LEVEL_BG_FILENAME = "bg.png";
	
		std::string level_base_path;
		std::string level_data_path;
		std::string level_asset_path;
		std::string index_path;

		std::vector<std::string> level_ids;
		Level current_level;
	
		int current_level_id{-1};
		int start_time{-1};

		//initialize paths
		void init_paths(std::string pPath);

		//Return the next level
		bool prepare_next_level(SDL_Renderer* pRenderer);

	public:
		//Constructor
		LevelManager()
		{
		}

		//Load the lvl_index file
		bool load_index(SDL_Renderer* pRenderer, std::string pPath);

		//Display the current level
		bool display(SDL_Renderer* pRenderer);

		//Display ending stats
		void display_stats(SDL_Renderer* pRenderer, int pElapsedTime);

		//Display an happy ending message
		void display_happy_ending(SDL_Renderer* pRenderer);

		//Event dispatcher
		void on_event(SDL_Event* pEvent);	
};

#endif
