#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Cell.h"
#include "Pattern.h"

#define menuWidth 300.f
#define pixelWidth 800.f
#define pixelHeight 800.f
#define cellSize 8.f

class Grid
{
	int gridWidth, gridHeight;

	void initializeCells();

public:
	std::vector<std::vector<Cell>> cellGrid;

	Grid();
	~Grid();

	void calculateNextStep();
	
	void spawnPattern(Pattern, int, int);
};

