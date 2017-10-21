#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>

#define SNAKE_SIZE 20

sf::Vector2f newFruit(sf::RenderWindow &win);

void Move(sf::RectangleShape* snake[], unsigned int length);
void Draw(sf::RenderWindow &win, sf::RectangleShape* snake[], unsigned int length);


int main(){
	sf::RenderWindow Window(sf::VideoMode(500, 500), "SFML works!");
	sf::RectangleShape* SnakeElements[624];
	sf::RectangleShape Fruit(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
	sf::Clock timer;
	
	unsigned int SnakeLength = 1;
	unsigned int Direction = 1;
	
	float SnakeNextMove = 500, SnakeMoveTimeCounter = 0, SnakeSpeed = 800;

	SnakeElements[0] = new sf::RectangleShape(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
	SnakeElements[0]->setPosition(260, 260);

	//for (int i = 1; i < 2; i++) {
	//	SnakeElements[i] = new sf::RectangleShape(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
	//	SnakeElements[i]->setPosition(SnakeElements[i - 1]->getPosition().x, SnakeElements[i - 1]->getPosition().y + 20);
	//	SnakeElements[i]->setFillColor(sf::Color(16 * i, 16 * i, 8 * i));
	//}

	Fruit.setFillColor(sf::Color(0xFF, 0x66, 0x33));
	Fruit.setPosition(newFruit(Window));

	while (Window.isOpen())	{
		if (Fruit.getPosition() == SnakeElements[0]->getPosition()) {
			Fruit.setPosition(newFruit(Window));
			++SnakeLength;
			SnakeElements[SnakeLength - 1] = new sf::RectangleShape(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
			SnakeElements[SnakeLength - 1]->setPosition(SnakeElements[SnakeLength - 2]->getPosition().x, SnakeElements[SnakeLength - 2]->getPosition().y);
			SnakeElements[SnakeLength - 1]->setFillColor(sf::Color(5 * SnakeLength, 10 * SnakeLength, 1 * SnakeLength));
 		}

		sf::Event event;
		while (Window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				Window.close();

			if (event.key.code == sf::Keyboard::Escape)
				Window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (Direction != 2) {
				Direction = 1;
			}
		}
		
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (Direction != 1) {
				Direction = 2;
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (Direction != 4) {
				Direction = 3;
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (Direction != 3) {
				Direction = 4;
			}
		}


		SnakeMoveTimeCounter += SnakeSpeed * timer.restart().asSeconds();

		if (SnakeMoveTimeCounter >= SnakeNextMove) {
			if(SnakeLength > 1)
				Move(SnakeElements, SnakeLength);

			switch (Direction){
			case 1:
				SnakeElements[0]->move(0, -SNAKE_SIZE);	//	UP
				//newFruit(window);
				break;
			case 2:
				SnakeElements[0]->move(0, SNAKE_SIZE);	//	DOWN
				//newFruit(window);
				break;
			case 3:
				SnakeElements[0]->move(-SNAKE_SIZE, 0);	//	LEFT
				//newFruit(window);
				break;
			case 4:
				SnakeElements[0]->move(SNAKE_SIZE, 0);	//	RIGHT
				//newFruit(window);
				break;
			default:
				break;
			}


			SnakeMoveTimeCounter = 0;
		}

		Window.clear();
		Draw(Window, &SnakeElements[0], SnakeLength);
		Window.draw(Fruit);
		Window.display();
	}

	return 0;
}

sf::Vector2f newFruit(sf::RenderWindow &win) {
	srand(static_cast<unsigned int>(time(NULL)));

	unsigned int x = (rand() % (win.getSize().x / 20) + 0) * 20;
	unsigned int y = (rand() % (win.getSize().y / 20) + 0) * 20;

	return sf::Vector2f(x, y);
}

void Move(sf::RectangleShape* snake[], unsigned int length) {
	for (unsigned int i = length - 1 ; i > 0; --i)
		snake[i]->setPosition(snake[i - 1]->getPosition());
}

void Draw(sf::RenderWindow &win, sf::RectangleShape* snake[], unsigned int length) {
	for (int i = 0; i < length; ++i)
		win.draw(*snake[i]);
}