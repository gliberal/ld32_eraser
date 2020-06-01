#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "position.h"
#include "player.h"
#include "door.h"
#include "pencil.h"
#include "spike.h"
#include "plantivorus.h"
#include "arachne.h"
#include "ghost.h"
#include "monster.h"
#include "time_bonus.h"

class Level
{
	private:
		int available_time{15};
		int current_time{0};
		int next_time_refresh{0};
		int next_fall_down{0};
		int next_spikes_update{0};
		int next_plants_update{0};
		int next_arachnes_update{0};
		int next_monster_move{0};

		std::string lvl_bg_path;
		std::string lvl_map_path;
		std::string lvl_asset_path;

		SDL_Surface* bg_image;
		SDL_Texture* bg_texture;

		SDL_Color txt_color = {0, 0, 0};
		TTF_Font* txt_font;
		SDL_Texture* timer_texture;
		SDL_Rect timer_rect;
		SDL_Rect timer_pos_rect;

		SDL_Surface* ground_image;	
		SDL_Texture* ground_texture;
		SDL_Rect sprite_rect;
		SDL_Rect bg_rect;

		std::vector<SDL_Rect> lvl_ground;

		Player lvl_player;
		Door lvl_door;

		std::vector<Pencil> lvl_pencils;
		std::vector<Spike> lvl_spikes;
		std::vector<Plantivorus> lvl_plants;
		std::vector<Arachne> lvl_arachnes;
		std::vector<Ghost> lvl_ghosts;
		std::vector<Monster> lvl_monsters;

		std::vector<TimeBonus> lvl_tbonuses;

		Mix_Music* lvl_music;
		Mix_Chunk* sfx_eraser;
		Mix_Chunk* sfx_die_splash;
		Mix_Chunk* sfx_get_time;

		//Add rect to lvl_ground vector
		void add_rect(int pX, int pY);

		//Load the level map
		bool load_map(std::string pMapFilepath);

		//Indicator if level is loaded
		bool is_load = false;

		//Indicator if level is finished
		bool is_finish = false;

	public:
		//Bonus of 5 sec
		static const int TIME_BONUS_VALUE = 5; 

		//Constructor
		Level(){};

		Level(std::string pMapPath, std::string pBgPath, std::string pAssetPath)
		{
			lvl_map_path = pMapPath;
			lvl_asset_path = pAssetPath;
			
			std::ifstream bg_file(pBgPath);		
			if(bg_file.is_open())
			{
				lvl_bg_path = pBgPath;
				bg_file.close();
			}
			else
			{
				lvl_bg_path = pAssetPath + "bg.png";
			}
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

		//Check for collision with timer bonuses
		int check_time_bonus_collision();

		//Check collisions with dangerous things
		bool check_danger_collision();

		//Check for collision between player_rect and door
		bool check_door_collision();

		//Refresh timer
		void refresh_timer(SDL_Renderer* pRenderer);

		//Display no more time picture
		void display_no_more_time(SDL_Renderer* pRenderer);

		//Display failure message
		void display_fail(SDL_Renderer* pRenderer);

		//Render the texture through given renderer
		bool render(SDL_Renderer* pRenderer);

		//Erase everything under the eraser
		bool erase_under(int pMouseX, int pMouseY);

		//event catcher
		void on_event(SDL_Event* pEvent);
};

#endif
