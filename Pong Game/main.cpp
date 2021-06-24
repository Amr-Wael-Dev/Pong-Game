//INCLUSION AND LIBRARIES 
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include "mainMenu.h"
#include "modeMenu.h"
#include "pauseMenu.h"
using namespace sf;
using namespace std;

//STATES FOR EVENTS
bool upKeyPressed = false;
bool downKeyPressed = false;
bool wKeyPressed = false;
bool sKeyPressed = false;
bool ballMove = true;
bool firstScore = false;

//STATES FOR MODES
bool player2On;
bool invertedMode;
bool mouseMode;
bool warpMode;

//STATES FOR WINNING
bool player1Won = false;
bool player2Won = false;
bool cpuWon = false;
bool drawGame = false;

//STATES FOR MENUS
bool playerChoice = false;
bool modeChoice = false;
bool paused = false;

//ENTRY POINT
int main()

{

	//WINDOW CREATION
	RenderWindow window(VideoMode(1340, 660), "Pong", Style::Close | Style::Resize | Style::Titlebar);
	window.setPosition(Vector2i(5, 5));
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	//EVENTS
	Event evnt;
	Event mainMenuEvent;
	Event modeMenuEvent;
	Event pauseMenuEvent;

	//MENUS
	mainMenu mainMenu(1340, 660);
	modeMenu modeMenu(1340, 660);
	pauseMenu pauseMenu(1340, 660);

	//FONT
	Font font;

	if (font.loadFromFile("Data/arial.ttf") == 0)

	{
		return 1;
	}

	//TEXT
	Text score;
	Text time;
	Text spaceBallMove;
	Text player1WinMessage;
	Text player2WinMessage;
	Text cpuWinMessage;
	Text drawMessage;
	Text continueMessage;

	//TIME
	Time::Time();

	Clock gameClock;
	Time elapsed = gameClock.getElapsedTime();
	Time gameTime = seconds(420);

	//SOUND BUFFERS
	SoundBuffer roofFloorHitBuffer;

	if (roofFloorHitBuffer.loadFromFile("Data/roofFloorHit.wav") == 0)

	{
		return 1;
	}

	SoundBuffer player1HitBuffer;

	if (player1HitBuffer.loadFromFile("Data/playerHit.wav") == 0)

	{
		return 1;
	}

	SoundBuffer player2HitBuffer;

	if (player2HitBuffer.loadFromFile("Data/playerHit.wav") == 0)

	{
		return 1;
	}

	SoundBuffer cpuPlayerHitBuffer;

	if (cpuPlayerHitBuffer.loadFromFile("Data/playerHit.wav") == 0)

	{
		return 1;
	}

	SoundBuffer menuMovementBuffer;

	if (menuMovementBuffer.loadFromFile("Data/menuMovement.wav") == 0)

	{
		return 1;
	}

	SoundBuffer menuSelectionBuffer;

	if (menuSelectionBuffer.loadFromFile("Data/menuSelection.wav") == 0)

	{
		return 1;
	}

	SoundBuffer goalScoreBuffer;

	if (goalScoreBuffer.loadFromFile("Data/goalScore.wav") == 0)

	{
		return 1;
	}

	SoundBuffer player1WinsBuffer;

	if (player1WinsBuffer.loadFromFile("Data/player1Wins.wav") == 0)

	{
		return 1;
	}

	SoundBuffer player2WinsBuffer;

	if (player2WinsBuffer.loadFromFile("Data/player2Wins.wav") == 0)

	{
		return 1;
	}

	SoundBuffer losingBuffer;

	if (losingBuffer.loadFromFile("Data/losing.wav") == 0)

	{
		return 1;
	}

	//SOUND EFFECTS

	Sound roofFloorHit;
	roofFloorHit.setBuffer(roofFloorHitBuffer);

	Sound player1Hit;
	player1Hit.setBuffer(player1HitBuffer);

	Sound player2Hit;
	player2Hit.setBuffer(player2HitBuffer);

	Sound cpuPlayerHit;
	cpuPlayerHit.setBuffer(cpuPlayerHitBuffer);

	Sound menuMovement;
	menuMovement.setBuffer(menuMovementBuffer);

	Sound menuSelection;
	menuSelection.setBuffer(menuSelectionBuffer);

	Sound goalScore;
	goalScore.setBuffer(goalScoreBuffer);

	Sound player1Wins;
	player1Wins.setBuffer(player1WinsBuffer);

	Sound player2Wins;
	player2Wins.setBuffer(player2WinsBuffer);

	Sound losing;
	losing.setBuffer(losingBuffer);

	//BACKGROUND MUSIC
	Music gameMusic1;

	if (gameMusic1.openFromFile("Data/gameMusic1.ogg") == 0)

	{
		return 1;
	}

	gameMusic1.setLoop(true);
	gameMusic1.setVolume(80);
	gameMusic1.play();

	//SCORE
	score.setFont(font);
	score.setCharacterSize(40);
	score.setFillColor(Color::White);
	score.setOrigin(Vector2f(10, 10));
	score.setPosition(Vector2f(window.getSize().x / 2 - 45, 20));
	int player1Score = 0;
	int player2Score = 0;

	//WIN MESSAGE
	player1WinMessage.setFont(font);
	player1WinMessage.setCharacterSize(100);
	player1WinMessage.setPosition(Vector2f(235, 200));
	player1WinMessage.setFillColor(Color::Red);
	player1WinMessage.setString("PLAYER 1 WINS !!!");

	player2WinMessage.setFont(font);
	player2WinMessage.setCharacterSize(100);
	player2WinMessage.setPosition(Vector2f(235, 200));
	player2WinMessage.setFillColor(Color::Red);
	player2WinMessage.setString("PLAYER 2 WINS !!!");

	cpuWinMessage.setFont(font);
	cpuWinMessage.setCharacterSize(100);
	cpuWinMessage.setPosition(Vector2f(185, 200));
	cpuWinMessage.setFillColor(Color::Red);
	cpuWinMessage.setString("COMPUTER WINS !!!");

	drawMessage.setFont(font);
	drawMessage.setCharacterSize(100);
	drawMessage.setPosition(Vector2f(320, 200));
	drawMessage.setFillColor(Color::Red);
	drawMessage.setString("It's a Draw ...");

	continueMessage.setFont(font);
	continueMessage.setCharacterSize(20);
	continueMessage.setPosition(Vector2f(1000, 620));
	continueMessage.setString("Press Any Key to Continue ...");

	//TIME MESSAGE
	time.setFont(font);
	time.setCharacterSize(20);
	time.setPosition(1130, 10);

	//MESSAGE TO INFORM PLAYER HOW TO MOVE THE BALL AFTER SCORING
	spaceBallMove.setFont(font);
	spaceBallMove.setCharacterSize(30);
	spaceBallMove.setPosition(685, 610);
	spaceBallMove.setString("Press SPACE to Move The Ball");

	//OBJECTS;;
	CircleShape pongBall;

	pongBall.setRadius(15);
	pongBall.setOrigin(15, 15);
	pongBall.setPosition(670, 330);
	pongBall.setFillColor(Color::Yellow);
	float yVelocityBall = 6;
	float xVelocityBall = 8;
	float xBallSpeedIncrease = 0.3;
	float yBallSpeedIncrease = 0.4;

	RectangleShape midLine[6];

	midLine[0].setFillColor(Color::Magenta);
	midLine[0].setSize(Vector2f(5, 75));
	midLine[0].setPosition(670, 0);

	midLine[1].setFillColor(Color::Magenta);
	midLine[1].setSize(Vector2f(5, 75));
	midLine[1].setPosition(669, 117);

	midLine[2].setFillColor(Color::Magenta);
	midLine[2].setSize(Vector2f(5, 75));
	midLine[2].setPosition(669, 234);

	midLine[3].setFillColor(Color::Magenta);
	midLine[3].setSize(Vector2f(5, 75));
	midLine[3].setPosition(669, 351);

	midLine[4].setFillColor(Color::Magenta);
	midLine[4].setSize(Vector2f(5, 75));
	midLine[4].setPosition(669, 468);

	midLine[5].setFillColor(Color::Magenta);
	midLine[5].setSize(Vector2f(5, 75));
	midLine[5].setPosition(669, 585);

	RectangleShape player1;

	player1.setSize(Vector2f(15, 90));
	player1.setFillColor(Color::Blue);
	player1.setOrigin(Vector2f(7.5, 45));
	player1.setPosition(Vector2f(1332, 330));
	float yVelocityPlayer1 = 10;

	RectangleShape player2;

	player2.setSize(Vector2f(15, 90));
	player2.setFillColor(Color::Red);
	player2.setOrigin(Vector2f(7.5, 45));
	player2.setPosition(Vector2f(8, 330));
	float yVelocityPlayer2 = 10;

	RectangleShape cpuPlayer;

	cpuPlayer.setSize(Vector2f(15, 90));
	cpuPlayer.setFillColor(Color::Red);
	cpuPlayer.setOrigin(Vector2f(7.5, 45));
	cpuPlayer.setPosition(Vector2f(8.0, 330));
	float yVelocitycpuPlayer = 0;

	//GAME LOOP
	while (window.isOpen())

	{
		if (gameTime.asSeconds() - elapsed.asSeconds() >= 0)

		{

			//GAMEPLAY CHECK
			if (playerChoice == true && modeChoice == true && paused == false && (player1Won == false && player2Won == false && cpuWon == false))

			{

				//EVENTS LOOP
				while (window.pollEvent(evnt))

				{
					if (evnt.type == Event::Closed)

					{
						window.close();
					}

					if (evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::Up)

					{
						upKeyPressed = true;
					}

					if (evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::Down)

					{
						downKeyPressed = true;
					}

					if (evnt.type == Event::KeyReleased && evnt.key.code == Keyboard::Up)

					{
						upKeyPressed = false;
					}

					if (evnt.type == Event::KeyReleased && evnt.key.code == Keyboard::Down)

					{
						downKeyPressed = false;
					}

					if (player2On == true)

					{
						if (evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::W)

						{
							wKeyPressed = true;
						}

						if (evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::S)

						{
							sKeyPressed = true;
						}

						if (evnt.type == Event::KeyReleased && evnt.key.code == Keyboard::W)

						{
							wKeyPressed = false;
						}

						if (evnt.type == Event::KeyReleased && evnt.key.code == Keyboard::S)

						{
							sKeyPressed = false;
						}
					}

					if (evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::Space)

					{
						ballMove = true;
					}

					if (evnt.type == Event::KeyPressed && evnt.key.code == Keyboard::Escape)

					{
						playerChoice = true;
						modeChoice = true;
						paused = true;
					}
				}

				//PLAYER MOVEMENT
				if (invertedMode == false)

				{
					if (upKeyPressed == true)

					{
						player1.move(Vector2f(0.0, -yVelocityPlayer1));
					}

					if (downKeyPressed == true)

					{
						player1.move(Vector2f(0.0, yVelocityPlayer1));
					}

					if (upKeyPressed == true && downKeyPressed == true)

					{
						player1.move(Vector2f(0.0, 0.0));
					}

					if (mouseMode == true)

					{
						player1.setPosition(1332, Mouse::getPosition().y);
					}

					if (player2On == true)

					{
						if (wKeyPressed == true)

						{
							player2.move(Vector2f(0.0, -yVelocityPlayer2));
						}

						if (sKeyPressed == true)

						{
							player2.move(Vector2f(0.0, yVelocityPlayer2));
						}

						if (wKeyPressed == true && sKeyPressed == true)

						{
							player2.move(Vector2f(0.0, 0.0));
						}
					}
				}

				if (invertedMode == true)

				{
					if (upKeyPressed == true)

					{
						player1.move(Vector2f(0.0, yVelocityPlayer1));
					}

					if (downKeyPressed == true)

					{
						player1.move(Vector2f(0.0, -yVelocityPlayer1));
					}

					if (upKeyPressed == true && downKeyPressed == true)

					{
						player1.move(Vector2f(0.0, 0.0));
					}

					if (player2On == true)

					{
						if (wKeyPressed == true)

						{
							player2.move(Vector2f(0.0, yVelocityPlayer2));
						}

						if (sKeyPressed == true)

						{
							player2.move(Vector2f(0.0, -yVelocityPlayer2));
						}

						if (wKeyPressed == true && sKeyPressed == true)

						{
							player2.move(Vector2f(0.0, 0.0));
						}
					}
				}

				//AI MOVEMENT
				if (player2On == false)

				{
					if (pongBall.getPosition().y < cpuPlayer.getPosition().y)

					{
						yVelocitycpuPlayer = -10;
					}

					if (pongBall.getPosition().y > cpuPlayer.getPosition().y)

					{
						yVelocitycpuPlayer = 10;
					}

					cpuPlayer.move(0, yVelocitycpuPlayer);
				}

				//PLAYER COLLISION WITH ROOF AND FLOOR
				if (warpMode == false)

				{
					if (player1.getPosition().y < 45)

					{
						player1.setPosition(1332, 45);
					}

					if (player1.getPosition().y > 615)

					{
						player1.setPosition(1332, 615);
					}

					if (player2On == true)

					{
						if (player2.getPosition().y < 45)

						{
							player2.setPosition(8, 45);
						}

						if (player2.getPosition().y > 615)

						{
							player2.setPosition(8, 615);
						}
					}

					if (player2On == false)

					{
						if (cpuPlayer.getPosition().y < 45)

						{
							cpuPlayer.setPosition(8, 45);
						}

						if (cpuPlayer.getPosition().y > 615)

						{
							cpuPlayer.setPosition(8, 615);
						}
					}
				}

				if (warpMode == true)

				{
					if (player1.getPosition().y < -45)

					{
						player1.setPosition(1332, 705);
					}

					if (player1.getPosition().y > 705)

					{
						player1.setPosition(1332, -45);
					}

					if (player2On == true)

					{
						if (player2.getPosition().y < -45)

						{
							player2.setPosition(8, 705);
						}

						if (player2.getPosition().y > 705)

						{
							player2.setPosition(8, -45);
						}
					}

					if (player2On == false)

					{
						if (cpuPlayer.getPosition().y < -45)

						{
							cpuPlayer.setPosition(8, 705);
						}

						if (cpuPlayer.getPosition().y > 705)

						{
							cpuPlayer.setPosition(8, -45);
						}
					}
				}

				//BALL MOVEMENT
				if (ballMove == true)

				{
					pongBall.move(xVelocityBall, yVelocityBall);
				}

				//BALL COLLISION WITH ROOF AND FLOOR
				if (pongBall.getPosition().y > 645)

				{
					yVelocityBall = -yVelocityBall;
					roofFloorHit.play();
				}

				if (pongBall.getPosition().y < 15)

				{
					yVelocityBall = -yVelocityBall;
					roofFloorHit.play();
				}

				//BALL OUT OF BOUNDS SCORING SYSTEM
				if (pongBall.getPosition().x < -15)

				{
					goalScore.play();
					player1Score++;
					pongBall.setPosition(670, 330 + (player1Score * player1Score) / 2);
					xVelocityBall = -8;
					yVelocityBall = 6;
					ballMove = false;
				}

				if (pongBall.getPosition().x > 1355)

				{
					goalScore.play();
					player2Score++;
					pongBall.setPosition(670, 330 - (player2Score * player2Score) / 2);
					xVelocityBall = 8;
					yVelocityBall = 6;
					ballMove = false;
				}

				//BALL COLLISION WITH PLAYER
				if (pongBall.getGlobalBounds().intersects(player1.getGlobalBounds()) == true)

				{
					xVelocityBall = -xVelocityBall;

					if (xVelocityBall > 0)

					{
						xVelocityBall += xBallSpeedIncrease;
					}

					if (xVelocityBall < 0)

					{
						xVelocityBall -= xBallSpeedIncrease;
					}

					if (yVelocityBall > 0)

					{
						yVelocityBall += yBallSpeedIncrease;
					}

					if (yVelocityBall < 0)

					{
						yVelocityBall -= yBallSpeedIncrease;
					}

					player1Hit.play();
				}

				if (player2On == true)

				{
					if (pongBall.getGlobalBounds().intersects(player2.getGlobalBounds()) == true)

					{
						xVelocityBall = -xVelocityBall;

						if (xVelocityBall > 0)

						{
							xVelocityBall += xBallSpeedIncrease;
						}

						if (xVelocityBall < 0)

						{
							xVelocityBall -= xBallSpeedIncrease;
						}

						if (yVelocityBall > 0)

						{
							yVelocityBall += yBallSpeedIncrease;
						}

						if (yVelocityBall < 0)

						{
							yVelocityBall -= yBallSpeedIncrease;
						}

						player2Hit.play();
					}
				}

				if (player2On == false)

				{
					if (pongBall.getGlobalBounds().intersects(cpuPlayer.getGlobalBounds()) == true)

					{
						xVelocityBall = -xVelocityBall;

						if (xVelocityBall > 0)

						{
							xVelocityBall += xBallSpeedIncrease;
						}

						if (xVelocityBall < 0)

						{
							xVelocityBall -= xBallSpeedIncrease;
						}

						if (yVelocityBall > 0)

						{
							yVelocityBall += yBallSpeedIncrease;
						}

						if (yVelocityBall < 0)

						{
							yVelocityBall -= yBallSpeedIncrease;
						}

						cpuPlayerHit.play();
					}
				}

				if ((player1Score == 1 && player2Score == 0) || (player2Score == 1 && player1Score == 0))

				{
					firstScore = true;
				}

				if (player2On == true)

				{
					if (player1Score == 11 && player2Score < 11)

					{
						player1Won = true;
						player1Wins.play();
					}

					if (player2Score == 11 && player1Score < 11)

					{
						player2Won = true;
						player2Wins.play();
					}
				}

				if (player2On == false)

				{
					if (player1Score == 11 && player2Score < 11)

					{
						player1Won = true;
						player1Wins.play();
					}

					if (player2Score == 11 && player1Score < 11)

					{
						cpuWon = true;
						losing.play();
					}
				}
			}
		}

		else if (gameTime.asSeconds() - elapsed.asSeconds() < 0)

		{

			if (player2On == true)

			{
				if (player1Score > player2Score)

				{
					player1Won = true;
				}

				if (player2Score > player1Score)

				{
					player2Won = true;
				}

				if (player1Score == player2Score)

				{
					drawGame = true;
				}
			}

			if (player2On == false)

			{
				if (player1Score > player2Score)

				{
					player1Won = true;
				}

				if (player2Score > player1Score)

				{
					cpuWon = true;
				}

				if (player1Score == player2Score)

				{
					drawGame = true;
				}
			}
		}

		//CONTINUING AFTER GAME
		if (player1Won == true || player2Won == true || cpuWon == true || drawGame == true)

		{
			while (window.pollEvent(evnt))

			{
				if (evnt.type == Event::KeyPressed)

				{
					player1Won = false;
					player2Won = false;
					cpuWon = false;
					drawGame = false;
					playerChoice = false;
					modeChoice = false;
					ballMove = true;
					player1.setPosition(Vector2f(1332, 330));
					player2.setPosition(Vector2f(8, 330));
					cpuPlayer.setPosition(Vector2f(8, 330));
				}

				if (evnt.type == Event::Closed)

				{
					window.close();
				}
			}
		}

		//RENDERING TO THE SCREEN
		window.clear();

		//MIDLINE
		if (playerChoice == true && modeChoice == true && paused == false && (player1Won == false && player2Won == false && cpuWon == false && drawGame == false))

		{

			for (int i = 0; i < 6; i++)

			{
				window.draw(midLine[i]);
			}
		}

		if (playerChoice == true && modeChoice == true && paused == true)

		{
			for (int i = 0; i < 6; i++)

			{
				if (i == 2)

				{
					continue;
				}

				window.draw(midLine[i]);
			}
		}

		//OBJECTS
		if (playerChoice == true && modeChoice == true && paused == false && (player1Won == false && player2Won == false && cpuWon == false && drawGame == false))

		{
			window.draw(pongBall);
			window.draw(player1);

			if (player2On == true)

			{
				window.draw(player2);
			}

			if (player2On == false)

			{
				window.draw(cpuPlayer);
			}
		}

		//MAIN MENU
		if (playerChoice == false && modeChoice == false && paused == false && (player1Won == false && player2Won == false && cpuWon == false && drawGame == false))

		{
			mainMenu.draw(window);

			//MAIN MENU EVENTS LOOP
			while (window.pollEvent(mainMenuEvent))

			{
				if (mainMenuEvent.type == Event::KeyPressed && mainMenuEvent.key.code == Keyboard::Up)

				{
					mainMenu.moveUp();
					menuMovement.play();
					break;
				}

				if (mainMenuEvent.type == Event::KeyPressed && mainMenuEvent.key.code == Keyboard::Down)

				{
					mainMenu.moveDown();
					menuMovement.play();
					break;
				}

				if (mainMenuEvent.type == Event::KeyPressed && mainMenuEvent.key.code == Keyboard::Return)

				{
					mainMenu.getSelectedItem();

					if (mainMenu.getSelectedItem() == 0)

					{
						player2On = false;
						playerChoice = true;
						modeChoice = false;
						menuSelection.play();
						break;
					}

					if (mainMenu.getSelectedItem() == 1)

					{
						player2On = true;
						playerChoice = true;
						modeChoice = false;
						menuSelection.play();
						break;
					}

					if (mainMenu.getSelectedItem() == 2)

					{
						window.close();
					}

					break;
				}

				if (mainMenuEvent.type == Event::Closed)

				{
					window.close();
				}
			}
		}

		//MODE MENU
		if (playerChoice == true && modeChoice == false && paused == false && (player1Won == false && player2Won == false && cpuWon == false && drawGame == false))

		{
			modeMenu.draw2(window);

			//MODE MENU EVENTS LOOP
			while (window.pollEvent(modeMenuEvent))

			{
				if (modeMenuEvent.type == Event::KeyPressed && modeMenuEvent.key.code == Keyboard::Up)

				{
					modeMenu.moveUp2();
					menuMovement.play();
					break;
				}

				if (modeMenuEvent.type == Event::KeyPressed && modeMenuEvent.key.code == Keyboard::Down)

				{
					modeMenu.moveDown2();
					menuMovement.play();
					break;
				}

				if (modeMenuEvent.type == Event::KeyPressed && modeMenuEvent.key.code == Keyboard::Escape)

				{
					modeChoice = false;
					playerChoice = false;
					break;
				}

				if (modeMenuEvent.type == Event::KeyPressed && modeMenuEvent.key.code == Keyboard::Return)

				{
					gameClock.restart();
					modeMenu.getSelectedItem2();

					if (modeMenu.getSelectedItem2() == 0)

					{
						mouseMode = false;
						warpMode = false;
						invertedMode = false;
						modeChoice = true;
						menuSelection.play();
						break;
					}

					if (modeMenu.getSelectedItem2() == 1)

					{
						mouseMode = true;
						warpMode = false;
						invertedMode = false;
						modeChoice = true;
						menuSelection.play();
						break;
					}

					if (modeMenu.getSelectedItem2() == 2)

					{
						warpMode = true;
						mouseMode = false;
						invertedMode = false;
						modeChoice = true;
						menuSelection.play();
						break;
					}

					if (modeMenu.getSelectedItem2() == 3)

					{
						invertedMode = true;
						warpMode = false;
						mouseMode = false;
						modeChoice = true;
						menuSelection.play();
						break;

					}

					if (modeMenu.getSelectedItem2() == 4)

					{
						playerChoice = false;
						modeChoice = false;
						menuSelection.play();
						break;
					}

					break;
				}

				if (modeMenuEvent.type == Event::Closed)

				{
					window.close();
				}
			}
		}

		//PAUSE MENU
		if (playerChoice == true && modeChoice == true && paused == true && (player1Won == false && player2Won == false && cpuWon == false && drawGame == false))

		{
			pauseMenu.draw3(window);

			//PAUSE MENU EVENTS LOOP
			while (window.pollEvent(pauseMenuEvent))

			{
				if (pauseMenuEvent.type == Event::KeyPressed && pauseMenuEvent.key.code == Keyboard::Up)

				{
					pauseMenu.moveUp3();
					menuMovement.play();
					break;
				}

				if (pauseMenuEvent.type == Event::KeyPressed && pauseMenuEvent.key.code == Keyboard::Down)

				{
					pauseMenu.moveDown3();
					menuMovement.play();
					break;
				}

				if (pauseMenuEvent.type == Event::KeyPressed && pauseMenuEvent.key.code == Keyboard::Escape)

				{
					paused = false;
					break;
				}

				if (pauseMenuEvent.type == Event::KeyPressed && pauseMenuEvent.key.code == Keyboard::Return)

				{
					pauseMenu.getSelectedItem3();

					if (pauseMenu.getSelectedItem3() == 0)

					{
						paused = false;
						menuSelection.play();
						break;
					}

					if (pauseMenu.getSelectedItem3() == 1)

					{
						player1Score = 0;
						player2Score = 0;
						paused = false;
						playerChoice = false;
						modeChoice = false;
						ballMove = true;
						pongBall.move(xVelocityBall, yVelocityBall);
						menuSelection.play();
						break;
					}
				}

				if (pauseMenuEvent.type == Event::Closed)

				{
					window.close();
				}
			}
		}

		//SCORE DISPLAY
		if ((playerChoice == false || modeChoice == false) && paused == false)

		{
			player1Score = 0;
			player2Score = 0;
			pongBall.setPosition(670, 330);
		}

		stringstream scoreDisplay;
		scoreDisplay << player2Score << "      " << player1Score;
		score.setString(scoreDisplay.str());

		//TIME DISPLAY
		stringstream timeDisplay;
		timeDisplay << "Time Remaining : " << gameTime.asSeconds() - elapsed.asSeconds();
		time.setString(timeDisplay.str());

		if (playerChoice == true && modeChoice == true && (player1Won == false && player2Won == false && cpuWon == false && drawGame == false))

		{
			window.draw(time);
		}

		if (playerChoice == true && modeChoice == true)

		{
			window.draw(score);
		}

		if (firstScore == true && paused == false && playerChoice == true && modeChoice == true && ballMove == false)

		{
			window.draw(spaceBallMove);
		}

		if (player1Won == true)

		{
			window.draw(midLine[0]);
			window.draw(player1WinMessage);
			window.draw(continueMessage);
		}

		if (player2Won == true)

		{
			window.draw(midLine[0]);
			window.draw(player2WinMessage);
			window.draw(continueMessage);
		}

		if (cpuWon == true)

		{
			window.draw(midLine[0]);
			window.draw(cpuWinMessage);
			window.draw(continueMessage);
		}

		if (drawGame == true)

		{
			window.draw(drawMessage);
			window.draw(continueMessage);
		}

		window.display();
	}

	//CLOSING THE WINDOW
	window.close();

	return 0;
}