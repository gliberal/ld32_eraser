#include "player.h"

//Initialize texture
bool Player::init_texture(SDL_Renderer* pRenderer)
{
	SDL_Surface* player_image = IMG_Load(player_image_path.c_str());
	player_texture = SDL_CreateTextureFromSurface(pRenderer, player_image);
	if(player_texture <= 0)
	{	
		return false;
	}
	SDL_FreeSurface(player_image);
	return true;
}

//Render the texture through given renderer
void Player::render(SDL_Renderer* pRenderer)
{
	if(player_direction == LEFT)
	{
		SDL_RenderCopy(pRenderer, player_texture, &sprite_rect, &player_rect);
	}
	else
	{
		SDL_RenderCopyEx(pRenderer, player_texture, &sprite_rect, &player_rect, 0, nullptr, SDL_FLIP_HORIZONTAL);
	}
}

//Set player position to the given one
void Player::set_pos(Position pPosition)
{
	pos = pPosition;
	player_rect.x = pPosition.get_x() * STEP_X;
	player_rect.y = pPosition.get_y() * STEP_Y;
}

//Move on X axis with a default step of 1
void Player::move_x(int step=1)
{
	pos.set_x(pos.get_x()+step);

	//Update player direction
	if(step < 0)
	{
		player_direction = LEFT;
	}
	else
	{
		player_direction = RIGHT;
	}

	//Update player sprite
	if(sprite_rect.x == 32*POS_0)
	{
		sprite_rect.x = 32*POS_1;
	}
	else
	{
		sprite_rect.x = 32*POS_0;
	}

	//Update player_rect with updated X
	player_rect.x = pos.get_x() * STEP_X;
}

//PLayer fall
bool Player::fall(std::vector<SDL_Rect> ground)
{
	//Update the rect
	pos.set_y(pos.get_y()+1);
	player_rect.y = pos.get_y() * STEP_Y;
			
	if(has_intersection(ground))
	{
		pos.set_y(pos.get_y()-1);
		player_rect.y = pos.get_y() * STEP_Y;
		return false;
	}
	return true;
}

bool Player::has_intersection(std::vector<SDL_Rect> sdl_rect_vector)
{
	for(auto lRect : sdl_rect_vector)
	{
		if(SDL_HasIntersection(&player_rect, &lRect))
		{
			return true;			
		}
	}
	return false;
}

//Move on Y axis with a default step of 1
void Player::move_y(int step=1)
{
	pos.set_y(pos.get_y()+step);

	//Update player_rect with updated Y
	player_rect.y = pos.get_y() * STEP_Y;
}


