#include "Environment.h"

Environment::Environment(int worldWidth, int worldHeight, Camera* c)
: WORLD_WIDTH(worldWidth), WORLD_HEIGHT(worldHeight)
{
	physics = new Physics(WORLD_HEIGHT, WORLD_WIDTH);
	camera = c;
}

void Environment::update()
{
	for (GameObject* o : environment)
		if (camera->canSee(o))
		{
			o->body.screenX = o->body.xPos - camera->body.xPos;
			o->body.screenY = o->body.yPos - camera->body.yPos;
			o->render(); // might not belong here
			if (o->body.physical) 
				physics->update(o);
		}
}

void Environment::addObject(GameObject* o)
{
	environment.push_back(o);
}
