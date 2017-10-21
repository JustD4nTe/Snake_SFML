#include <SFML/Graphics.hpp>

#define SNAKE_SIZE 20

int main(){
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	sf::RectangleShape snake(sf::Vector2f(SNAKE_SIZE, SNAKE_SIZE));
	snake.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	sf::Clock timer;

	unsigned int Direction = 1;

	float frameSwitch = 500, frameCounter = 0, frameSpeed = 800;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.key.code == sf::Keyboard::Escape)
				window.close();			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			Direction = 1;
		
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			Direction = 2;

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			Direction = 3;

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			Direction = 4;


		frameCounter += frameSpeed * timer.restart().asSeconds();

		if (frameCounter >= frameSwitch) {
			switch (Direction){
			case 1:
				snake.move(0, -SNAKE_SIZE);	//	UP
				break;
			case 2:
				snake.move(0, SNAKE_SIZE);	//	DOWN
				break;
			case 3:
				snake.move(-SNAKE_SIZE, 0);	//	LEFT
				break;
			case 4:
				snake.move(SNAKE_SIZE, 0);	//	RIGHT
				break;
			default:
				break;
			}

			frameCounter = 0;
		}

		window.clear();
		window.draw(snake);
		window.display();
	}

	return 0;
}