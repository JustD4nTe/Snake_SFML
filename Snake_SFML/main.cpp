#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

#define SNAKE_SIZE 20


// Window size
#define RES_X 500
#define RES_Y 500

// Snake start posision
#define SNAKE_X 260
#define SNAKE_Y 260

#define RED 20
#define GREEN 10
#define BLUE 20

sf::Vector2f GeneratePositionForNewFruit(const sf::RenderWindow &win);

void Move(sf::RectangleShape* snake[], const unsigned length);
void Draw(sf::RenderWindow &win, sf::RectangleShape* snake[], const unsigned length);
bool Collision(sf::RectangleShape* snake[], const unsigned length);

int main() {
	sf::RenderWindow Window(sf::VideoMode(RES_X, RES_Y), "Snake by JustD4nTe");
	sf::RectangleShape* SnakeElements[624];
	sf::RectangleShape Fruit(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
	sf::Clock timer;

	const uint32_t fruitColor = 0xFF6633;

	unsigned int SnakeLength = 1;
	unsigned int Direction = 1;

	unsigned int Green = 60, GreenCounter = 1;
	// When Green was changed more than 20 times
	// its goes darker or lighter (oppositly compare with last changing)
	bool isReverseGreen = false;

	float SnakeNextMove = 100, SnakeMoveTimeCounter = 0, SnakeSpeed = 400;

	// Create head of snake
	SnakeElements[0] = new sf::RectangleShape(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
	SnakeElements[0]->setPosition(SNAKE_X, SNAKE_Y);

	Fruit.setFillColor(sf::Color(fruitColor));
	Fruit.setPosition(GeneratePositionForNewFruit(Window));

	while (Window.isOpen()) {
		if (Collision(&SnakeElements[0], SnakeLength))
			break;


		sf::Event event;
		while (Window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				Window.close();

			if (event.key.code == sf::Keyboard::Escape)
				Window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (Direction != 2)
				Direction = 1;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (Direction != 1)
				Direction = 2;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (Direction != 4)
				Direction = 3;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (Direction != 3)
				Direction = 4;
		}


		SnakeMoveTimeCounter += SnakeSpeed * timer.restart().asSeconds();
		// Moving
		if (SnakeMoveTimeCounter >= SnakeNextMove) {
			if (SnakeLength > 1)
				Move(SnakeElements, SnakeLength);

			switch (Direction) {
			case 1:
				SnakeElements[0]->move(0, -SNAKE_SIZE);	//	UP
				break;
			case 2:
				SnakeElements[0]->move(0, SNAKE_SIZE);	//	DOWN
				break;
			case 3:
				SnakeElements[0]->move(-SNAKE_SIZE, 0);	//	LEFT
				break;
			case 4:
				SnakeElements[0]->move(SNAKE_SIZE, 0);	//	RIGHT
				break;
			default:
				break;
			}

			SnakeMoveTimeCounter = 0;
		}
		// Eating a fruit
		if (Fruit.getPosition() == SnakeElements[0]->getPosition()) {
			Fruit.setPosition(GeneratePositionForNewFruit(Window));

			SnakeElements[SnakeLength] = new sf::RectangleShape(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
			SnakeElements[SnakeLength]->setPosition(SnakeElements[SnakeLength - 1]->getPosition().x, SnakeElements[SnakeLength - 1]->getPosition().y);
			
			if (GreenCounter == 20) {
				isReverseGreen = (isReverseGreen ? false : true);
				GreenCounter = 1;
			}

			if (isReverseGreen)
				Green = (255 - (GREEN * GreenCounter++));
			else
				Green = (GREEN * GreenCounter++) + 60;

			SnakeElements[SnakeLength]->setFillColor(sf::Color(RED, Green, BLUE));
			++SnakeLength;
		}

		Window.clear();
		Draw(Window, &SnakeElements[0], SnakeLength);
		Window.draw(Fruit);
		Window.display();
	}

	sf::RenderWindow WinEndGame(sf::VideoMode(400, 100), "KONIEC GRY");

	sf::Text text;
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "NOT FONT";
	
	std::string strEndGame("Wynik:\n");
	strEndGame.append(std::to_string(SnakeLength - 1));
	strEndGame.append("\nKliknij klawisz Esc aby wyjsc...");
	
	text.setFont(font); 
	text.setString(strEndGame);
	text.setCharacterSize(24); 
	text.setFillColor(sf::Color::White);

	while (WinEndGame.isOpen()) {
		sf::Event event;
		while (WinEndGame.pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
				WinEndGame.close();
				Window.close();
			}
		}
		WinEndGame.draw(text);
		WinEndGame.display();
	}
	return 0;
}

sf::Vector2f GeneratePositionForNewFruit(const sf::RenderWindow &win) {
	srand(static_cast<unsigned int>(time(NULL)));

	unsigned x = (rand() % (win.getSize().x / 20) + 0) * 20;
	unsigned y = (rand() % (win.getSize().y / 20) + 0) * 20;

	return sf::Vector2f(x, y);
}

void Move(sf::RectangleShape* snake[],const unsigned int length) {
	for (unsigned int i = length - 1 ; i > 0; --i)
		snake[i]->setPosition(snake[i - 1]->getPosition());
}

void Draw(sf::RenderWindow &win, sf::RectangleShape* snake[], const unsigned int length) {
	for (unsigned int i = 1; i <= length; ++i)
		win.draw(*snake[length - i]);
}

bool Collision(sf::RectangleShape* snake[], const unsigned int length) {
	sf::RectangleShape HeadOfSnake = *snake[0];
	if (HeadOfSnake.getPosition().x >= RES_X || HeadOfSnake.getPosition().x < 0 || HeadOfSnake.getPosition().y >= RES_Y || HeadOfSnake.getPosition().y < 0)
		return true;

	for (unsigned int i = 2; i < length; i++) {
		if (HeadOfSnake.getPosition() == snake[i]->getPosition())
			return true;
	}

	return false;
}