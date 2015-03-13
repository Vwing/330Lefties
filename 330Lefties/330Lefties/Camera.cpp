#include "Camera.h"
#include "Globals.h"
#include <algorithm>
#include <queue>

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
	//body.physical = false;

	option = FIXED;
	pan_amount = 0;

	environment = env;
	offset_x = 0;
	offset_y = 0;
	pan_rate = 0;
	counter = 0;

	//set camera movement option with these key presses
	Global_RegisterForEvent(this, SDLK_o);
	Global_RegisterForEvent(this, SDLK_f);
	Global_RegisterForEvent(this, SDLK_x);
	Global_RegisterForEvent(this, SDLK_y);
	Global_RegisterForEvent(this, SDLK_1);
	Global_RegisterForEvent(this, SDLK_2);
	Global_RegisterForEvent(this, SDLK_3);
	Global_RegisterForEvent(this, SDLK_4);
}

Camera::~Camera(void){

}

bool Camera::canSee(GameObject* obj){
	if (!obj->body.visible)
		return false;

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
		body.xPos = (center_obj->body.xPos + (center_obj->body.width / 2)) - (body.width / 2) + offset_x;
		body.yPos = (center_obj->body.yPos + (center_obj->body.height / 2)) - (body.height / 2) + offset_y;
		break;
	case CONSTANT_PAN_X:
		/*
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
		}*/
		
		if (counter == pan_rate){
			body.xPos += pan_amount;
			counter = 0;
		}
		else{
			counter++;
		}
		break;
	case CONSTANT_PAN_Y:
		/*
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
		}*/
		if (counter == pan_rate){
			body.yPos += pan_amount;
			counter = 0;
		}
		else{
			counter++;
		}
		break;
	}
}

void Camera::render() {
	/*
		This method renders the objects visible by the Camera, in order by layer.

		Get all the elements that can be seen by the Camera, then render them by layer.
	*/

	class CompareGameObjects{
	public:
		bool operator()(GameObject* t1, GameObject* t2) //for use in a priority queue. Useful for rendering by layer.
		{
			if (t1->body.layer < t2->body.layer) return true;
			else if (t1->body.layer == t2->body.layer && t1->body.width * t1->body.height < t2->body.width * t2->body.height)
				return true; //same layer? Render larger object first.
			return false;
		}
	};
	std::vector<GameObject*>& objects = environment->objects;

	std::priority_queue<GameObject*, std::vector<GameObject*>, CompareGameObjects> visible;

	for (int i=0; i<objects.size(); ++i){
		if(canSee(objects.at(i))){
			visible.push(objects.at(i));
		}
	}

	int layer;
	int index;

	//loop through visible objects list
	while(!visible.empty()){

		//update screen coordinates of object
		visible.top()->body.screenX = visible.top()->body.xPos - body.xPos;
		visible.top()->body.screenY = visible.top()->body.yPos - body.yPos;

		//objects hopefully render based on screen coordinates
		visible.top()->render();
		visible.pop();
	}
}

void Camera::handleEvent(Uint32 sdlEvent) 
{
	if (sdlEvent == SDLK_f || sdlEvent == SDLK_1)
	{
		setMovementOption(FIXED);
	}
	else if (sdlEvent == SDLK_o || sdlEvent == SDLK_2)
	{
		setMovementOption(CENTER_OBJ);
	}
	else if (sdlEvent == SDLK_x || sdlEvent == SDLK_3)
	{
		setMovementOption(CONSTANT_PAN_X);
	}
	else if (sdlEvent == SDLK_y || sdlEvent == SDLK_4)
	{
		setMovementOption(CONSTANT_PAN_Y);
	}
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

void Camera::setMovementOption(MovementOption opt){
	option = opt;
}

void Camera::setMovementOption(std::string opt){
	if (opt == "FIXED")
		option = FIXED;
	if (opt == "CENTER_OBJ")
		option = CENTER_OBJ;
	if (opt == "PAN_X")
		option = CONSTANT_PAN_X;
	if (opt == "PAN_Y")
		option = CONSTANT_PAN_Y;
}

void Camera::setOffset(int x, int y){
	offset_x = x;
	offset_y = y;
}

void Camera::setPanRate(int rate){
	pan_rate = rate;
}