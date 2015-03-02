#pragma once

#include "Physics.h"
#include "Camera.h"
#include "GameObject.h"
#include <vector>

class Environment
{
public:
	Environment(int worldWidth, int worldHeight, Camera* c);
	void update();
	// Might want a render() here

	void addObject(GameObject* o);

private:
	int WORLD_WIDTH;
	int WORLD_HEIGHT;

	std::vector<GameObject*> environment;
	Camera* camera;
	Physics* physics;
};
