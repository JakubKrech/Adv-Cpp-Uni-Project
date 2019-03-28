#include "Grid.h"

#include <iostream>
#include <random>


void Grid::initializeCells()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(20, 255);
	int R = uniform_dist(e1);
	std::cout << "Randomized R color value: " <<  R << std::endl;
	//cool R values: 23, 227

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

Grid::Grid(int W, int H, int cS): pixelWidth(W), pixelHeight(H), cellSize(cS)
{
	gridWidth = pixelWidth / cellSize;
	gridHeight = pixelHeight / cellSize;

	cellGrid.resize(gridWidth);
	window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(pixelWidth, pixelHeight), "GameOfLife"));

	initializeCells();
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

void Grid::spawnGlider(int xx, int yy) // to be removed
{
	cellGrid[xx][yy].setNextState(true);
	cellGrid[xx + 1][yy].setNextState(true);
	cellGrid[xx + 2][yy].setNextState(true);
	cellGrid[xx + 2][yy - 1].setNextState(true);
	cellGrid[xx + 1][yy - 2].setNextState(true);
}

void Grid::spawnFrog(int xx, int yy) // to be removed
{
	cellGrid[xx][yy].setNextState(true);
	cellGrid[xx][yy + 1].setNextState(true);
	cellGrid[xx][yy + 2].setNextState(true);
	cellGrid[xx + 1][yy + 1].setNextState(true);
	cellGrid[xx + 1][yy + 2].setNextState(true);
	cellGrid[xx + 1][yy + 3].setNextState(true);
}

void Grid::spawnCopperhead(int xx, int yy) // to be removed
{
	cellGrid[xx + 5][yy].setNextState(true);
	
	cellGrid[xx + 5][yy + 1].setNextState(true);

	cellGrid[xx + 6][yy + 2].setNextState(true);
	cellGrid[xx + 9][yy + 2].setNextState(true);

	cellGrid[xx + 4][yy + 3].setNextState(true);
	cellGrid[xx + 5][yy + 3].setNextState(true);
	cellGrid[xx + 6][yy + 3].setNextState(true);
	cellGrid[xx + 8][yy + 3].setNextState(true);
	cellGrid[xx + 9][yy + 3].setNextState(true);
	cellGrid[xx + 11][yy + 3].setNextState(true);

	cellGrid[xx][yy + 4].setNextState(true);
	cellGrid[xx + 1][yy + 4].setNextState(true);
	cellGrid[xx + 8][yy + 4].setNextState(true);
	cellGrid[xx + 9][yy + 4].setNextState(true);
	cellGrid[xx + 11][yy + 4].setNextState(true);
	cellGrid[xx + 12][yy + 4].setNextState(true);

	cellGrid[xx][yy + 5].setNextState(true);
	cellGrid[xx + 1][yy + 5].setNextState(true);
	cellGrid[xx + 8][yy + 5].setNextState(true);
	cellGrid[xx + 9][yy + 5].setNextState(true);
	cellGrid[xx + 11][yy + 5].setNextState(true);
	cellGrid[xx + 12][yy + 5].setNextState(true);

	cellGrid[xx + 4][yy + 6].setNextState(true);
	cellGrid[xx + 5][yy + 6].setNextState(true);
	cellGrid[xx + 6][yy + 6].setNextState(true);
	cellGrid[xx + 8][yy + 6].setNextState(true);
	cellGrid[xx + 9][yy + 6].setNextState(true);
	cellGrid[xx + 11][yy + 6].setNextState(true);

	cellGrid[xx + 6][yy + 7].setNextState(true);
	cellGrid[xx + 9][yy + 7].setNextState(true);

	cellGrid[xx + 5][yy + 8].setNextState(true);

	cellGrid[xx + 5][yy + 9].setNextState(true);
}
