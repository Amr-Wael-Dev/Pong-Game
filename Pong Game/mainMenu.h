//INCLUSION AND LIBRARIES
#pragma once
#include "SFML\Graphics.hpp"
using namespace sf;

//DEFINING THE MAX. NUMBER OF ITEM THE MENU HAS
const int maximumNumberOfItems = 3;

class mainMenu

{
private:

	//ATTRIBUTES
	int itemNumber;
	Font itemFont;
	Text itemText[maximumNumberOfItems];

public:

	mainMenu(float width, float height);
	~mainMenu();

	//FUNCTIONS
	void draw(RenderWindow& window);
	void moveUp();
	void moveDown();
	int getSelectedItem()

	{
		return itemNumber;
	}
};

