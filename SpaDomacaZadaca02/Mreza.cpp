#include "Mreza.h"
#include <iostream>
#include <ctime>

Mreza::Mreza(sf::RenderWindow* window)
{
	this->window = window;
}

void Mreza::set_background()//sf::RectangleShape& background
{
	background.setSize(sf::Vector2f(800.f, 800.f));
	background.setFillColor(sf::Color::Green);
	background.setOrigin(0, 0);
}

void Mreza::inicijaliziraj()
{
	srand(time(nullptr));

	// pozadina, možeš je probat u konstruktor
	set_background();
	window->draw(this->background);

	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		int y = 0;
		for (int j = 0; j < 20; j++)
		{
			// 1/4 -> 25% sanse da ce se inicijalizirati u boji, ostali ce biti "prozirni"
			int randy = rand() % 4;
			mreza[i][j].setRadius(19);
			if (!randy)
			{
				mreza[i][j].setFillColor(sf::Color::Red);
				flags.state[i][j] = true;
			}
			else
			{
				mreza[i][j].setFillColor(sf::Color::Green);
				flags.state[i][j] = false;
			}
			mreza[i][j].setPosition(sf::Vector2f(x, y));
			y += 40;
			window->draw(mreza[i][j]);
		}
		x += 40;
	}
}

short Mreza::brojSusjeda_edge(char c)
{
	int broj = 0;
	switch (c)
	{
	case 'c':
		if (flags.state[0][1])
		{
			broj++;
		}
		if (flags.state[1][0])
		{
			broj++;
		}
		if (flags.state[1][1])
		{
			broj++;
		}
		break;
	case 'd':
		if (flags.state[0][18])
		{
			broj++;
		}
		if (flags.state[1][19])
		{
			broj++;
		}
		if (flags.state[1][18])
		{
			broj++;
		}
		break;
	case 'a':
		if (flags.state[19][1])
		{
			broj++;
		}
		if (flags.state[18][0])
		{
			broj++;
		}
		if (flags.state[18][1])
		{
			broj++;
		}
		break;
	case 'b':
		if (flags.state[19][18])
		{
			broj++;
		}
		if (flags.state[18][19])
		{
			broj++;
		}
		if (flags.state[18][18])
		{
			broj++;
		}
		break;
	default:
		break;

		return broj;
	}
}

void Mreza::set_flags_edge()
{
	short broj = brojSusjeda_edge('c');
	if (broj < 2)
	{
		flags.newstate[0][0] = false;
	}
	else if (broj == 3)
	{
		flags.newstate[0][0] = true;
	}

	broj = brojSusjeda_edge('d');
	if (broj < 2)
	{
		flags.newstate[0][19] = false;
	}
	else if (broj == 3)
	{
		flags.newstate[0][19] = true;
	}

	broj = brojSusjeda_edge('a');
	if (broj < 2)
	{
		flags.newstate[19][0] = false;
	}
	else if (broj == 3)
	{
		flags.newstate[19][0] = true;
	}

	broj = brojSusjeda_edge('b');
	if (broj < 2)
	{
		flags.newstate[19][19] = false;
	}
	else if (broj == 3)
	{
		flags.newstate[19][19] = true;
	}
}

/*
* ako se radi sa gornjim redom kao drugi pararametar se true, ako s donjim onda false
*/
short Mreza::brojSusjeda_upDown(int x, bool smjer)
{
	int upDown, rop;
	if (smjer)
	{
		upDown = 0;
		rop = 1;
	}
	else
	{
		upDown = 19;
		rop = 18;
	}

	short broj = 0;
	if (flags.state[upDown][x - 1])
	{
		broj++;
	}
	if (flags.state[upDown][x + 1])
	{
		broj++;
	}
	for (int i = x - 1; i <= x + 1; i++)
	{
		if (flags.state[rop][i])
		{
			broj++;
		}
	}
	return broj;
}

void Mreza::set_flags_upDown(bool smjer)
{
	int upDown;
	if (smjer)
	{
		upDown = 0;
	}
	else
	{
		upDown = 19;
	}

	for (int x = 1; x < 19; x++)
	{
		short broj = brojSusjeda_upDown(x, true);
		if (broj < 2)
		{
			flags.newstate[upDown][x] = false;
		}
		else if (broj == 3)
		{
			flags.newstate[upDown][x] = true;
		}
		else if (broj > 3)
		{
			flags.newstate[upDown][x] = false;
		}

	}
}

short Mreza::brojSusjeda_mid(int i, int j)
{
	short broj = 0;
	for (int k = i - 1; k <= i + 1; k++)
	{
		for (int z = j - 1; z <= j + 1; z++)
		{
			if (flags.state[k][z])
			{
				broj++;
			}
		}
	}

	return broj;
}

void Mreza::set_flags_mid()
{
	int broj = 0;
	for (int i = 1; i < 19; i++)
	{
		for (int j = 1; j < 19; j++)
		{
			broj = brojSusjeda_mid(i, j);

			switch (broj)
			{
			case 0:
			case 1:
				flags.newstate[i][j] = false;
				broj = 0;
				break;
			case 2:
				broj = 0;
				break;
			case 3:
				flags.newstate[i][j] = true;
				broj = 0;
				break;
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
				flags.newstate[i][j] = false;
				broj = 0;
				break;
			default:
				break;
			}

		}
	}
}

short Mreza::brojSusjeda_leftRight(int x, bool strana)
{
	int leftRight, rop;
	if (strana)
	{
		leftRight = 0;
		rop = 1;
	}
	else
	{
		leftRight = 19;
		rop = 18;
	}

	short broj = 0;
	if (flags.state[x - 1][leftRight])
	{
		broj++;
	}
	if (flags.state[x + 1][leftRight])
	{
		broj++;
	}
	for (int i = x - 1; i <= x + 1; i++)
	{
		if (flags.state[i][rop])
		{
			broj++;
		}
	}
	return broj;

}

/* true desno, false lijevo ~ m.p. Thompson */
void Mreza::set_flags_leftRight(bool strana)
{
	int leftRight;
	if (strana)
	{
		leftRight = 19;
	}
	else
	{
		leftRight = 0;
	}

	for (int x = 1; x < 19; x++)
	{
		short broj = brojSusjeda_upDown(x, true);
		if (broj < 2)
		{
			flags.newstate[x][leftRight] = false;
		}
		else if (broj == 3)
		{
			flags.newstate[x][leftRight] = true;
		}
		else if (broj > 3)
		{
			flags.newstate[x][leftRight] = false;
		}
	}
}

void Mreza::premapirajFlagove()
{
	set_flags_mid();
	set_flags_upDown(true);
	set_flags_upDown(false);
	set_flags_leftRight(true);
	set_flags_leftRight(false);
	set_flags_edge();

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			flags.state[i][j] = flags.newstate[i][j];
		}
	}
}

void Mreza::draw()
{
	// pozadina, možeš je probat u konstruktor
	set_background();
	window->draw(this->background);
	premapirajFlagove();

	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		int y = 0;
		for (int j = 0; j < 20; j++)
		{
			if (flags.state[i][j])
			{
				mreza[i][j].setFillColor(sf::Color::Red);
			}
			else
			{
				mreza[i][j].setFillColor(sf::Color::Green);
			}
			window->draw(mreza[i][j]);
		}
	}
}