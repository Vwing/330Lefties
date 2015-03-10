#ifndef PHYSICS_H
#define PHYSICS_H
#include "SDL.h"
#include "Unit.h"
#include <vector>
#include <math.h> //I don't think this is needed, but it's here just in case

class Physics{
public:
	Physics(int worldHeight, int worldWidth)
		:WORLD_HEIGHT(worldHeight), WORLD_WIDTH(worldWidth)
	{
	}

bool check_borders(Unit* obj){
	return (obj->body.yPos + obj->body.height >= WORLD_HEIGHT //bottom
	|| obj->body.yPos <= 0 //top
	|| obj->body.xPos + obj->body.width >= WORLD_WIDTH //right
	|| obj->body.xPos <= 0) //left
	}

void set_world(int width, int height){
	WORLD_HEIGHT = height;
	WORLD_WIDTH = width;
	}

bool check_collision(Unit* obj1, Unit* obj2){
	return !(obj2->body.xPos > obj1->body.xPos + obj1->body.width
	|| obj2->body.xPos + obj2->body.width < obj1->body.xPos
	|| obj2->body.yPos > obj1->body.yPos + obj1->body.height
	|| obj2->body.yPos + obj2->body.height < obj1->body.yPos);
	}

int magnitude(Unit* obj){
	return obj->width * obj->height;
	}

void gravity(Unit* obj){
	obj->body.xPos += (log10(magnitude(obj)))/1.5;
	}

void update(Unit* obj){
	check_borders(obj);
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
