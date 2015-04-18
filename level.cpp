#include "level.h"
#include <iostream>

//Load the level
bool Level::load(SDL_Renderer* pRenderer)
{
	//Initialize the background image	
	bg_image = IMG_Load((lvl_asset_path + "bg.png").c_str());
	
	//Initialize the ground image
	ground_image = IMG_Load((lvl_asset_path + "ground.png").c_str());

	//Initialize the bg sprite
	bg_rect.w = 1024;
	bg_rect.h = 768;
	bg_rect.x = 0;
	bg_rect.y = 0;

	//Initialize the ground sprite
	sprite_rect.w = 64;
	sprite_rect.h = 16;
	sprite_rect.x = 0;
	sprite_rect.y = 0;

	//Load the map
	if(!load_map(lvl_map_path))
	{
		cerr << "Cannot load level map: " + lvl_map_path << endl;
		return false;
	}

	//Load level textures
	if(!init_textures(pRenderer)) 
	{
		cerr << "Cannot initialize level textures" << endl;
		return false;
	}

	//Initialize the music
	lvl_music = Mix_LoadMUS((lvl_asset_path + "sfx/music.ogg").c_str());
	if(!lvl_music)
	{
		cerr << "Cannot load music" << endl;
		return false;
	}

	//Initialize the beep sound
	lvl_beep = Mix_LoadWAV((lvl_asset_path + "sfx/eraser.wav").c_str());
	if(lvl_beep == nullptr)
	{
		cerr << "Cannot load sounds" << endl;  
		return false;
	}
	Mix_VolumeChunk(lvl_beep, 60);

	is_load = true;

	//Play background music
	play_bg_music();

	return true;
}

//Unload level
void Level::unload()
{
	//Destroy textures
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(ground_texture);
	SDL_DestroyTexture(lvl_player.get_texture());
	SDL_DestroyTexture(lvl_door.get_texture());

	//Stop music
	Mix_HaltMusic();
	Mix_FreeMusic(lvl_music);

	//Free sounds
	Mix_FreeChunk(lvl_beep);
	Mix_FreeChunk(lvl_door_open);

	lvl_ground.clear();
	lvl_player.reborn();

	is_load = false;
}

//Add rect to lvl_ground vector
void Level::add_rect(int pX, int pY)
{
	SDL_Rect tmp_rect;
	tmp_rect.w = 64;
	tmp_rect.h = 16;
	tmp_rect.x = pX * 64;
	tmp_rect.y = pY * 64;

	lvl_ground.push_back(tmp_rect);	
}

//Load the level map
bool Level::load_map(string pMapFilepath)
{
	bool has_door = false;
	bool has_player = false;

	string lvl_player_path = lvl_asset_path + "playersheet.png";
	string lvl_door_path = lvl_asset_path + "hole.png";
	
	ifstream lvl_file(pMapFilepath);

	if(lvl_file.is_open())
	{
		string line;
		float line_idx{0};
		float col_idx{0};

		while(getline(lvl_file, line))
		{
			for(auto lChar : line)
			{
				switch(lChar)
				{
					case '*':
						add_rect(col_idx, line_idx);
						break;
					case 'P':
						has_player = true;
						lvl_player = Player(lvl_player_path, col_idx, line_idx);
						break;
					case 'D':
						has_door = true;
						lvl_door = Door(lvl_door_path, col_idx, line_idx);
						break;
				}
				col_idx++;
			}
		
			col_idx = 0;
			line_idx++;
		}
		lvl_file.close();
	
		if(!has_player)
		{
			cerr << "There is no player in this level map (" + pMapFilepath + ") !!" << endl;
			return false;
		}

		if(!has_door)
		{
			cerr << "There is no exit in this level map (" + pMapFilepath + ") !!" << endl;
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

//Initialize textures to be rendered
bool Level::init_textures(SDL_Renderer* pRenderer)
{
	bg_texture = SDL_CreateTextureFromSurface(pRenderer, bg_image);
	if(bg_texture <= 0)
	{
		cerr << "Invalid background texture" << endl;
		return false;
	}
	SDL_FreeSurface(bg_image);
	
	ground_texture = SDL_CreateTextureFromSurface(pRenderer, ground_image);
	if(ground_texture <= 0)
	{
		cerr << "Invalid ground texture" << endl;
		return false;
	}
	SDL_FreeSurface(ground_image);

	if(!lvl_door.init_texture(pRenderer))
	{
		cerr << "Invalid door texture" << endl;
		return false;
	}

	if(!lvl_player.init_texture(pRenderer))
	{
		cerr << "Invalid coco texture" << endl;
		return false;
	}

	return true;
}

//Launch the music
void Level::play_bg_music()
{
	Mix_PlayMusic(lvl_music, -1);
	Mix_VolumeMusic(30);
}

//Check for collision with a given SDL_Rect
bool Level::check_ground_collision()
{
	for(auto lGroundRect : lvl_ground)
	{
		if(SDL_HasIntersection(lvl_player.get_rect(), &lGroundRect))
		{
			return true;			
		}
	}
	return false;
}

bool Level::check_door_collision()
{
	SDL_Rect* lRect = lvl_door.get_rect();
	if(SDL_HasIntersection(lvl_player.get_rect(), lRect))
	{
		return true;
	}
	return false;
}

//Render the texture through given renderer
bool Level::render(SDL_Renderer* pRenderer)
{
	SDL_RenderCopy(pRenderer, bg_texture, &bg_rect, &bg_rect);

	for(auto lGroundRect : lvl_ground)
	{	
		SDL_RenderCopy(pRenderer, ground_texture, &sprite_rect, &lGroundRect);
	}

	lvl_door.render(pRenderer);

	current_time = SDL_GetTicks();
	if(current_time > next_fall_down)
	{
		if(lvl_player.is_jumping())
		{
			lvl_player.walk();
		}
		else
		{
			lvl_player.fall(lvl_ground);
		}
		next_fall_down = current_time + 80;
	}
	
	//Check if the player is in front of the door
	if(check_door_collision())
	{
		is_finish = true;
	}
	
	lvl_player.render(pRenderer);
	return true;
}

//Erase everything under the eraser
void Level::erase_under(int pMouseX, int pMouseY)
{
	//Create a rect from the mouse coordinates
	SDL_Rect mouse_rect;
	mouse_rect.w = 32;
	mouse_rect.h = 32;
	mouse_rect.x = pMouseX;
	mouse_rect.y = pMouseY;
	
	//Just a test with the ground but will only be possible with different monsters or dangers
	int cpt = 0;
	int ground_removal_id = -1;
	for(auto lGroundRect : lvl_ground)
	{
		if(SDL_HasIntersection(&mouse_rect, &lGroundRect))
		{
			ground_removal_id = cpt;			
		}
		cpt++;
	}

	if(ground_removal_id > -1)
	{
		lvl_ground.erase(lvl_ground.begin() + ground_removal_id);	
	}
}

//Handle SDL events 
void Level::on_event(SDL_Event* pEvent)
{
	switch(pEvent->type)
	{
		case SDL_KEYDOWN:
			switch(pEvent->key.keysym.sym)
			{
				case SDLK_LEFT:
					lvl_player.move_x(-1);
					if(check_ground_collision() == true)
					{
						lvl_player.move_x(1);
					}
					break;
				case SDLK_RIGHT:
					lvl_player.move_x(1);
					if(check_ground_collision() == true)
					{
						lvl_player.move_x(-1);
					}
					break;
				case SDLK_UP:
					lvl_player.move_y(-2);
					if(check_ground_collision() == true)
					{
						lvl_player.move_y(1);
					}
					else
					{
						lvl_player.jump();
					}
					break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			erase_under(pEvent->motion.x, pEvent->motion.y);
			break;
	}
}	
