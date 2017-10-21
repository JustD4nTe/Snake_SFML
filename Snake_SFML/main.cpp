#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

#define SNAKE_SIZE 20

//void newFruit(sf::RenderWindow &win);

//unsigned int getNumberOfSnakeElements(sf::RectangleShape &win);
void Move(sf::RectangleShape* snake[], unsigned int length);
void Draw(sf::RenderWindow &win, sf::RectangleShape* snake[]);

unsigned int MoveCounter = 1;


int main(){
	sf::RenderWindow Window(sf::VideoMode(500, 500), "SFML works!");
	//sf::RectangleShape snake(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
	sf::RectangleShape* SnakeElements[625];
	SnakeElements[0] = new sf::RectangleShape(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
	SnakeElements[0]->setPosition(Window.getSize().x / 2, Window.getSize().y / 2);

	for (int i = 1; i < 7; i++) {
		SnakeElements[i] = new sf::RectangleShape(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
		SnakeElements[i]->setPosition(SnakeElements[i - 1]->getPosition().x, SnakeElements[i - 1]->getPosition().y + 20);
		SnakeElements[i]->setFillColor(sf::Color(32 * i, 16 * i, 8 * i));
	}

	sf::Clock timer;


	unsigned int SnakeLength = 6;
	unsigned int Direction = 1;
	

	float SnakeNextMove = 500, SnakeMoveTimeCounter = 0, SnakeSpeed = 800;

	while (Window.isOpen())	{
		sf::Event event;
		while (Window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				Window.close();

			if (event.key.code == sf::Keyboard::Escape)
				Window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			Direction = 1;
		
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			Direction = 2;

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			Direction = 3;

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			Direction = 4;


		SnakeMoveTimeCounter += SnakeSpeed * timer.restart().asSeconds();

		if (SnakeMoveTimeCounter >= SnakeNextMove) {
			switch (Direction){
			case 1:
				++MoveCounter;
				Move(SnakeElements, SnakeLength);
				SnakeElements[0]->move(0, -SNAKE_SIZE);	//	UP
				//newFruit(window);
				break;
			case 2:
				++MoveCounter;
				Move(SnakeElements, SnakeLength);
				SnakeElements[0]->move(0, SNAKE_SIZE);	//	DOWN
				//newFruit(window);
				break;
			case 3:
				++MoveCounter;
				Move(SnakeElements, SnakeLength);
				SnakeElements[0]->move(-SNAKE_SIZE, 0);	//	LEFT
				//newFruit(window);
				break;
			case 4:
				++MoveCounter;
				Move(SnakeElements, SnakeLength);
				SnakeElements[0]->move(SNAKE_SIZE, 0);	//	RIGHT
				//newFruit(window);
				break;
			default:
				++MoveCounter;
				break;
			}

			SnakeMoveTimeCounter = 0;
		}

		Window.clear();
		//Window.draw(SnakeElements);
		Draw(Window, &SnakeElements[0]);
		Window.display();
	}

	return 0;
}

//
//unsigned int getNumberOfSnakeElements(sf::RectangleShape &win) {
//	return ((win.getSize().x / 20) * (win.getSize().y / 20));
//}

//void newFruit(sf::RenderWindow &win) {
//	srand(static_cast<unsigned int>(time(NULL)));
//
//	unsigned int x = (rand() % (win.getSize().x / 20) + 0) * 20;
//	unsigned int y = (rand() % (win.getSize().y / 20) + 0) * 20;
//
//	std::cout << "x: " << x << " y: " << y << std::endl;
//}

void Move(sf::RectangleShape* snake[], unsigned int length) {
	for (unsigned int i = length; i > 0; i--)
		snake[i]->setPosition(snake[i - 1]->getPosition());
}

void Draw(sf::RenderWindow &win, sf::RectangleShape* snake[]) {
	for (int i = 0; i < 7; i++)
		win.draw(*snake[i]);
}