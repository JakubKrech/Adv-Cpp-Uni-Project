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

public:
	std::vector<std::vector<Cell>> cellGrid;

	std::unique_ptr<sf::RenderWindow> window;

	Grid(int, int, int);
	~Grid();

	void calculateNextStep();
	void spawnGlider(int, int);
	void spawnFrog(int, int);
	void spawnCopperhead(int xx, int yy);
};

