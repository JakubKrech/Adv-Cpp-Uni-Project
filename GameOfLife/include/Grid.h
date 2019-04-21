#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Cell.h"
#include "Pattern.h"

#define menuWidth 300.f
#define pixelWidth 800.f
#define pixelHeight 800.f
#define cellSize 4.f

class Grid
{
	int gridWidth, gridHeight;

	std::string path = "PatternsRLE";

	void initializeCells();
	void readPatternsFromRLEFiles(std::string);

public:
	std::vector<std::vector<Cell>> cellGrid;
	std::map<std::string, Pattern> patterns;

	Grid();
	~Grid();

	void calculateNextStep();
	
	void spawnPattern(std::string, int, int);
};

