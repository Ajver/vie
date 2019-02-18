#include "Logger.h"

#include <stdexcept>

namespace vie
{

	void Logger::fatalError(const std::string& errorString)
	{
		throw std::runtime_error("FATAL_ERROR: " + errorString);
	}

	void Logger::log(const std::string& logString)
	{
		printf(("LOG: " + logString + "\n").c_str());
	}

}