#include "Logger.h"

#include <stdexcept>

#include "Engine.h"

namespace vie
{

	Engine* Logger::m_engine = nullptr;

	void Logger::fatalError(const std::string& errorString)
	{
		printf("FATAL ERROR: %s\n", errorString.c_str());
		throw std::runtime_error(errorString);
	}

	void Logger::log(const std::string& logString)
	{
		printf("LOG: %s\n", logString.c_str());
		m_engine->onLog(logString);
	}

}