#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Cell.h"



class Grid
{
	int pixelWidth, pixelHeight;
	int cellSize;
	int gridWidth, gridHeight;

	void initializeCells();
	void copyGridAliveStates(std::vector<std::vector<Cell>>&, std::vector<std::vector<Cell>>&);
public:
	std::vector<std::vector<Cell>> cellGrid;
	std::vector<std::vector<Cell>> temp;

	std::unique_ptr<sf::RenderWindow> window; //usunac raw pointer

	Grid(int, int, int);
	~Grid();

	void calculateNextStep();
	void spawnGlider(int, int);
};

