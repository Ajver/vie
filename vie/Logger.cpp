#include "Logger.h"

#include <stdexcept>

#include "Engine.h"

namespace vie
{

	Engine* Logger::m_engine = nullptr;

	void Logger::fatalError(const std::string& errorString)
	{
		throw std::runtime_error(errorString);
	}

	void Logger::log(const std::string& logString)
	{
		m_engine->onLog(logString);
	}

}