#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define colorDead sf::Color::White
#define colorAlive sf::Color::Red

class Cell : public sf::RectangleShape
{
public:
	int x, y;
	bool isAlive = false;
	enum direction { NW = 0, N, NE, E, SE, S, SW, W };
	std::vector<Cell*> neighbors;

public:
	Cell(sf::Vector2f, sf::Vector2f, int, int);
	~Cell();
	

	void setAlive();
	void setDead();
};

