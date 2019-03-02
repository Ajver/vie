#include "Logger.h"

#include <stdexcept>

#include "Engine.h"

namespace vie
{

	Engine* Logger::m_engine;

	void Logger::fatalError(const std::string& errorString)
	{
		printf("\nFATAL ERROR: %s\n\n", errorString.c_str());
		throw std::runtime_error(errorString);
	}

	void Logger::log(const std::string& logString)
	{
		printf("\nLOG: \n\n", logString.c_str());
		m_engine->onLog(logString);
	}

}