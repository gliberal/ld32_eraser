#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "level.h"
#include <string>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

class LevelManager
{
	private:
		const string INDEX_FILENAME = "lvl_index";
		const string LEVEL_MAP_FILENAME = "lvl_map";
		const string LEVEL_BG_FILENAME = "bg.png";
	
		string level_base_path;
		string level_data_path;
		string level_asset_path;
		string index_path;

		vector<string> level_ids;
		Level current_level;
	
		int current_level_id{-1};
		int start_time{-1};

		//initialize paths
		void init_paths(string pPath);

		//Return the next level
		bool prepare_next_level(SDL_Renderer* pRenderer);

	public:
		//Constructor
		LevelManager()
		{
		}

		//Load the lvl_index file
		bool load_index(SDL_Renderer* pRenderer, string pPath);

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
