#ifndef __WORLD_H__
#define __WORLD_H__

#include "gf2d_sprite.h"

//Think of an area as a screen, when we move to the edge, we want to move over by one screen
typedef struct
{
	Sprite* background;		/*background image for this area*/
	Sprite* tileSet;		/*sprite containing the tiles for this area*/
	Sprite* tileLayer;		/*prerendered tile layer*/
	Uint8*	tileMap;		/*the tiles that make up this area*/
	Uint32	tileHeight;		/*how many tiles tall*/
	Uint32	tileWidth;		/*how many tiles wide*/
}Area;
/*
* @brief test function to see if world is working
*/
Area* area_test_new();

/*
* @brief allocate a new empty area
* @return NULL on error, or a blank area
*/
Area* area_new(Uint32 width, Uint32 height);

/*
* @brief free a previously allocated area
* @param area the area to free
*/
void area_free(Area* area);

/*
* @brief draw the area
* @param area the area to draw
*/
void area_draw(Area* area);

#endif