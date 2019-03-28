#include "Pattern.h"



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
		f.read(result.data(), sz);

		fullInfo = result;
	}
	else std::cout << "File doesn't exist" << std::endl;
}

Pattern::Pattern(fs::path filePath)
{
	readFile(filePath);
	std::cout << fullInfo << std::endl;
}


Pattern::~Pattern()
{
}
