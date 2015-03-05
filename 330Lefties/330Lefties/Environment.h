#pragma once

//#include "Physics.h"
#include "GameObject.h"
#include <vector>

class Environment
{
public:
	Environment(int worldWidth, int worldHeight, bool update_all = true);
	~Environment(void);

	//Call update() on objects in the environment.
	void update();

	//Add object to the environment.
	void addObject(GameObject* obj);

	//Remove object from environment.
	void removeObject(GameObject* obj);

	//Get world height.
	int getHeight();

	//Get world width.
	int getWidth();

	
	//Vector of objects in the environment.
	std::vector<GameObject*> objects;


private:
	int WORLD_WIDTH;
	int WORLD_HEIGHT;

	//Physics* physics;

	//Choose whether to update objects outside of the camera area
	//Possibly make more options in the future.
	bool update_all;
};
