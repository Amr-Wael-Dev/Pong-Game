//INCLUSION AND LIBRARIES
#include "pauseMenu.h"
#include <iostream>
using namespace std;
using namespace sf;

//CALLING THE CONSTRUCTOR
pauseMenu::pauseMenu(float width, float height)

{

	//FONT
	if (itemFont3.loadFromFile("Data/arial.ttf") == false)

	{
		cout << "error";
	}

	//TEXT
	itemText3[0].setFont(itemFont3);
	itemText3[0].setFillColor(Color::Red);
	itemText3[0].setString("Continue");
	itemText3[0].setCharacterSize(35);
	itemText3[0].setPosition(600, 200);

	itemText3[1].setFont(itemFont3);
	itemText3[1].setFillColor(Color::White);
	itemText3[1].setString("Return to Main Menu");
	itemText3[1].setCharacterSize(35);
	itemText3[1].setPosition(515, 295);

	itemNumber3 = 0;
}

pauseMenu::~pauseMenu()

{
}

//FUNCTIONS IMPLEMENTATION
void pauseMenu::draw3(RenderWindow& window)

{
	for (int i = 0; i < maximumNumberOfItems3; i++)

	{
		window.draw(itemText3[i]);
	}
}

void pauseMenu::moveUp3()

{
	if ((itemNumber3 - 1) >= -1)

	{
		itemText3[itemNumber3].setFillColor(Color::White);
		itemNumber3--;

		if (itemNumber3 == -1)

		{
			itemNumber3 = 1;
		}

		itemText3[itemNumber3].setFillColor(Color::Red);
	}
}

void pauseMenu::moveDown3()

{
	if ((itemNumber3 + 1) <= maximumNumberOfItems3)

	{
		itemText3[itemNumber3].setFillColor(Color::White);
		itemNumber3++;

		if (itemNumber3 == 2)

		{
			itemNumber3 = 0;
		}

		itemText3[itemNumber3].setFillColor(Color::Red);
	}
}