#ifndef PHYSICS_H
#define PHYSICS_H
#include "SDL.h"
#include "Unit.h"
#include <vector>

class Physics{
public:
	Physics(int worldHeight, int worldWidth)
		:WORLD_HEIGHT(worldHeight), WORLD_WIDTH(worldWidth)
	{
	}

	// Returns true if given game object is colliding with world bounds
	// and moves the object back within the bounds. (<- should go in different function)
	bool check_borders(Unit* obj){ //constants can be replaced with variables
		if (obj->body.yPos + obj->body.height >= WORLD_HEIGHT){ //bottom
			obj->body.yPos = WORLD_HEIGHT - obj->body.height;
			return true;
		}
		else if (obj->body.yPos <= 0) //top
		{
			obj->body.yPos = 0;
			return true;
		}
		if (obj->body.xPos + obj->body.width >= WORLD_WIDTH) //right
		{
			obj->body.xPos -= obj->body.width / 20;
			return true;
		}
		else if (obj->body.xPos <= 0) //left
		{
			obj->body.xPos = 0;
			return true;
		}
			
	}

	void set_world(int width, int height)
	{
		WORLD_HEIGHT = height;
		WORLD_WIDTH = width;
	}

	bool check_collision(Unit* obj1, Unit* obj2){
		return !(obj2->body.xPos > obj1->body.xPos + obj1->body.width
			|| obj2->body.xPos + obj2->body.width < obj1->body.xPos
			|| obj2->body.yPos > obj1->body.yPos + obj1->body.height
			|| obj2->body.yPos + obj2->body.height < obj1->body.yPos);
	}

	void gravity(Unit* obj){ 
		// obj->body.xPos -= obj->body.gravity;
		obj->body.xPos -= 1;
	}

	void update(Unit* obj){
		check_borders(obj);
		//check_collision has to be called from somewhere else
		gravity(obj);
	}

	void update(std::vector<Unit*> objects){
		for (Unit* o : objects)
		{
			for (Unit* p : objects)
				check_collision(o, p);
			check_borders(o);
			gravity(o);
		}
	}

private:
	int WORLD_WIDTH;
	int WORLD_HEIGHT;
};
#endif
