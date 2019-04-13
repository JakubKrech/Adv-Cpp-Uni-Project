#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Cell.h"
#include "Pattern.h"



class Grid
{
	int pixelWidth, pixelHeight;
	int cellSize;
	int gridWidth, gridHeight;

	void initializeCells();

public:
	std::vector<std::vector<Cell>> cellGrid;

	std::unique_ptr<sf::RenderWindow> window;

	Grid(int, int, int);
	~Grid();

	void calculateNextStep();
	
	void spawnPattern(Pattern, int, int);
};
