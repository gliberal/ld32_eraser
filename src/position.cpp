#include "position.h"

/**
 * get_x
 * \brief get x coordinate
 * \return int : x position
 **/
int Position::get_x()
{
	return coord_x;
}

/**
 * get_y
 * \brief get y coordinate
 * \return int : y position
 **/
int Position::get_y()
{
	return coord_y;
}

/**
 * set_x
 * \brief set x coordinate
 * \return void
 **/
void Position::set_x(int pX=0)
{
	if(pX >= MIN_X && pX <= MAX_X)
	{	
		coord_x = pX;
	}
}

/**
 * set_y
 * \brief set y coordinate
 * \return void
 **/
void Position::set_y(int pY=0)
{
	if(pY >= MIN_Y && pY <= MAX_Y)
	{
		coord_y = pY;
	}
}

