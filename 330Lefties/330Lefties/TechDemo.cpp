#include <iostream>
#include <sstream>
#include <Windows.h>
#include "res_path.h"
#include "Globals.h"
#include "Game.h"
#include "SoundManager.h"
#include "Timer.h"
#include <ostream>
#include "TextBoxResource.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int LEVEL_WIDTH = 2560;
const int LEVEL_HEIGHT = 1600;
const int FRAMES_PER_SECOND = 60;

void helperAddMToMoveSequence(Sprite* sprite1, std::string sequence, int frame1, int frame2, int frame3){
	std::vector<int> moveFrames;
	moveFrames.clear();
	moveFrames.push_back(frame1);
	moveFrames.push_back(frame2);
	moveFrames.push_back(frame3);
	for (int frameNum : moveFrames)
		for (int i = 0; i < 10; i++)
			sprite1->addFrameToSequence(sequence, frameNum, 2);
}

Sprite* MakeSprite(std::string resPath, Game* game)
{
	Sprite* sprite1 = game->createSprite(resPath + "Fey.png", 32, 32);
	int frame1 = sprite1->makeFrame(0, 0);
	int frame2 = sprite1->makeFrame(32, 0);
	int frame3 = sprite1->makeFrame(64, 0);
	helperAddMToMoveSequence(sprite1, "walk down", frame1, frame2, frame3);

	frame1 = sprite1->makeFrame(0, 32);
	frame2 = sprite1->makeFrame(32, 32);
	frame3 = sprite1->makeFrame(64, 32);
	helperAddMToMoveSequence(sprite1, "walk left", frame1, frame2, frame3);

	frame1 = sprite1->makeFrame(0, 64);
	frame2 = sprite1->makeFrame(32, 64);
	frame3 = sprite1->makeFrame(64, 64);
	helperAddMToMoveSequence(sprite1, "walk right", frame1, frame2, frame3);

	frame1 = sprite1->makeFrame(0, 96);
	frame2 = sprite1->makeFrame(32, 96);
	frame3 = sprite1->makeFrame(64, 96);
	helperAddMToMoveSequence(sprite1, "walk up", frame1, frame2, frame3);

	return sprite1;
}

//bool vHeld = false;
//
//void handleEvent(Uint32 sdlEvent)
//{
//	if (sdlEvent == SDLK_v)
//	{
//		vHeld = true;
//	}
//}

int main(int argc, char **argv){

	Game* game = new Game(SCREEN_WIDTH, SCREEN_HEIGHT, 500, 500);

	Timer fps;

	TextBoxResource *TextBoxResource = TextBoxResource::getInstance();

	const std::string resPath = getResourcePath("SpriteDemo");

	Sprite* spriteBG = game->createSprite(resPath + "Background2.png", LEVEL_WIDTH, LEVEL_HEIGHT);
	spriteBG->body.layer = 2;
	spriteBG->makeFrame(0, 0);

	game->getSoundManager().setMusic(resPath + "loop1.wav");
	game->getSoundManager().playMusic();

	game->getSoundManager().createEffect("walk", resPath + "step1.wav");
	game->getSoundManager().createEffect("collide", resPath + "collide.wav");

	TextBoxResource->loadFont(resPath + "SpecialElite.ttf", 30);

	// game->setEnvironment(1000, SCREEN_HEIGHT);   (STILL DEBUGGING)
	game->addToEnvironment(spriteBG);

	// Button won't listen for events properly.
	Uint32 buttonDownEvent = 500;
	Button* button = game->addButton(resPath + "button_states.png", buttonDownEvent, 200, 40);
	button->onButtonUp(0, 0);
	button->onButtonDown(0, 40);
	button->onButtonOver(0, 80);

	Sprite* sprite1 = MakeSprite(resPath, game);
	Sprite* sprite2 = MakeSprite(resPath, game);

	//int x = SCREEN_WIDTH / 2 - sprite1->body.width / 2;
	//int y = SCREEN_HEIGHT / 2 - sprite1->body.height / 2;
	int x = 10;
	int y = LEVEL_HEIGHT * 7 / 13;

	sprite1->setPos(x, y);
	sprite2->setPos(x + sprite2->body.width, y);
	sprite1->changeSequence("walk up");
	sprite2->changeSequence("walk up");

	Character* guy = new Character(sprite1, 100);
	Character* guy2 = new Character(sprite2, 100);
	Global_RegisterForEvent(guy2, SDLK_v);
	game->addToEnvironment(guy);
	game->addToEnvironment(guy2);
	game->camera->setCenterObject(guy);
	game->camera->setMovementOption("CENTER_OBJ");

	Uint32 collideEvent = 999999;

	while (!game->isOver())
	{
		fps.start();
		game->update();
		//Render the scene
		game->render();

		if (game->physics->collide(guy, guy2, collideEvent))
		{
			game->getSoundManager().playEffect("collide");
		}
		while (fps.getTicks() < 1000 / FRAMES_PER_SECOND){}
	}


	getchar();

	return 0;
}
