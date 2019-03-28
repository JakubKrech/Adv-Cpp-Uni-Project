#include "Cell.h"

#include <iostream>

Cell::Cell(sf::Vector2f size, sf::Vector2f position, int xx, int yy, sf::Color clr) : x{ xx }, y{ yy }//, color{clr}
{
	this->setSize(size);
	this->setPosition(position);
	this->setFillColor(clr);
	neighbors.resize(8, NULL);
}


Cell::~Cell()
{
}

void Cell::setNextState(bool state)
{
	nextState = state;
}

void Cell::updateState()
{
	previousState = nextState;
}

