#include "simple_logger.h"

#include "entity.h"

typedef struct
{
	Entity* entity_list;
	Uint32	entity_max;
}EntityManager;

static EntityManager entity_manager = { 0 }; /**initialize a LOCAL entity manager*/

void entity_system_close()
{
	entity_clear_all(NULL);

	if (entity_manager.entity_list)
	{
		free(entity_manager.entity_list);
	}

	memset(&entity_manager, 0, sizeof(EntityManager));
}

void entity_system_init(Uint32 max)
{
	if (entity_manager.entity_list)
	{
		slog("Cannot have two instances of an entity manager, one is already active");
		return;
	}

	if (!max)
	{
		slog("Cannot allocate 0 entities!");
		return;
	}

	entity_manager.entity_list = gfc_allocate_array(sizeof(Entity), max);

	if (!entity_manager.entity_list)
	{
		slog("Failed to allocate global entity list.");
		return;
	}

	entity_manager.entity_max = max;
	atexit(entity_system_close);
}

void entity_clear_all(Entity* ignore)
{
	for (int i = 0;i < entity_manager.entity_max;i++)
	{
		if (&entity_manager.entity_list[i] == ignore)
		{
			continue;
		}

		if (!entity_manager.entity_list[i]._inuse)
		{
			continue; //skip this iteration of the loop
		}

		entity_free(&entity_manager.entity_list[i]);
	}
}

Entity* entity_new()
{
	for (int i = 0;i < entity_manager.entity_max;i++)
	{
		if (entity_manager.entity_list[i]._inuse)
		{
			continue;
		}

		memset(&entity_manager.entity_list[i], 0, sizeof(Entity));
		entity_manager.entity_list[i]._inuse = 1;
		//setting the default color
		//setting the default scale
		return &entity_manager.entity_list[i];
	}
	slog("No more available entities.");
	return NULL;
}

void entity_free(Entity* self)
{
	if (!self) //can't do anything if we have nothing
	{
		return;
	}

	gf2d_sprite_free(self->sprite);

	//anything else we allocate for our entity would get cleaned up here
	if (self->free)
	{
		self->free(self->data);
	}
}

void entity_think(Entity* self)
{
	if (!self)
	{
		return;
	}
	//any biolerplate think stuff here
	if (self->think)
	{
		self->think(self);
	}
}

void entity_system_think()
{
	for (int i = 0;i < entity_manager.entity_max;i++)
	{
		if (!entity_manager.entity_list[i]._inuse)
		{
			continue;
		}

		entity_think(&entity_manager.entity_list[i]);
	}
}

void entity_update(Entity* self)
{
	if (!self)
	{
		return; //any biolerplate think stuff here
	}
	if (self->update)
	{
		self->update(self);
	}
}

void entity_system_update()
{
	for (int i = 0;i < entity_manager.entity_max;i++)
	{
		if (!entity_manager.entity_list[i]._inuse)
		{
			continue;
		}

		entity_update(&entity_manager.entity_list[i]);
	}
}

void entity_draw(Entity* self)
{
	if (!self)
	{
		return; //any biolerplate think stuff here
	}
	if (self->sprite)
	{
		gf2d_sprite_render(
			self->sprite,
			self->position,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			(Uint32)self->frame
		);
	}
}

void entity_system_draw()
{
	for (int i = 0;i < entity_manager.entity_max;i++)
	{
		if (!entity_manager.entity_list[i]._inuse)
		{
			continue;
		}

		entity_draw(&entity_manager.entity_list[i]);
	}
}