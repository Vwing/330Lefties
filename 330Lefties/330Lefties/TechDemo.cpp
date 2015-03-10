#include <iostream>
#include <sstream>
#include <Windows.h>
#include "res_path.h"
#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Sprite* MakeSprite(std::string resPath, Game* game)
{
	Sprite* sprite1 = game->createSprite(resPath + "player.png", 95, 130);
	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(0, 0), 100);
	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(95, 0), 100);
	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(190, 0), 100);
	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(285, 0), 100);
	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(380, 0), 100);
	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(475, 0), 100);
	sprite1->addFrameToSequence("walk right", sprite1->makeFrame(570, 0), 100);

	sprite1->addFrameToSequence("walk left", sprite1->makeFrame(570, 260), 100);
	sprite1->setTexture(resPath + "Up.png", game->renderer);
	sprite1->addFrameToSequence("walk up", sprite1->makeFrame(0, 0), 100);
	sprite1->setTexture(resPath + "Down.png", game->renderer);
	for (int i = 0; i<13; i++)
	{
		for (int j = 0; j<5; j++)
		{
			sprite1->addFrameToSequence("walk down", sprite1->makeFrame(0, i * 130), 100);
		}
	}
	
	return sprite1;
}

int main(int argc, char **argv){

	Game* game = new Game(SCREEN_WIDTH, SCREEN_HEIGHT, 500, 500);
	Camera* camera = game->camera;

	const std::string resPath = getResourcePath("SpriteDemo");

	Sprite* spriteBG = game->createSprite(resPath + "Background.png", SCREEN_WIDTH, SCREEN_HEIGHT);
	//spriteBG->body.layer = 0;
	int bgFrame = spriteBG->makeFrame(0, 0);
	game->addToEnvironment(spriteBG);

	Sprite* sprite1 = MakeSprite(resPath, game);
	Sprite* sprite2 = MakeSprite(resPath, game);

	int x = SCREEN_WIDTH / 2 - sprite1->body.width / 2;
	int y = SCREEN_HEIGHT / 2 - sprite1->body.height / 2;
	sprite1->setPos(x, y);
	sprite2->setPos(x + sprite2->body.width, y);

	Character* guy = new Character(sprite1, 100);
	Character* guy2 = new Character(sprite2, 100);
	game->addToEnvironment(guy);
	game->addToEnvironment(guy2);
	camera->setCenterObject(guy);

	while (!game->isOver()){

		game->update();
		//Render the scene
		game->render();
	}


	getchar();

	return 0;
}
