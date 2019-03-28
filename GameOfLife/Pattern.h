#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;

class Pattern
{
	void readFile(fs::path);
	void parseData(std::string);
	void fillCellPatern();
public:
	std::string fullInfo;
	std::string name;
	int width, height;
	std::string RLE_format;

	std::vector<std::vector<bool>> cellPattern;

	Pattern(fs::path);
	~Pattern();
};

