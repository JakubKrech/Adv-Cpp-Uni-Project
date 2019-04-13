#include "..\\include\\Pattern.h"



void Pattern::readFile(fs::path filePath)
{
	if (fs::exists(filePath) ) {
		// Open the stream to 'lock' the file.
		std::ifstream f{ filePath };

		// Obtain the size of the file.
		const auto sz = fs::file_size(filePath);

		// Create a buffer.
		std::string result(sz, ' ');

		// Read the whole file into the buffer.
		//f.read(result.data(), sz);
		f.read((char*)result.data(), sz);

		fullInfo = result;
	}
	else std::cout << "File doesn't exist" << std::endl;
}

void Pattern::parseData(std::string input)
{
	auto found = input.find("#N");
	name = input.substr(found + 3, input.find("\n") - 3);

	found = input.find("x = ");
	width = std::stoi(input.substr(found + 4, input.find(", y") - 1));

	found = input.find("y = ");
	height = std::stoi(input.substr(found + 4, input.find(", rule") - 1));

	found = input.find("\n", found);
	RLE_format = input.substr(found + 1, input.find("!"));

	std::cout << name << " " << width << " " << height << " " << RLE_format << std::endl;
}

void Pattern::fillCellPatern()
{
	int x = 0;
	int y = 0;
	int number = 0;
	bool status = false;

	for (auto it = RLE_format.begin(); it != RLE_format.end(); it++) 
	{
		if (*it == '!')
		{
			break;
		}
		else if (isdigit(*it))
		{
			number = number * 10 + ((int)*it - '0');
		}
		else
		{
			if (*it == 'b' || *it == 'o') {
				
				*it == 'b' ? status = false : status = true;
				
				if (number == 0) number = 1;
				for (int i = 0; i < number; i++)
				{
						cellPattern[x + i][y] = status;
				}

				x += number;
				number = 0;
			}
			else if (*it == '$')
			{
				x = 0;
				number != 0 ? y += number : ++y;
				number = 0;
			}
		}
	}
	
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			std::cout << cellPattern[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << "\n\n";
}

Pattern::Pattern(fs::path filePath)
{
	readFile(filePath);
	parseData(fullInfo);
	
	cellPattern.resize(width, std::vector<bool>(height, false));

	fillCellPatern();

}


Pattern::~Pattern()
{

}
