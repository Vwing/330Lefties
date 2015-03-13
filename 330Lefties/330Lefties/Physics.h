#ifndef PHYSICS_H
#define PHYSICS_H
#include "SDL.h"
#include "Unit.h"
#include <vector>
#include <math.h> //I don't think this is needed, but it's here just in case

class Physics{
public:
	Physics(int worldWidth, int worldHeight)
		:WORLD_HEIGHT(worldHeight), WORLD_WIDTH(worldWidth)
	{
	}

	bool check_borders(Unit* obj){
		return (obj->body.yPos + obj->body.height >= WORLD_HEIGHT //bottom
			|| obj->body.yPos <= 0 //top
			|| obj->body.xPos + obj->body.width >= WORLD_WIDTH //right
			|| obj->body.xPos <= 0); //left
	}

	void set_world(int width, int height){
		WORLD_HEIGHT = height;
		WORLD_WIDTH = width;
	}

	bool check_collision(Unit* obj1, Unit* obj2){
		//The sides of the rectangles
		int left1, left2;
		int right1, right2;
		int top1, top2;
		int bottom1, bottom2;

		//Calculate the sides of obj1
		left1 = obj1->body.xPos;
		right1 = obj1->body.xPos + obj1->body.width;
		top1 = obj1->body.yPos;
		bottom1 = obj1->body.yPos + obj1->body.height;

		//Calculate the sides of obj2
		left2 = obj2->body.xPos;
		right2 = obj2->body.xPos + obj2->body.width;
		top2 = obj2->body.yPos;
		bottom2 = obj2->body.yPos + obj2->body.height;

		bool physicsEnabled = obj1.enablePhysics && obj2.enablePhysics;
		//If any of the sides from 1 are outside of 2
		if (bottom1 < top2)
		{
			return false;
		}
		else if(physicsEnabled) // If physics enabled, don't allow overlap
		{
			int diff = bottom1 - top2; 
			obj1->body.yPos -= diff;
			return true;
		}
		if (top1 > bottom2)
		{
			return false;
		}
		else if(physicsEnabled) // If physics enabled, don't allow overlap
		{
			int diff = bottom2 - top1; 
			obj1->body.yPos += diff;
			return true;
		}
		if(right1 < left2)
		{
			return false;
		}
		else if(physicsEnabled)
		{
			int diff = right1 - left2;
			obj1->body.xPos -= diff;
			return true;
		}
		if(left1 > right2)
		{
			return false;
		}
		else if(physicsEnabled)
		{
			int diff = right2 - left1;
			obj1->body.xPos += diff;
			return true;
		}
	}


	bool collide(Unit* obj1, Unit* obj2, Uint32 the_event){
		if (check_collision(obj1, obj2)){
			obj1->handleEvent(the_event);
			obj2->handleEvent(the_event);
				
			return true;
		}
		return false;
	}

	bool collide(Unit* obj, std::vector<Unit*> group, Uint32 the_event){
		bool result;
		if (group.size() == 0)
			return false;

		for (Unit* unit : group) {
			if (check_collision(obj, unit)){
				obj->handleEvent(the_event);
				unit->handleEvent(the_event);
				result = true;
			}
		}
		return result;
	}

	bool collide(std::vector<Unit*> group1, std::vector<Unit*> group2, Uint32 the_event){
		bool result;
		if (group1.size() == 0 || group2.size() == 0)
		{
			return false;
		}

		for (Unit* unit1 : group1){
			for (Unit* unit2 : group2){
				if (check_collision(unit1, unit2)){
					unit1->handleEvent(the_event);
					unit2->handleEvent(the_event);
					result = true;
				}
			}
		}
	return result;
}


int magnitude(Unit* obj){
	return obj->body.width * obj->body.height;
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
