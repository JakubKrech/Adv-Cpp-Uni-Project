#include "..\\include\\Grid.h"

#include <iostream>
#include <random>
#include "..\\vendor\\Dear_ImGui\\imgui.h"
#include "..\\vendor\\Dear_ImGui\\imgui-SFML.h"

void Grid::initializeCells()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(20, 255);
	int R = uniform_dist(e1);
	std::cout << "Randomized R color value: " <<  R << std::endl;

	for (auto x = 0; x < gridWidth; x++) {
		for (auto y = 0; y < gridHeight; y++) {

			int G = x == 0 ? 0 : (int)(255 / (float)((gridWidth * 1.0) / (x * 1.0)));
			int B = y == 0 ? 0 : (int)(255 / (float)((gridHeight * 1.0) / (y * 1.0)));

			sf::Color cellColor = sf::Color(R, G, B, 255);

			Cell newCell{ sf::Vector2f(cellSize, cellSize), sf::Vector2f(x*cellSize, y*cellSize), x, y, cellColor };
			cellGrid[x].push_back(newCell);
		}
	}

	int left, top, right, bottom;

	for (auto x = 0; x < gridWidth; x++) {
		for (auto y = 0; y < gridHeight; y++) {		

			x == 0 ? left = gridWidth - 1 : left = x - 1;
			y == 0 ? top = gridHeight - 1 : top = y - 1;
			x == gridWidth - 1 ? right = 0 : right = x + 1;
			y == gridHeight - 1 ? bottom = 0 : bottom = y + 1;

			cellGrid[x][y].neighbors[Cell::NW] = &cellGrid[left][top];
			cellGrid[x][y].neighbors[Cell::N] = &cellGrid[x][top];
			cellGrid[x][y].neighbors[Cell::NE] = &cellGrid[right][top];
			cellGrid[x][y].neighbors[Cell::E] = &cellGrid[right][y];
			cellGrid[x][y].neighbors[Cell::SE] = &cellGrid[right][bottom];
			cellGrid[x][y].neighbors[Cell::S] = &cellGrid[x][bottom];
			cellGrid[x][y].neighbors[Cell::SW] = &cellGrid[left][bottom];
			cellGrid[x][y].neighbors[Cell::W] = &cellGrid[left][y];
		}
	}
}

void Grid::readPatternsFromRLEFiles(std::string path)
{
	for (const auto &entry : fs::directory_iterator(path)) {
		Pattern newPattern{ entry };
		this->patterns.insert(std::pair<std::string, Pattern>(newPattern.name, newPattern));
	}

	// print read patterns
	for (const auto &x : patterns)
		std::cout << x.second.name << std::endl;
}


Grid::Grid()
{
	gridWidth =  pixelWidth  / cellSize;
	gridHeight = pixelHeight / cellSize;

	std::cout << gridWidth << " " << gridHeight << std::endl;

	cellGrid.resize(gridWidth);

	initializeCells();
	readPatternsFromRLEFiles("PatternsRLE");
}


Grid::~Grid()
{
}

void Grid::calculateNextStep()
{
	for (auto x = 0; x < gridWidth; x++) {
		for (auto y = 0; y < gridHeight; y++) {

			int aliveNighbours = 0;

			for (auto neighbor : cellGrid[x][y].neighbors) if (neighbor->previousState) ++aliveNighbours;

			if (cellGrid[x][y].previousState == false) {
				if (aliveNighbours == 3) cellGrid[x][y].setNextState(true);		// cell becomes alive by reproduction
			}
			else if (cellGrid[x][y].previousState == true) {

				if (aliveNighbours < 2) cellGrid[x][y].setNextState(false);			// alive cell dies by underpopulation
																					// else if (aliveNighbours == 2 || aliveNighbours == 3) {}; // alive cell stays alive
				else if (aliveNighbours > 3) cellGrid[x][y].setNextState(false);	// alive cell dies by overpopulation
			}
		}
	}

	for (auto x = 0; x < gridWidth; x++) {
		for (auto y = 0; y < gridHeight; y++) {
			if (cellGrid[x][y].previousState != cellGrid[x][y].nextState) {

				cellGrid[x][y].updateState();
			}
		}
	}
}

void Grid::spawnPattern(std::string patternName, int x, int y)
{
	Pattern patternToSpawn = patterns.find(patternName)->second;
	int xx, yy;

	for (size_t i = 0; i < patternToSpawn.height; i++)
	{
		for (size_t j = 0; j < patternToSpawn.width; j++)
		{
			xx = x + i;
			yy = y + j;

			if (xx >= pixelWidth / cellSize) xx -= pixelWidth / cellSize;
			//else if (xx < 0) xx += pixelWidth;

			if (yy >= pixelHeight / cellSize) yy -= pixelHeight / cellSize;
			//else if (yy < 0) yy += pixelHeight;

			cellGrid[xx][yy].nextState = patternToSpawn.cellPattern[j][i];
		}
	}
}
