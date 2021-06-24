//INCLUSION AND LIBRARIES
#include "mainMenu.h"
#include <iostream>
using namespace std;
using namespace sf;

//CALLING THE CONSTRUCTOR
mainMenu::mainMenu(float width, float height)

{

	//FONT
	if (itemFont.loadFromFile("Data/arial.ttf") == false)

	{
		cout << "error";
	}

	//TEXT
	itemText[0].setFont(itemFont);
	itemText[0].setFillColor(Color::Red);
	itemText[0].setString("Player 1 VS Computer");
	itemText[0].setCharacterSize(30);
	itemText[0].setPosition(525, 200);

	itemText[1].setFont(itemFont);
	itemText[1].setFillColor(Color::White);
	itemText[1].setString("Player 1 VS Player 2");
	itemText[1].setCharacterSize(30);
	itemText[1].setPosition(535, 300);

	itemText[2].setFont(itemFont);
	itemText[2].setFillColor(Color::White);
	itemText[2].setString("Exit");
	itemText[2].setCharacterSize(30);
	itemText[2].setPosition(643, 400);

	itemNumber = 0;
}

mainMenu::~mainMenu()

{
}

//FUNCTIONS IMPLEMENTATION
void mainMenu::draw(RenderWindow& window)

{
	for (int i = 0; i < maximumNumberOfItems; i++)

	{
		window.draw(itemText[i]);
	}
}

void mainMenu::moveUp()

{
	if ((itemNumber - 1) >= -1)

	{
		itemText[itemNumber].setFillColor(Color::White);
		itemNumber--;

		if (itemNumber == -1)

		{
			itemNumber = 2;
		}

		itemText[itemNumber].setFillColor(Color::Red);
	}
}

void mainMenu::moveDown()

{
	if ((itemNumber + 1) <= maximumNumberOfItems)

	{
		itemText[itemNumber].setFillColor(Color::White);
		itemNumber++;

		if (itemNumber == 3)

		{
			itemNumber = 0;
		}

		itemText[itemNumber].setFillColor(Color::Red);
	}
}