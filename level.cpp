#include "level.h"
#include <iostream>

//Load the level
bool Level::load(SDL_Renderer* pRenderer)
{
	//Initialize the background image	
	bg_image = IMG_Load((lvl_asset_path + "bg.png").c_str());

	txt_font = TTF_OpenFont((lvl_asset_path + "ThinPencilHandwriting.ttf").c_str(), 40);
	if(!txt_font)
	{
		cerr << "Cannot load the font" << endl;
	}

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
	sfx_eraser = Mix_LoadWAV((lvl_asset_path + "sfx/eraser.wav").c_str());
	if(sfx_eraser == nullptr)
	{
		cerr << "Cannot load sounds" << endl;  
		return false;
	}
	Mix_VolumeChunk(sfx_eraser, 60);

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

	for(auto &lvl_pencil : lvl_pencils)
	{
		SDL_DestroyTexture(lvl_pencil.get_texture());
	}

	for(auto &lvl_spike : lvl_spikes)
	{
		SDL_DestroyTexture(lvl_spike.get_texture());
	}

	for(auto &lvl_plant : lvl_plants)
	{
		SDL_DestroyTexture(lvl_plant.get_texture());
	}

	for(auto &lvl_arachne : lvl_arachnes)
	{
		SDL_DestroyTexture(lvl_arachne.get_texture());
	}

	for(auto &lvl_ghost : lvl_ghosts)
	{
		SDL_DestroyTexture(lvl_ghost.get_texture());
	}

	for(auto &lvl_monster : lvl_monsters)
	{
		lvl_monster.dispose();
	}

	//Stop music
	Mix_HaltMusic();
	Mix_FreeMusic(lvl_music);

	//Free sounds
	Mix_FreeChunk(sfx_eraser);

	TTF_CloseFont(txt_font);
	SDL_DestroyTexture(timer_texture);

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
	string lvl_pencil_path = lvl_asset_path + "pencil.png";
	string lvl_spike_path = lvl_asset_path + "spike.png";
	string lvl_plant_path = lvl_asset_path + "plant.png";
	string lvl_arachne_path = lvl_asset_path + "arachne.png";
	string lvl_ghost_path = lvl_asset_path + "ghost.png";
	string lvl_monster_path = lvl_asset_path + "monster.png";

	ifstream lvl_file(pMapFilepath);

	if(lvl_file.is_open())
	{
		string line;
		float line_idx{0};
		float col_idx{0};

		int monster_x1{0};
		int monster_x2{0};

		while(getline(lvl_file, line))
		{
			for(auto lChar : line)
			{
				switch(lChar)
				{
					case '*': //Ground
						add_rect(col_idx, line_idx);
						break;
					case 'P': //Player
						has_player = true;
						lvl_player = Player(lvl_player_path, col_idx, line_idx);
						break;
					case 'D': //Door
						has_door = true;
						lvl_door = Door(lvl_door_path, col_idx, line_idx);
						break;
					case 'A': //Arachnee
						{
							Arachne lvl_arachne = Arachne(lvl_arachne_path, col_idx, line_idx);
							lvl_arachnes.push_back(lvl_arachne);
						}
						break;
					case '[': //Monster start
						monster_x1 = col_idx;
						break;
					case ']': //Monster end
						monster_x2 = col_idx;
						break;
					case 'S': //Spike
						{
							Spike lvl_spike = Spike(lvl_spike_path, col_idx, line_idx);
							lvl_spikes.push_back(lvl_spike);
						}
						break;
					case 'F': //Fleur
						{
							Plantivorus lvl_plant = Plantivorus(lvl_plant_path, col_idx, line_idx);
							lvl_plants.push_back(lvl_plant);

						}
						break;
					case 'G': //Ghost
						{
							Ghost lvl_ghost = Ghost(lvl_ghost_path, col_idx, line_idx);
							lvl_ghosts.push_back(lvl_ghost);
						}
						break;
					case 'C': //Crayon
						{
							Pencil lvl_pencil = Pencil(lvl_pencil_path, col_idx, line_idx);
							lvl_pencils.push_back(lvl_pencil);
						}
						break;
				}
				col_idx++;
			}
		
			if(monster_x1 != monster_x2)
			{
				Monster lvl_monster = Monster(lvl_monster_path, monster_x1, monster_x2, line_idx);
			       	lvl_monsters.push_back(lvl_monster);	
			}

			monster_x1 = 0;
			monster_x2 = 0;
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

	for(auto &lvl_pencil : lvl_pencils)
	{
		if(!lvl_pencil.init_texture(pRenderer))
		{
			cerr << "Invalid pencil texture" << endl;
			return false;
		}
	}

	for(auto &lvl_spike : lvl_spikes)
	{
		if(!lvl_spike.init_texture(pRenderer))
		{
			cerr << "Invalid spike texture" << endl;
			return false;
		}
	}

	for(auto &lvl_plant : lvl_plants)
	{
		if(!lvl_plant.init_texture(pRenderer))
		{
			cerr << "Invalid plantivorus texture" << endl;
			return false;
		}
	}

	for(auto &lvl_arachne : lvl_arachnes)
	{
		if(!lvl_arachne.init_texture(pRenderer))
		{
			cerr << "Invalid arachne texture" << endl;
			return false;
		}
	}

	for(auto &lvl_ghost : lvl_ghosts)
	{
		if(!lvl_ghost.init_texture(pRenderer))
		{
			cerr << "Invalid ghost texture" << endl;
			return false;
		}
	}

	for(auto &lvl_monster : lvl_monsters)
	{
		if(!lvl_monster.init_texture(pRenderer))
		{
			cerr << "Invalid monster texture" << endl;
			return false;
		}
	}

	if(!lvl_door.init_texture(pRenderer))
	{
		cerr << "Invalid door texture" << endl;
		return false;
	}

	if(!lvl_player.init_texture(pRenderer))
	{
		cerr << "Invalid player texture" << endl;
		return false;
	}

	return true;
}

//Launch the music
void Level::play_bg_music()
{
	Mix_PlayMusic(lvl_music, -1);
	Mix_VolumeMusic(20);
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

//Check collisions with dangerous things
bool Level::check_danger_collision()
{
	//Check pencils
	for(auto &lvl_spike : lvl_spikes)
	{
		if(SDL_HasIntersection(lvl_player.get_rect(), lvl_spike.get_rect()))
		{
			return true;			
		}
	}

	//Check with plantivorus
	for(auto &lvl_plant : lvl_plants)
	{
		if(SDL_HasIntersection(lvl_player.get_rect(), lvl_plant.get_rect()))
		{
			return true;			
		}
	}

	//Check with ghost
	for(auto &lvl_ghost : lvl_ghosts)
	{
		if(SDL_HasIntersection(lvl_player.get_rect(), lvl_ghost.get_rect()))
		{
			return true;			
		}
	}

	//Check with arachne
	for(auto &lvl_arachne : lvl_arachnes)
	{
		if(SDL_HasIntersection(lvl_player.get_rect(), lvl_arachne.get_rect()))
		{
			return true;			
		}
	}

	//Check with monster
	for(auto &lvl_monster : lvl_monsters)
	{
		if(SDL_HasIntersection(lvl_player.get_rect(), lvl_monster.get_rect()))
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

	for(auto &lvl_pencil : lvl_pencils)
	{
		lvl_pencil.render(pRenderer);
	}

	for(auto &lvl_spike : lvl_spikes)
	{
		lvl_spike.render(pRenderer);
	}

	for(auto &lvl_plant : lvl_plants)
	{
		lvl_plant.render(pRenderer);
	}

	for(auto &lvl_arachne : lvl_arachnes)
	{
		lvl_arachne.render(pRenderer);
	}

	for(auto &lvl_ghost : lvl_ghosts)
	{
		lvl_ghost.render(pRenderer);
	}

	for(auto &lvl_monster : lvl_monsters)
	{
		lvl_monster.render(pRenderer);
	}

	lvl_door.render(pRenderer);

	current_time = SDL_GetTicks();

	if(start_time == -1)
	{
		start_time = current_time; 
	}

	if(current_time > next_time_refresh)
	{
		//(current_time - start_time) / 1000;
		string current_txt = to_string((current_time - start_time) / 1000);
		SDL_Surface* txt_image = TTF_RenderText_Blended_Wrapped(txt_font, current_txt.c_str(), txt_color, bg_rect.w - 5);
		timer_texture = SDL_CreateTextureFromSurface(pRenderer, txt_image);
		if(timer_texture <= 0)
		{
			return false;
		}
		SDL_FreeSurface(txt_image);

		int lWidth{0};
		int lHeight{0};
		SDL_QueryTexture(timer_texture, nullptr, nullptr, &lWidth, &lHeight);
		
		timer_rect.w = lWidth;
		timer_rect.h = lHeight;
		timer_rect.x = 0;
		timer_rect.y = 0;

		timer_pos_rect.w = timer_rect.w;
		timer_pos_rect.h = timer_rect.h;
		timer_pos_rect.x = 5*bg_rect.w/6 + 80;
		timer_pos_rect.y = 5;

		next_time_refresh = current_time + 1000;
	}
	SDL_RenderCopy(pRenderer, timer_texture, &timer_rect, &timer_pos_rect);

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

	if(current_time > next_monster_move)
	{
		for(auto &lvl_monster : lvl_monsters)
		{
			lvl_monster.move();
		}
		next_monster_move = current_time + 180;
	}

	if(current_time > next_spikes_update)
	{
		for(auto &lvl_spike : lvl_spikes)
		{
			lvl_spike.switch_spikes();
		}
	
		next_spikes_update = current_time + 210;
	}

	if(current_time > next_plants_update)
	{
		for(auto &lvl_plant : lvl_plants)
		{
			lvl_plant.switch_position();
		}
	
		next_plants_update = current_time + 1000;
	}

	if(current_time > next_arachnes_update)
	{
		for(auto &lvl_arachne : lvl_arachnes)
		{
			lvl_arachne.switch_position();
		}
	
		for(auto &lvl_ghost : lvl_ghosts)
		{
			lvl_ghost.switch_position();
		}

		next_arachnes_update = current_time + 600;
	}
	
	//Check if the player collides with dangerous things
	if(check_danger_collision())
	{
		return false;
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
bool Level::erase_under(int pMouseX, int pMouseY)
{
	//Create a rect from the mouse coordinates
	SDL_Rect mouse_rect;
	mouse_rect.w = 32;
	mouse_rect.h = 32;
	mouse_rect.x = pMouseX;
	mouse_rect.y = pMouseY;
	
	//Test the ground
	int cpt = 0;
	int removal_id = -1;
	for(auto lGroundRect : lvl_ground)
	{
		if(SDL_HasIntersection(&mouse_rect, &lGroundRect))
		{
			removal_id = cpt;			
		}
		cpt++;
	}

	if(removal_id > -1)
	{
		lvl_ground.erase(lvl_ground.begin() + removal_id);
		return true;	
	}

	//Test the spikes
	cpt = 0;
	for(auto &lvl_spike : lvl_spikes)
	{
		if(SDL_HasIntersection(&mouse_rect, lvl_spike.get_rect()))
		{
			removal_id = cpt;			
		}
		cpt++;
	}

	if(removal_id > -1)
	{
		lvl_spikes.erase(lvl_spikes.begin() + removal_id);
		return true;
	}

	//Test the plantivorus
	cpt = 0;
	for(auto &lvl_plant : lvl_plants)
	{
		if(SDL_HasIntersection(&mouse_rect, lvl_plant.get_rect()))
		{
			removal_id = cpt;			
		}
		cpt++;
	}

	if(removal_id > -1)
	{
		lvl_plants.erase(lvl_plants.begin() + removal_id);
		return true;
	}

	//Test arachnes
	cpt = 0;
	for(auto &lvl_arachne : lvl_arachnes)
	{
		if(SDL_HasIntersection(&mouse_rect, lvl_arachne.get_rect()))
		{
			removal_id = cpt;			
		}
		cpt++;
	}

	if(removal_id > -1)
	{
		lvl_arachnes.erase(lvl_arachnes.begin() + removal_id);
		return true;
	}

	//Test monsters
	cpt = 0;
	for(auto &lvl_monster : lvl_monsters)
	{
		if(SDL_HasIntersection(&mouse_rect, lvl_monster.get_rect()))
		{
			removal_id = cpt;			
		}
		cpt++;
	}

	if(removal_id > -1)
	{
		lvl_monsters.erase(lvl_monsters.begin() + removal_id);
		return true;
	}

	return false;
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
			if(erase_under(pEvent->motion.x, pEvent->motion.y))
			{
				//Play sound only if something erasable is under the eraser
				Mix_PlayChannel(-1, sfx_eraser, 0); 
			}
			break;
	}
}	
