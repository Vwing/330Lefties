#include "Environment.h"
#include <algorithm>

Environment::Environment(int worldWidth, int worldHeight, bool updateAll)
	: WORLD_WIDTH(worldWidth), WORLD_HEIGHT(worldHeight){

	//physics = new Physics(WORLD_HEIGHT, WORLD_WIDTH);
	update_all = updateAll;
}

Environment::~Environment(void){

}

void Environment::update(){
	/*
		Temporary update function.

		Objects may want to update despite whether they can be seen by the
		camera or not. This function only updates what can be seen by the camera.
	*/
	if (update_all){
		for (int i=0; i<objects.size(); i++){
			objects.at(i)->update();
		}
	}
	else{
		/*
		for (int i=0; i<objects.size(); i++){
			if (camera->canSee(objects.at(i))){
				//only updates objects that the camera can see.
				objects.at(i)->update();
				//physics update
				
				if (objects.at(i)->physical){
					physics->update(objects.at(i));
				}
				
			}
		}
		*/
	}
	
}

void Environment::addObject(GameObject* obj){
	objects.push_back(obj);
}

void Environment::removeObject(GameObject* obj){
	std::vector<GameObject*>::iterator it;
	it = find(objects.begin(), objects.end(), obj);

	if (it != objects.end()){
		//find index
		int index = distance(objects.begin(), it);

		//swap and pop
		std::swap(objects.at(index), objects.back());
		objects.pop_back();
	}
}

int Environment::getHeight(){
	return WORLD_HEIGHT;
}

int Environment::getWidth(){
	return WORLD_WIDTH;
}