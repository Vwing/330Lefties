#include "Camera.h"
#include <algorithm>

Camera::Camera(int width, int height, Environment* env, int xPos, int yPos)
{
	/*
		This class assumes objects' positions are relative to the top left corner
		of the environment/world.

		This means that the position of the object relative to the window/camera would be:
		relative_x = obj->body.xPos - body.xPos;
		relative_y = obj->body.yPos - body.yPos;
	*/

	body.width = width;
	body.height = height;
	body.xPos = xPos;
	body.yPos = yPos;
	body.physical = false;

	option = FIXED;
	pan_amount = 0;

	environment = env;
}

Camera::~Camera(void){

}

bool Camera::canSee(GameObject* obj){
	//For the sake of code clarity.
	Body& camera = body;
	Body& object = obj->body;

	//All must be true to be seen by the camera.
	bool within_left = false;
	bool within_right = false;
	bool within_top = false;
	bool within_bottom = false;

	//Check if within Camera's left edge.
	if (object.xPos < camera.xPos){
		if (object.xPos + object.width > camera.xPos){
			within_left = true;
		}
	}
	else{
		within_left = true;
	}

	//Check if within Camera's right edge.
	if (object.xPos < camera.xPos + camera.width){
		within_right = true;
	}

	//Check if within Camera's top edge.
	if (object.yPos < camera.yPos){
		if (object.yPos + object.height > camera.yPos){
			within_top = true;
		}
	}
	else{
		within_top = true;
	}

	//Check if within bottom edge.
	if (object.yPos < camera.yPos + camera.height){
		within_bottom = true;
	}


	//Returns true if all four values are true.
	return (within_left && within_right && within_top && within_bottom);
}


void Camera::setEnvironment(Environment* env){
	environment = env;
}

void Camera::setEnvironment(Environment* env, int x, int y){
	environment = env;
	body.xPos = x;
	body.yPos = y;
}

void Camera::setCameraPos(int x, int y){
	body.xPos = x;
	body.yPos = y;
}

void Camera::moveCamera(int dx, int dy){
	body.xPos += dx;
	body.yPos += dy;
}

void Camera::setPanAmount(int amt){
	pan_amount = amt;
}

void Camera::setCenterObject(GameObject* obj){
	center_obj = obj;
}

void Camera::update() {
	/*
		This is where the implementation for how the camera moves in the
		environment will go.

		Updates the camera's position relative to the environment.

		Does not update the environment objects.
	*/

	switch(option){
	case FIXED:
		//don't ever change. you're perfect just the way you are.
		break;
	case CENTER_OBJ:
		//center on center_obj
		body.xPos = (center_obj->body.xPos + (center_obj->body.width / 2)) - body.width;
		body.yPos = (center_obj->body.yPos + (center_obj->body.height / 2)) - body.height;
		break;
	case CONSTANT_PAN_X:
		if (body.xPos + pan_amount < 0){
			//if camera will go past left boundary
			body.xPos = 0;
		}
		else if (body.xPos + body.width + pan_amount > environment->getWidth()){
			//if camera will go past right boundary
			body.xPos = environment->getWidth() - body.width;
		}
		else{
			body.xPos += pan_amount;
		}
		break;
	case CONSTANT_PAN_Y:
		if (body.yPos + pan_amount < 0){
			//if camera will go past top boundary
			body.yPos = 0;
		}
		else if (body.yPos + body.height + pan_amount > environment->getHeight()){
			//if camera will go past bottom boundary
			body.yPos = environment->getHeight() - body.height;
		}
		else{
			body.yPos += pan_amount;
		}
		break;
	}
}

void Camera::render() {
	/*
		This method renders the objects visible by the Camera, in order by layer.

		Get all the elements that can be seen by the Camera, then render them by layer.
	*/
	std::vector<GameObject*>& objects = environment->objects;

	std::vector<GameObject*> visible;

	for (int i=0; i<objects.size(); i++){
		if(canSee(objects.at(i))){
			visible.push_back(objects.at(i));
		}
	}

	int layer;
	int index;

	//loop through visible objects list
	while(visible.size() > 0){
		layer = visible.at(0)->body.layer;
		index = 0;
		//find lowest layer
		for (int i=0; i<visible.size(); i++){
			if (visible.at(i)->body.layer < layer){
				layer = visible.at(i)->body.layer;
				index = i;
			}
		}

		//swap lowest layer element with the last element, then render and pop
		std::swap(visible.back(),visible.at(index));

		//update screen coordinates of object
		visible.back()->body.screenX = visible.back()->body.xPos - body.xPos;
		visible.back()->body.screenY = visible.back()->body.yPos - body.yPos;

		//objects hopefully render based on screen coordinates
		visible.back()->render();
		visible.pop_back();
	}
}

void Camera::handleEvent(SDL_Event sdlEvent) 
{
	/*
		Implementation for events:

		When and how should the camera move based on what input
	*/
}

int Camera::getHeight(){
	return body.height;
}

int Camera::getWidth(){
	return body.width;
}

int Camera::getX(){
	return body.xPos;
}

int Camera::getY(){
	return body.yPos;
}