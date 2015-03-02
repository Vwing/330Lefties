#pragma once

#include "Physics.h"
#include "Camera.h"
#include "GameObject.h"
#include <vector>

class Environment
{
public:
	Environment();
	void update();

private:
	std::vector<GameObject*> environment;
	Camera* camera;
	Physics physics;
};