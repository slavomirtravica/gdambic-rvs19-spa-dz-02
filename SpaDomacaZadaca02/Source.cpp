#include <SFML/Graphics.hpp>
#include "Mreza.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Game of Life");
	window.setFramerateLimit(60);
	Mreza mreza(&window);

	mreza.inicijaliziraj();
	window.display();
	sf::sleep(sf::seconds(2));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		mreza.draw();
		window.display();
		sf::sleep(sf::seconds(2));
	}

	return 0;
}