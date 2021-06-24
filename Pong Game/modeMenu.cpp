//INCLUSION AND LIBRARIES
#include "modeMenu.h"
#include <iostream>
using namespace std;
using namespace sf;

//CALLING THE CONSTRUCTOR
modeMenu::modeMenu(float width, float height)

{

	//FONT
	if (itemFont2.loadFromFile("Data/arial.ttf") == false)

	{
		cout << "error";
	}

	//TEXT
	itemText2[0].setFont(itemFont2);
	itemText2[0].setFillColor(Color::Red);
	itemText2[0].setString("Normal Mode");
	itemText2[0].setCharacterSize(25);
	itemText2[0].setPosition(595, 100);

	itemText2[1].setFont(itemFont2);
	itemText2[1].setFillColor(Color::White);
	itemText2[1].setString("Mouse Mode");
	itemText2[1].setCharacterSize(25);
	itemText2[1].setPosition(595, 200);

	itemText2[2].setFont(itemFont2);
	itemText2[2].setFillColor(Color::White);
	itemText2[2].setString("Warp Mode");
	itemText2[2].setCharacterSize(25);
	itemText2[2].setPosition(605, 300);

	itemText2[3].setFont(itemFont2);
	itemText2[3].setFillColor(Color::White);
	itemText2[3].setString("Inverted Mode");
	itemText2[3].setCharacterSize(25);
	itemText2[3].setPosition(592, 400);

	itemText2[4].setFont(itemFont2);
	itemText2[4].setFillColor(Color::White);
	itemText2[4].setString("Back To Main Menu");
	itemText2[4].setCharacterSize(25);
	itemText2[4].setPosition(560, 500);

	itemNumber2 = 0;
}

modeMenu::~modeMenu()

{
}

//FUNCTIONS IMPLEMENTATION
void modeMenu::draw2(RenderWindow& window)

{
	for (int i = 0; i < maximumNumberOfItems2; i++)

	{
		window.draw(itemText2[i]);
	}
}

void modeMenu::moveUp2()

{
	if ((itemNumber2 - 1) >= -1)

	{
		itemText2[itemNumber2].setFillColor(Color::White);
		itemNumber2--;

		if (itemNumber2 == -1)

		{
			itemNumber2 = 4;
		}

		itemText2[itemNumber2].setFillColor(Color::Red);
	}
}

void modeMenu::moveDown2()

{
	if ((itemNumber2 + 1) <= maximumNumberOfItems2)

	{
		itemText2[itemNumber2].setFillColor(Color::White);
		itemNumber2++;

		if (itemNumber2 == 5)

		{
			itemNumber2 = 0;
		}

		itemText2[itemNumber2].setFillColor(Color::Red);
	}
}