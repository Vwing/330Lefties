#include "UI.h"

UI::UI()
{
	elements = std::vector<UI_Element*>();	
}

UI::~UI()
{
	elements.clear();
}

// Add button by creating a new sprite with params
/*
Button* UI::addButton(std::function<void(void)> funcToCall, std::string filePath, int width, int height, int xPos = 0, int yPos = 0)
{
	Button* newButton = new Button(funcToCall, new Sprite(filePath, width, height, xPos, yPos));
	elements.push_back(newButton);
	return newButton;
}
*/

// Add button using existing sprite
Button* UI::addButton(Sprite* sprite, Uint32 onDownEvent)
{
	Button* newButton = new Button(sprite, onDownEvent);
	elements.push_back(newButton);
	return newButton;
}

void UI::handleEvent(Uint32 sdlEvent)
{

}

void UI::update()
{
	for (int i = 0; i < elements.size(); i++)
	{
		elements[i]->update();
	}
}
void UI::render()
{
	for (int i = 0; i < elements.size(); i++)
	{
		elements[i]->render();
	}
}
