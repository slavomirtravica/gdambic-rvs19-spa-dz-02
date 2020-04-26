#pragma once
#include <SFML/Graphics.hpp>
#include "Flags.h"

class Mreza
{
public:
	Mreza(sf::RenderWindow* window);
	void inicijaliziraj();
	void set_background();
	short brojSusjeda_mid(int i, int j);
	short brojSusjeda_upDown(int x, bool smjer);
	short brojSusjeda_leftRight(int x, bool strana);
	short brojSusjeda_edge(char c);
	void set_flags_mid();
	void set_flags_upDown(bool smjer);
	void set_flags_leftRight(bool strana);
	void set_flags_edge();
	void premapirajFlagove();
	void draw();
private:
	sf::RenderWindow* window;
	sf::RectangleShape background;
	sf::CircleShape mreza[20][20];
	struct Flags flags;
};

