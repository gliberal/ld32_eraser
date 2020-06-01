#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include <string>
#include <vector>
#include <SDL2/SDL.h>

#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#endif

class Player
{
	Position pos;
	std::string player_image_path;
	SDL_Texture* player_texture;
	SDL_Rect sprite_rect;
	SDL_Rect player_rect;
	int player_direction;
	bool is_jump = false;	
	bool is_dead = false;

	public:
		//Constant initialization
		static const int POS_0 = 2;
		static const int POS_1 = 1;
		static const int POS_DEAD = 0;

		static const int STEP_X = 64;
		static const int STEP_Y = 64;
		
		static const int LEFT = 0;
		static const int RIGHT = 1;

		//Constructors
		Player(std::string pSpritePath="", int pX=0, int pY=0)
		{
			pos = Position(pX, pY);

			player_image_path = pSpritePath;
			player_direction = RIGHT;

			sprite_rect.w = 32;
			sprite_rect.h = 64;
			sprite_rect.x = 32 * POS_0;
			sprite_rect.y = 0;

			player_rect.w = sprite_rect.w;
			player_rect.h = sprite_rect.h;
			player_rect.x = pX * STEP_X;
			player_rect.y = pY * STEP_Y;
		}

		//Getter for player_rect (will be used for collsion)
		SDL_Rect* get_rect(){ return &player_rect; }

		//Initialize texture
		bool init_texture(SDL_Renderer* pRenderer);

		//Getter for player texture
		SDL_Texture* get_texture(){return player_texture;}

		void jump(){is_jump=true;}
	
		void walk(){is_jump=false;}

		bool is_jumping(){return is_jump;}

		//Set the player position to the given position
		void set_pos(Position pPosition);

		//Kill the player
		void kill(){is_dead = true;}

		//Reborn the player
		void reborn(){is_dead = false;}

		//Check if player is alive
		bool is_alive(){return !is_dead;}

		//Render the texture through given renderer
		void render(SDL_Renderer* pRenderer);

		//Move on X axis 
		void move_x(int step);

		//Move on Y axis
		void move_y(int step);

		//Let the user falls if he's not on the groud
		bool fall(std::vector<SDL_Rect> ground);

		//Check if player has instersection with given SDL_Rects
		bool has_intersection(std::vector<SDL_Rect> sdl_rect_vector);
};
#endif
