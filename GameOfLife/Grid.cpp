#include "Grid.h"

#include <iostream>


void Grid::initializeCells()
{
	for (auto x = 0; x < gridWidth; x++) {
		for (auto y = 0; y < gridHeight; y++) {
			Cell newCell{ sf::Vector2f(cellSize, cellSize), sf::Vector2f(x*cellSize, y*cellSize), x, y };
			cellGrid[x].push_back(newCell);
		}
	}

	/*for (auto x = 0; x < gridWidth; x++) {
		for (auto y = 0; y < gridHeight; y++) {
			std::cout << cellGrid[x][y].x << " " << cellGrid[x][y].y << std::endl;
		}
	}*/

	int left, top, right, bottom;

	for (auto x = 0; x < gridWidth; x++) {
		for (auto y = 0; y < gridHeight; y++) {		

			x == 0 ? left = gridWidth - 1 : left = x - 1;
			y == 0 ? top = gridHeight - 1 : top = y - 1;
			x == gridWidth - 1 ? right = 0 : right = x + 1;
			y == gridHeight - 1 ? bottom = 0 : bottom = y + 1;

			/*x - 1 > 0 ? left = x - 1 : left = gridWidth - 1;
			y - 1 > 0 ? top = y - 1 : top = gridHeight - 1;
			x + 1 < gridWidth - 1 ? right = x + 1 : right = 0;
			y + 1 < gridHeight - 1 ? bottom = y + 1 : bottom = 0;*/
			/*left = x - 1;
			top = y - 1;
			right = x + 1;
			bottom = y + 1;*/

			/*if (left >= 0 && top >= 0) cellGrid[x][y].neighbors[Cell::NW] = &cellGrid[left][top];
			if (top >= 0) cellGrid[x][y].neighbors[Cell::N] = &cellGrid[x][top];
			if (right < gridWidth && top >= 0) cellGrid[x][y].neighbors[Cell::NE] = &cellGrid[right][top];
			if (right < gridWidth) cellGrid[x][y].neighbors[Cell::E] = &cellGrid[right][y];
			if (right < gridWidth && bottom < gridHeight) cellGrid[x][y].neighbors[Cell::SE] = &cellGrid[right][bottom];
			if (bottom < gridHeight) cellGrid[x][y].neighbors[Cell::S] = &cellGrid[x][bottom];
			if (left >= 0 && bottom < gridHeight) cellGrid[x][y].neighbors[Cell::SW] = &cellGrid[left][bottom];
			if (left >= 0) cellGrid[x][y].neighbors[Cell::W] = &cellGrid[left][y];*/
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

	/*for (auto x = 0; x < gridWidth; x++) {
		for (auto y = 0; y < gridHeight; y++) {
			for(auto z: cellGrid[x][y].neighbors)
				if(z != NULL) std::cout << x << y << " NULL" << std::endl;
		}
	}*/

}

Grid::Grid(int W, int H, int cS): pixelWidth(W), pixelHeight(H), cellSize(cS)
{
	gridWidth = pixelWidth / cellSize;
	gridHeight = pixelHeight / cellSize;

	cellGrid.resize(gridWidth);
	window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(pixelWidth, pixelHeight), "GameOfLife"));

	initializeCells();
	temp = cellGrid;
}


Grid::~Grid()
{
}

void Grid::calculateNextStep()
{
	copyGridAliveStates(cellGrid, temp);
	
	for (auto x = 0; x < gridWidth; x++) {
		for (auto y = 0; y < gridHeight; y++) {

			int aliveNighbours = 0;

			if (cellGrid[x][y].neighbors[Cell::NW]->isAlive) aliveNighbours++;
			if (cellGrid[x][y].neighbors[Cell::N]->isAlive) aliveNighbours++;
			if (cellGrid[x][y].neighbors[Cell::NE]->isAlive) aliveNighbours++;
			if (cellGrid[x][y].neighbors[Cell::E]->isAlive) aliveNighbours++;
			if (cellGrid[x][y].neighbors[Cell::SE]->isAlive) aliveNighbours++;
			if (cellGrid[x][y].neighbors[Cell::S]->isAlive) aliveNighbours++;
			if (cellGrid[x][y].neighbors[Cell::SW]->isAlive) aliveNighbours++;
			if (cellGrid[x][y].neighbors[Cell::W]->isAlive) aliveNighbours++;

			if (cellGrid[x][y].isAlive == false) {
				if (aliveNighbours == 3) temp[x][y].setAlive();		// cell becomes alive by reproduction
			}
			else if (cellGrid[x][y].isAlive == true) {

				if (aliveNighbours < 2) temp[x][y].setDead();			// alive cell dies by underpopulation
																					// else if (aliveNighbours == 2 || aliveNighbours == 3) {}; // alive cell stays alive
				else if (aliveNighbours > 3) temp[x][y].setDead();	// alive cell dies by overpopulation
			}
		}
	}

	copyGridAliveStates(temp, cellGrid);
}

void Grid::spawnGlider(int xx, int yy)
{
	cellGrid[xx][yy].setAlive();
	cellGrid[xx + 1][yy].setAlive();
	cellGrid[xx + 2][yy].setAlive();
	cellGrid[xx + 2][yy - 1].setAlive();
	cellGrid[xx + 1][yy - 2].setAlive();
}

void Grid::copyGridAliveStates(std::vector<std::vector<Cell>> &from, std::vector<std::vector<Cell>> &to)
{
	for (auto x = 0; x < from.size(); x++) {
		for (auto y = 0; y < from[0].size(); y++) {
			if (to[x][y].isAlive && !from[x][y].isAlive) to[x][y].setDead();
			else if (!to[x][y].isAlive && from[x][y].isAlive) to[x][y].setAlive();
			//to[x][y].isAlive = from[x][y].isAlive;
		}
	}
}
