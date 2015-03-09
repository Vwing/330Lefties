#include <SDL.h>
#include "Sprite.h"
#include <vector>
#include "UI_Element.h"
#include "Button.h"

class UI
{
public:
	
	UI();
	~UI();

	std::vector<UI_Element*> elements;

	// Add button by creating a new sprite with params
	Button* addButton(std::function<void(void)> funcToCall, std::string filePath, int width, int height, int xPos = 0, int yPos = 0);
	// Add button using existing sprite
	// Button* addButton(Sprite* sprite);

	void handleEvent(Uint32 sdlEvent);
	void update();
	void render();

};
