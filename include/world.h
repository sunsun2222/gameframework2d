#ifndef __WORLD_H__
#define __WORLD_H__

#include "gf2d_sprite.h"

typedef struct
{
	Sprite* background;	/*background image for this area*/
	Sprite* tileset;		/*sprite containing the tiles for this area*/
	Uint8* tileMap;		/*the tiles that make up this area*/
	Uint32	tileHeight;		/*how many tiles tall*/
	Uint32	tileWidth;		/*how many tiles wide*/
}Area;

/*
* @brief allocate a new empty area
* @return NULL on error, or a blank area
*/
Area* areaNew();

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