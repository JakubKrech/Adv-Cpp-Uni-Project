#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>

class Cell : public sf::RectangleShape
{
public:
	int x, y;
	bool previousState = false;
	bool nextState = false;
	enum direction { NW = 0, N, NE, E, SE, S, SW, W };
	std::vector<Cell*> neighbors;
	std::deque<bool> memento;
	const static int mementoMaxSize = 50;

public:
	Cell(sf::Vector2f, sf::Vector2f, int, int, sf::Color);
	~Cell();
	
	void setNextState(bool);
	void updateState();

	void addMemento();
	bool getMemento();
};

