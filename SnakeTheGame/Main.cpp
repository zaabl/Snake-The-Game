#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML\Audio.hpp>
#include <string>
#include <cstdlib>
#include <ctime>

#define scaleX = 32;
#define scaleY = 24;

using namespace std;
using namespace sf;

struct Snake
{
	RectangleShape head;
	int length = 3;
	Vector2f lastPosition;
	string currentDirection;
	string pastDirection;
	int x = 16, y = 12;
	RectangleShape body[660];
	string bodyPastDirection[660];
	Vector2f BodylastPosition[660];
};

RectangleShape point(Vector2f(32.0f,24.0f));
Texture appleTex;

SoundBuffer pointSoundBuffer;
Sound pointSound;
sf::RenderWindow window(sf::VideoMode(1024, 768), "Snake");
bool mainMenu = true, start = false, settings = false, pause = false, gameover = false;
RectangleShape backGround(Vector2f(1024.0f, 768.0f));
Texture backGroundTexture;
RectangleShape mapbg(Vector2f(1024.0f, 768.0f));
Texture mapbackGroundTexture;
Text menuTxt[5];
Font menuFont;
int selectionCount = 0;
SoundBuffer selectionSoundBuffer;
Sound selectionSound;
Snake snake;
SoundBuffer backGroundThemeBuffer;
Sound backGroundTheme;
SoundBuffer selectedSoundBuffer;
Sound selectedSound;
Texture headRight; Texture tailRight;
Texture headLeft; Texture tailLeft;
Texture headUp; Texture tailUp;
Texture headDown; Texture tailDown;
Texture bodyVertical;
Texture bodyHorizontal;
bool called = false;
Text gameText[5]; // 0 Press 'P' to start. 1 Paused!. 2 Gameover!. 3 Your Score is. 4 You win.
int mape[24][32] = {
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
void generatePoint()
{
	if (!called)
	{
		srand(time(NULL));
		called = true;
	}
	int randomX = (rand() % 23) + 1;
	int randomY = (rand() % 31) + 1;
	cout << randomX << " " << randomY;
	if (mape[randomY][randomX] == 1)
	{
		generatePoint();
	}
	else
	{
		point.setPosition(32 * randomX, 24 * randomY);
		mape[randomY][randomX] = 2;
	}
}
void mainMenuSetup()
{
	//================BackGround================
	//==========================================

	backGroundTexture.loadFromFile("bg.jpg");
	backGround.setTexture(&backGroundTexture);
	menuFont.loadFromFile("Future TimeSplitters.otf");
	menuTxt[0].setFont(menuFont);
	menuTxt[0].setString("Snake The Game");
	menuTxt[0].setCharacterSize(160);
	menuTxt[0].setPosition(170, 50);
	selectionSoundBuffer.loadFromFile("selectSound.wav");
	selectionSound.setBuffer(selectionSoundBuffer);
	backGroundThemeBuffer.loadFromFile("menuTheme.wav");
	backGroundTheme.setBuffer(backGroundThemeBuffer);
	selectedSoundBuffer.loadFromFile("selected.wav");
	selectedSound.setBuffer(selectedSoundBuffer);

	//================Start================
	//==========================================

	menuTxt[1].setFont(menuFont);
	menuTxt[1].setString("Start");
	menuTxt[1].setCharacterSize(70);
	menuTxt[1].setPosition(440, 320);

	//================Settings================
	//==========================================

	menuTxt[2].setFont(menuFont);
	menuTxt[2].setString("Settings");
	menuTxt[2].setCharacterSize(70);
	menuTxt[2].setPosition(415, 420);

	//================HighSores================
	//==========================================

	menuTxt[3].setFont(menuFont);
	menuTxt[3].setString("HighScores");
	menuTxt[3].setCharacterSize(70);
	menuTxt[3].setPosition(400, 520);

	//================Quit================
	//==========================================

	menuTxt[4].setFont(menuFont);
	menuTxt[4].setString("Quit");
	menuTxt[4].setCharacterSize(70);
	menuTxt[4].setPosition(450, 620);
}
void updateMainMenu(int selection)
{
	selectionSound.play();
	cout << selectionCount << endl;
	if (selection == 1)
	{
		menuTxt[1].setFillColor(Color::Black);
		menuTxt[2].setFillColor(Color::White);
		menuTxt[4].setFillColor(Color::White);
	}
	else if (selection == 2)
	{
		menuTxt[2].setFillColor(Color::Black);
		menuTxt[1].setFillColor(Color::White);
		menuTxt[3].setFillColor(Color::White);
	}
	else if (selection == 3)
	{
		menuTxt[3].setFillColor(Color::Black);
		menuTxt[2].setFillColor(Color::White);
		menuTxt[4].setFillColor(Color::White);
	}
	else if (selection == 4)
	{
		menuTxt[4].setFillColor(Color::Black);
		menuTxt[3].setFillColor(Color::White);
		menuTxt[1].setFillColor(Color::White);
	}
}
string selection()
{
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		if (selectionCount == 4)
		{
			selectionCount = 1;
		}
		else
		{
			selectionCount++;
		}
		updateMainMenu(selectionCount);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		if (selectionCount == 1)
		{
			selectionCount = 4;
		}
		else
		{
			selectionCount--;
		}
		updateMainMenu(selectionCount);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Space))
	{	
		backGroundTheme.stop();
		selectedSound.play();

		if (selectionCount == 4) 
		{
			return "Quit";
		}
		else if (selectionCount == 1)
		{
			return "start";
		}
	}

	return "NothingSelected";
}
void snakeSetup()
{
	snake.head.setSize(Vector2f(32.0f, 24.0f));
	snake.head.setFillColor(Color::Cyan);
	snake.head.setPosition(512, 384);
	snake.lastPosition.x = 480;
	snake.lastPosition.y = 360;
	snake.currentDirection = "Right";
	
	snake.body[0].setPosition(480, 384);
	snake.body[1].setPosition(448, 384);
	snake.body[2].setPosition(416, 384);

	headRight.loadFromFile("headRight.png"); tailRight.loadFromFile("tailRight.png");
	headLeft.loadFromFile("headLeft.png"); tailLeft.loadFromFile("tailLeft.png");
	headUp.loadFromFile("headUp.png"); tailUp.loadFromFile("tailUp.png");
	headDown.loadFromFile("headDown.png"); tailDown.loadFromFile("tailDown.png");
	bodyHorizontal.loadFromFile("bodyH.png");
	bodyVertical.loadFromFile("bodyV.png");

	for (int i = 0; i < snake.length; i++)
	{	
		snake.body[i].setSize(Vector2f(32.0f, 24.0f));
		snake.body[i].setFillColor(Color::Green);
	}
	
}
void mapUpdate()
{
	snake.y = snake.head.getPosition().y / 24;
	snake.x = snake.head.getPosition().x / 32;
	mape[snake.y][snake.x] = 1;
	
	if (snake.head.getPosition() == point.getPosition())
	{
		cout << "yes";
		pointSound.play();
		generatePoint();
		snake.body[snake.length].setSize(Vector2f(32.0f, 24.0f));
		snake.body[snake.length].setFillColor(Color::Green);
		snake.body[snake.length].setPosition(snake.BodylastPosition[snake.length-1]);
		snake.length++;
		
	}
}
void movement()
{
	snake.lastPosition = snake.head.getPosition();

	if (snake.currentDirection == "Up")
	{	
		snake.head.setTexture(&headUp);
		snake.pastDirection = "Up";
		if (snake.head.getPosition().y == 0)
		{
			snake.head.setPosition(snake.head.getPosition().x, 744);
		}
		else {
			snake.head.move(0, -24);
		}
	}
	else if (snake.currentDirection == "Down")
	{
		snake.head.setTexture(&headDown);
		snake.pastDirection = "Down";
		if (snake.head.getPosition().y == 744)
		{
			snake.head.setPosition(snake.head.getPosition().x, 0);
		}
		else {
			snake.head.move(0, 24);
		}
	}
	else if (snake.currentDirection == "Right")
	{	
		snake.head.setTexture(&headRight);
		snake.pastDirection = "Right";
		if (snake.head.getPosition().x == 992)
		{
			snake.head.setPosition(0, snake.head.getPosition().y);
		}
		else {
			snake.head.move(32, 0);
		}
	}
	else if (snake.currentDirection == "Left")
	{
		snake.head.setTexture(&headLeft);
		snake.pastDirection = "Left";
		if (snake.head.getPosition().x == 0)
		{
			snake.head.setPosition(992, snake.head.getPosition().y);
		}
		else {
			snake.head.move(-32, 0);
		}
	}

	snake.y = snake.head.getPosition().y / 24;
	snake.x = snake.head.getPosition().x / 32;

	if (mape[snake.y][snake.x] == 1)
	{
		gameover = true;
	}

	snake.BodylastPosition[0] = snake.body[0].getPosition();
	snake.body[0].setPosition(snake.lastPosition);
	snake.bodyPastDirection[0] = snake.pastDirection;
	snake.body[0].setFillColor(Color::Color(45,196,136));
	for (int i = 1; i < snake.length; i++)
	{
		snake.BodylastPosition[i] = snake.body[i].getPosition();
		snake.body[i].setPosition(snake.BodylastPosition[i - 1]);
		snake.bodyPastDirection[i] = snake.bodyPastDirection[i - 1];
		snake.body[i].setFillColor(Color::Color::Color(45, 196, 136));
		int pointX = snake.body[i].getPosition().x / 32;
		int pointY = snake.body[i].getPosition().y / 24;
		mape[pointY][pointX] = 1;
	}
	int pointX = snake.body[snake.length - 1].getPosition().x / 32;
	int pointY = snake.body[snake.length - 1].getPosition().y / 24;
	mape[pointY][pointX] = 0;
}
void movementDetector()
{
	if (Keyboard::isKeyPressed(Keyboard::Up) && snake.pastDirection != "Down")
	{
		snake.currentDirection = "Up";
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && snake.pastDirection != "Up")
	{
		snake.currentDirection = "Down";
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && snake.pastDirection != "Left")
	{
		snake.currentDirection = "Right";
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && snake.pastDirection != "Right")
	{
		snake.currentDirection = "Left";
	}
	else if (Keyboard::isKeyPressed(Keyboard::P))
	{
		pause = true;
	}

}
void mapSetup()
{
	mapbackGroundTexture.loadFromFile("map.jpg");
	mapbg.setTexture(&mapbackGroundTexture);
	appleTex.loadFromFile("apple.png");
	point.setTexture(&appleTex);
	generatePoint();
	pointSoundBuffer.loadFromFile("point.wav");
	pointSound.setBuffer(pointSoundBuffer);
	for (int i = 0; i < 5; i++)
	{
		gameText[i].setFont(menuFont);
		gameText[i].setCharacterSize(160);
		gameText[i].setPosition(170, 250);
	}
	gameText[0].setString("Press 'P' to start");
	gameText[1].setString("Game Paused!");
	gameText[2].setString("Game Over");
	gameText[4].setString("You win!");
}
int main()
{
	mainMenuSetup();
	snakeSetup();
	mapSetup();
	bool firstTime = true;
	
	while (window.isOpen())
	{
		if (mainMenu)
		{
			backGroundTheme.play();
		}
		while (mainMenu)
		{
			Event event;
			while (window.pollEvent(event))
			{
				window.setFramerateLimit(60);
				if (event.type == sf::Event::Closed)
					window.close();
				//cout << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << endl;

				string selected = selection();
				if (selected == "Quit")
				{
					return 0;
				}
				else if (selected == "start")
				{
					start = true;
					mainMenu = false;
				}
		
			}

			window.clear();
			window.draw(backGround);
			for (int i = 0; i < 5; i++)
			{
				window.draw(menuTxt[i]);
			}
			/*window.draw(menuTxt[0]); window.draw(menuTxt[1]); window.draw(menuTxt[2]); window.draw(menuTxt[3]); window.draw(menuTxt[4]);*/
			window.display();
		}
		while (start)
		{	
			while (!pause)
			{
				mapUpdate();
				window.setFramerateLimit(10);
				Event event;
				while (window.pollEvent(event))
				{
					movementDetector();
				}
				movement();

				for (int i = 0; i < 24; i++)
				{
					for (int j = 0; j < 32; j++)
					{
						cout << mape[i][j];
					}
					cout << endl;
				}
				cout << endl << endl;
				window.clear();
				window.draw(mapbg);
				window.draw(snake.head);
				window.draw(point);
				for (int i = 0; i < snake.length; i++)
				{
					window.draw(snake.body[i]);
				}

				if(firstTime)
				{ 
					window.draw(gameText[0]);
					pause = true;
					firstTime = false;
				}
				if (gameover)
				{
					pause = true;
					gameText[2].setPosition(250, 250);
					window.draw(gameText[2]);
					gameText[3].setPosition(250, 450);
					//gametext[3].setstring("your score is " + snake.length * 40);
					window.draw(gameText[3]);
				}

				window.display();
			}
			if (pause)
			{
				window.draw(gameText[0]);
			}
			if (Keyboard::isKeyPressed(Keyboard::P))
				pause = false;

		}
		


		
	}

	return 0;
}