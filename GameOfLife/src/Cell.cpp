#include "..\\include\\Cell.h"

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

void Cell::addMemento()
{
	this->memento.push_front(this->previousState);
	if (this->memento.size() > mementoMaxSize) 
		this->memento.pop_back();

	//std::cout << memento.size() << std::endl;
}

bool Cell::getMemento()
{
	bool state = this->memento.front();
	this->memento.pop_front();
	return state;
}

