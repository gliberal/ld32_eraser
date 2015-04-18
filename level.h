#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "position.h"
#include "player.h"
#include "door.h"

using namespace std;

class Level
{
	private:
		int current_time{0};
		int next_fall_down{0};
		
		string lvl_map_path;
		string lvl_asset_path;

		SDL_Surface* bg_image;
		SDL_Texture* bg_texture;

		SDL_Surface* ground_image;	
		SDL_Texture* ground_texture;
		SDL_Rect sprite_rect;
		SDL_Rect bg_rect;

		vector<SDL_Rect> lvl_ground;

		Player lvl_player;
		Door lvl_door;

		Mix_Music* lvl_music;
		Mix_Chunk* lvl_beep;
		Mix_Chunk* lvl_door_open;

		//Add rect to lvl_ground vector
		void add_rect(int pX, int pY);

		//Load the level map
		bool load_map(string pMapFilepath);

		//Indicator if level is loaded
		bool is_load = false;

		//Indicator if level is finished
		bool is_finish = false;

	public:
		//Constructor
		Level(string pMapPath, string pAssetPath)
		{
			lvl_map_path = pMapPath;
			lvl_asset_path = pAssetPath;
		}

		//Load the level
		bool load(SDL_Renderer* pRenderer);

		//Unload the level (cleanup memory)
		void unload();

		//Unifnish the level
		void unfinish(){is_finish = false;}

		//Getter for is_finished indicator
		bool is_finished(){return is_finish;}

		//Getter for is_loaded indicator
		bool is_loaded(){return is_load;}

		//Initialize the texture to be rendered
		bool init_textures(SDL_Renderer* pRenderer);

		//Launch the music
		void play_bg_music();

		//Check for collision with a given SDL_Rect
		bool check_ground_collision();

		//Check for collision between player_rect and door
		bool check_door_collision();

		//Render the texture through given renderer
		bool render(SDL_Renderer* pRenderer);

		//event catcher
		void on_event(SDL_Event* pEvent);
};

#endif