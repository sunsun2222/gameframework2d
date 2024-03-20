#ifndef __WORLD_H__
#define __WORLD_H__

#include "sprite.h"

typedef struct
{
	Sprite	*background;	/*background image for this area*/
	Sprite	*tileset;		/*sprite containing the tiles for this area*/
	Uint8	*tileMap;		/*the tiles that make up this area*/
	Uint32	tileHeight;		/*how many tiles tall*/
	Uint32	tileWidth;		/*how many tiles wide*/
}Area;

#endif