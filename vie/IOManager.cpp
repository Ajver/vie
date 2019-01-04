#include "IOManager.h"

#include <fstream>

namespace vie
{

	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}

		// Seek to the end
		file.seekg(0, std::ios::end);

		// Get the file size
		// tellg() returns number of bytes 
		int fileSize = file.tellg();

		// Return to begin of the file
		file.seekg(0, std::ios::beg);

		// Reduuce the file size by any header bytes that might be present
		fileSize -= file.tellg();

		buffer.resize(fileSize);

		if (fileSize == 0)
			return false;

		file.read((char*)&buffer[0], fileSize);
		file.close();

		return true;
	}

}