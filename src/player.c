#include "simple_logger.h"
#include "gfc_input.h"
#include "player.h"

void player_input(Entity* self)
{
	Vector2D dir = { 0 };

	if (!self)
	{
		slog("Failed to spawn player entity.");
		return NULL;
	}

	gfc_input_update();

	if (gfc_input_command_down("right"))	dir.x = 1;		//right
	if (gfc_input_command_down("left"))		dir.x = -1;		//left
	if (gfc_input_command_down("down"))		dir.y = 1;		//down
	if (gfc_input_command_down("up"))		dir.y = -1;		//up

	vector2d_normalize(&dir);
	vector2d_scale(self->velocity, dir, 3);
}

void player_think(Entity* self)
{
	//Vector2D dir = {0};

	if (!self)
	{
		return;
	}

	player_input(self);

	/**
	Uint32 mx, my = 0;
	SDL_GetMouseState(&mx,&my);

	if (self->position.x > mx)	dir.x = -1;
	if (self->position.x < mx)	dir.x = 1;
	if (self->position.y > my)	dir.y = -1;
	if (self->position.y < my)	dir.y = 1;

	vector2d_normalize(&dir);
	vector2d_scale(self->velocity,dir,3);
	*/
}
void player_update(Entity* self)
{
	if (!self)return;

	self->frame += 0.1;

	if (self->frame >= 16)
	{
		self->frame = 0;
	}

	vector2d_add(self->position, self->position, self->velocity);
}
void player_free(Entity* self)
{
	if (!self)return;
}

Entity* player_new()
{
	Entity* self;
	self = entity_new();

	if (!self)
	{
		slog("Failed to spawn a player entity.");
		return NULL;
	}

	//initializes the input system to the config file
	gfc_input_init("gfc/sample_config/input.cfg");

	//player stats
	self->health = 12;

	self->sprite = gf2d_sprite_load_all(
		"images/ed210.png",
		128,
		128,
		16,
		0);
	self->frame = 0;
	self->position = vector2d(0, 0);

	self->think = player_think;
	self->update = player_update;
	self->free = player_free;

	return self;
}