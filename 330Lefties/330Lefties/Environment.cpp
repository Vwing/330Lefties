#include "Environment.h"

Environment::Environment()
{
	camera = new Camera();
}

void Environment::update()
{
	for (GameObject* o : environment)
		if (camera->canSee(o))
		{
			o->body.screenX = o->body.xPos - camera->body.xPos;
			o->body.screenY = o->body.yPos - camera->body.yPos;
			o->render();
			if (o->body.physical)
				physics.update(o);
		}
}