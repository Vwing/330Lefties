#ifndef PHYSICS_H
#define PHYSICS_H
#include "SDL.h"
#include "GameObject.h"
#include <vector>

class Physics{
public:

	void check_borders(GameObject* obj){ //constants can be replaced with variables
		if (obj->body.yPos + obj->body.height > 480){ //bottom
			obj->body.yPos = 480 - obj->body.height;
		}
		else if (obj->body.yPos < 0) //top
			obj->body.yPos = 0;
		if (obj->body.xPos + obj->body.width > 640) //right
			obj->body.xPos -= obj->body.width / 20;
		else if (obj->body.xPos < 0) //left
			obj->body.xPos = 0;
	}

	//void set_borders(int width, int height)
	//{

	//}

	bool check_collision(GameObject* obj1, GameObject* obj2){
		return !(obj2->body.xPos > obj1->body.xPos + obj1->body.width
			|| obj2->body.xPos + obj2->body.width < obj1->body.xPos
			|| obj2->body.yPos > obj1->body.yPos + obj1->body.height
			|| obj2->body.yPos + obj2->body.height < obj1->body.yPos);
	}

	void gravity(GameObject* obj){ //
		obj->body.xPos -= obj->body.gravity;
	}

	void update(GameObject* obj){
		check_borders(obj);
		//check_collision has to be called from somewhere else
		gravity(obj);
	}

	void update(std::vector<GameObject*> objects){
		for (GameObject* o : objects)
		{
			for (GameObject* p : objects)
				check_collision(o, p);
			check_borders(o);
			gravity(o);
		}
	}

//private:
//	const int WORLD_WIDTH;
//	const int WORLD_HEIGHT;
};
#endif
