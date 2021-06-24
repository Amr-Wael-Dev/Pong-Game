//INCLUSION AND LIBRARIES
#pragma once
#include "SFML\Graphics.hpp"
using namespace sf;

//DEFINING THE MAX. NUMBER OF ITEM THE MENU HAS

const int maximumNumberOfItems2 = 5;

class modeMenu

{
private:

	//ATTRIBUTES
	int itemNumber2;
	Font itemFont2;
	Text itemText2[maximumNumberOfItems2];

public:

	modeMenu(float width, float height);
	~modeMenu();

	//FUNCTIONS
	void draw2(RenderWindow& window);
	void moveUp2();
	void moveDown2();
	int getSelectedItem2()

	{
		return itemNumber2;
	}
};
