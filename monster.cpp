#include "monster.h"

//Initialize texture
bool Monster::init_texture(SDL_Renderer* pRenderer)
{
	monster_texture = SDL_CreateTextureFromSurface(pRenderer, monster_image);
	if(monster_texture <= 0)
	{
		return false;
	}
	SDL_FreeSurface(monster_image);
	return true;
}

//Render the texture through given renderer
void Monster::render(SDL_Renderer* pRenderer)
{
	if(direction == RIGHT)
	{
		SDL_RenderCopyEx(pRenderer, monster_texture, &sprite_rect, &monster_rect, 0, nullptr, SDL_FLIP_HORIZONTAL);
	}	
	else
	{
		SDL_RenderCopy(pRenderer, monster_texture, &sprite_rect, &monster_rect);
	}
}

//Set player position to the given one
void Monster::set_pos(Position pPosition)
{
	pos = pPosition;

	monster_rect.x = pPosition.get_x() * STEP_X;
	monster_rect.y = pPosition.get_y() * STEP_Y;
}

//Move the monster and refresh its surface
void Monster::move()
{
	int x_val{0};
	int y_val{pos.get_y()};
	
	if(direction == RIGHT)
	{
		if(pos.get_x() < x_max)
		{
			x_val = pos.get_x() + 1;
			set_pos(Position(x_val, y_val));
		}
		else
		{
			direction = LEFT;
		}
	}
	else
	{
		if(pos.get_x() > x_min)
		{
			x_val = pos.get_x() - 1;
			set_pos(Position(x_val, y_val));
		}
		else
		{
			direction = RIGHT;
		}
	}
	
	switch(sprite_rect.x)
	{
		case POS_0:
			sprite_rect.x = POS_1;
			break;
		case POS_1:
			sprite_rect.x = POS_2;
			break;
		default:
			sprite_rect.x = POS_0;
			break;
	}
}

//Destroy
void Monster::dispose()
{
	SDL_DestroyTexture(monster_texture);	
}
