#include <iostream>
#include <sstream>
#include <Windows.h>
#include "res_path.h"
#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char **argv){

	Game* game = new Game(SCREEN_WIDTH, SCREEN_HEIGHT, 500, 500);

	const std::string resPath = getResourcePath("330LProject");

	Sprite* spriteBG = game->createSprite(resPath + "Background.png", SCREEN_WIDTH, SCREEN_HEIGHT);
	int bgFrame = spriteBG->makeFrame(0, 0);
	game->addToEnvironment(spriteBG);

	Sprite* sprite1 = game->createSprite(resPath + "Fey.png", 32, 32);

	int down1 = sprite1->makeFrame(0, 0);
	int down2 = sprite1->makeFrame(32, 0);
	int down3 = sprite1->makeFrame(64, 0);
	int left1 = sprite1->makeFrame(0, 36);
	int left2 = sprite1->makeFrame(32, 36);
	int left3 = sprite1->makeFrame(64, 36);
	int right1 = sprite1->makeFrame(0, 72);
	int right2 = sprite1->makeFrame(32, 72);
	int right3 = sprite1->makeFrame(64, 72);
	int up1 = sprite1->makeFrame(0, 108);
	int up2 = sprite1->makeFrame(32, 108);
	int up3 = sprite1->makeFrame(64, 108);

	sprite1->addFrameToSequence("walk down", down1, 100);
	sprite1->addFrameToSequence("walk left", left1, 100);
	sprite1->addFrameToSequence("walk right", right1, 100);
	sprite1->addFrameToSequence("walk up", up1, 100);

	sprite1->addFrameToSequence("walk down", down2, 100);
	sprite1->addFrameToSequence("walk left", left2, 100);
	sprite1->addFrameToSequence("walk right", right2, 100);
	sprite1->addFrameToSequence("walk up", up2, 100);

	sprite1->addFrameToSequence("walk down", down3, 100);
	sprite1->addFrameToSequence("walk left", left3, 100);
	sprite1->addFrameToSequence("walk right", right3, 100);
	sprite1->addFrameToSequence("walk up", up3, 100);

	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 2;
	sprite1->setPos(x, y);

	Character* guy = new Character(sprite1, 100);
	game->addToEnvironment(guy);

	while (!game->isOver()){

		game->update();
		//Render the scene
		game->render();
	}


	getchar();

	return 0;
}
