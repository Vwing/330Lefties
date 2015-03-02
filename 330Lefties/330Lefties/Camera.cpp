#include "Camera.h"

Camera::Camera(int width, int height, int xPos, int yPos)
{
	body.width = width;
	body.height = height;
	body.xPos = xPos;
	body.yPos = yPos;
	body.physical = false;

	// add subscriptions here
}

bool Camera::canSee(GameObject* obj1){ //stolen from Physics
	return !(body.xPos > obj1->body.xPos + obj1->body.width
		|| body.xPos + body.width < obj1->body.xPos
		|| body.yPos > obj1->body.yPos + obj1->body.height
		|| body.yPos + body.height < obj1->body.yPos);
}

void Camera::update() {}

void Camera::render() {}

void Camera::handleEvent(SDL_Event sdlEvent) 
{
	/*
		Implementation for events:
		
		When and how should the camera move based on what input
	
	*/
}
