#pragma once

#include "GameObject.h"
#include "Environment.h"
#include "SDL.h"

class Camera : public GameObject
{
public:
	Camera(int width, int height, Environment* env, int xPos = 0, int yPos = 0);
	~Camera(void);

	//Determines whether an object lies within the camera range.
	bool canSee(GameObject* obj);
	
	//Changes the Environment that the camera moves through and renders.
	void setEnvironment(Environment* env);
	//Change Environment and change (x,y) position of camera.
	void setEnvironment(Environment* env, int x, int y);

	//Set the camera position (relative to the environment's top left corner).
	void setCameraPos(int x, int y);

	//Move camera position.
	void moveCamera(int dx, int dy);

	//Set the pixel amount the camera should move for a constant pan
	void setPanAmount(int amt);

	//Set the object the camera should center on
	void setCenterObject(GameObject* obj);

	//Get the camera width.
	int getWidth();
	//Get the camera height.
	int getHeight();
	//Get the camera x.
	int getX();
	//Get the camera y.
	int getY();


	void handleEvent(SDL_Event sdlEvent);
	void update();
	void render();

	
	enum MovementOption {CONSTANT_PAN_X, CONSTANT_PAN_Y, CENTER_OBJ, FIXED};

private:
	Environment* environment;
	MovementOption option;

	int pan_amount;
	GameObject* center_obj;
};
