#include "UI.h"

UI::UI()
{

}

UI::~UI()
{

}

// Add button by creating a new sprite with params
/*
Button* UI::addButton(std::string filePath, int width, int height, int xPos = 0, int yPos = 0)
{
	Button* newButton = new Button(filePath, width, height, xPos, yPos);
	elements.push_back(newButton);
	return newButton;
}

// Add button using existing sprite
Button* UI::addButton(Sprite* sprite)
{
	Button* newButton = new Button(sprite);
	elements.push_back(newButton);
	return newButton;
}
*/

void UI::handleEvent(Uint32 sdlEvent)
{

}

void UI::update()
{
	for (UI_Element* el : elements)
	{
		el->update();
	}
}
void UI::render()
{
	for (UI_Element* el : elements)
	{
		el->render();
	}
}