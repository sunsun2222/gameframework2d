#include "simple_logger.h"


#include "player.h"

void player_think(Entity *self)
{
	if (!self)return;
}
void player_update(Entity* self)
{
	if (!self)return;
}
void player_free(Entity* self)
{
	if (!self)return;
}

Entity* player_new()
{
	Entity *self;
	self = entity_new();
	if (!self)
	{
		slog("Failed to spawn a player entity.");
		return NULL;
	}

	self->sprite = gf2d_sprite_load_all(
		"images/ed210.png",
		128,
		128,
		16,
		0 );	
	self->frame = 0;		
	self->position = vector2D(0,0);

	self->think = player_think;
	self->update = player_update;
	self->free = player_free;

	return self;
}