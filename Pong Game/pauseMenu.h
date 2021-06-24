//INCLUSION AND LIBRARIES
#pragma once
#include "SFML\Graphics.hpp"
using namespace sf;

//DEFINING THE MAX. NUMBER OF ITEM THE MENU HAS

const int maximumNumberOfItems3 = 2;

class pauseMenu

{
private:

	//ATTRIBUTES
	int itemNumber3;
	Font itemFont3;
	Text itemText3[maximumNumberOfItems3];

public:

	pauseMenu(float width, float height);
	~pauseMenu();

	//FUNCTIONS
	void draw3(RenderWindow& window);
	void moveUp3();
	void moveDown3();
	int getSelectedItem3()

	{
		return itemNumber3;
	}
};

