#include "simple_logger.h"
#include "gf2d_sprite.h"

#include "world.h"

void area_tile_layer_build(Area* area)
{
	int i, j, index;
	Vector2D position;
	Uint32 frame;

	if (!area) return;

	if (area->tileLayer)
	{
		gf2d_sprite_free(area->tileLayer);
	}

	area->tileLayer = gf2d_sprite_new();

	//left off at 19:27 on p2 worldbuilding

	for (j = 0; j < area->tileHeight; j++)
	{
		for (i = 0; i < area->tileWidth; i++)
		{
			index = i + (j * area->tileWidth);

			if (area->tileMap[index] == 0) continue;

			position.x = i * area->tileSet->frame_w;
			position.y = j * area->tileSet->frame_h;
			frame = area->tileMap[index] - 1;

			gf2d_sprite_draw_to_surface(
				area->tileSet,
				position,
				NULL,
				NULL,
				frame,
				area->tileLayer);
		}
	}
}

Area *area_test_new()
{
	int i;
	int width = 75, height = 45;
	Area *area;

	area = area_new(width,height);

	if (!area) return NULL;

	area->background = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
	area->tileSet = gf2d_sprite_load_all(
		"images/backgrounds/tempTileset.png",
		16,
		16,
		1,
		1);

	for (i = 0; i < width; i++)
	{
		area->tileMap[i] = 1;
		area->tileMap[i + ((height-1) * width)] = 1;
	}

	for (i = 0; i < height; i++)
	{
		area->tileMap[i*width] = 1;
		area->tileMap[i*width + (width - 1)] = 1;
	}

	return area;
}

Area *area_new(Uint32 width, Uint32 height)
{
	Area *area;

	if ((!width) || (!height))
	{
		slog("Cannot create an area with no width and height");
		return NULL;
	}

	area = gfc_allocate_array(sizeof(Area), 1);
	if (!area)
	{
		slog("failed to allocate a new area");
		return NULL;
	}

	//all defaults/boilerplate code would go here
	area->tileSet = gfc_allocate_array(sizeof(Uint8), height * width);
	area->tileHeight = height;
	area->tileWidth = width;

	return area;
}

void area_free(Area* area)
{
	if (!area) return;

	gf2d_sprite_free(area->background);
	gf2d_sprite_free(area->tileSet);		
	free(area->tileMap);
	free(area);
}

void area_draw(Area* area)
{
	int i, j;
	int index;
	int frame;
	Vector2D position;

	if (!area) return;
	if (!area->tileSet) return;	//can't draw with no tiles

	gf2d_sprite_draw_image(area->background, vector2d(0, 0));

	for (j = 0; j < area->tileHeight; j++)
	{
		for (i = 0; i < area->tileWidth; i++)
		{
			index = i + (j * area->tileWidth);
			position.x = i * area->tileSet->frame_w;
			position.y = j * area->tileSet->frame_h;

			if (area->tileMap[index] == 0) continue;

			frame = area->tileMap[index] - 1;
			gf2d_sprite_draw(
				area->tileSet,
				position,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				frame);
		}
	}
}