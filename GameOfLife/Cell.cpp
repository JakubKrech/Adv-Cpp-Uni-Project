#include "Cell.h"

#include <iostream>

Cell::Cell(sf::Vector2f size, sf::Vector2f position, int xx, int yy) : x{ xx }, y{ yy }
{
	this->setSize(size);
	this->setPosition(position);
	this->setFillColor(colorDead);
	neighbors.resize(8, NULL);

}


Cell::~Cell()
{
	//std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
}

void Cell::setAlive()
{
	isAlive = true;
	this->setFillColor(colorAlive);
}

void Cell::setDead()
{
	isAlive = false;
	this->setFillColor(colorDead);
}

