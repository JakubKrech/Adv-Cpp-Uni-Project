#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;

class Pattern
{
	void readFile(fs::path);
public:
	std::string fullInfo;
	std::string name;
	int width, height;
	std::string RLE_format;

	Pattern(fs::path);
	~Pattern();
};

