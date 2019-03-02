#pragma once

#include <string>

namespace vie
{
	class Engine;

	class Logger
	{
	public:
		static void fatalError(const std::string& errorString);
		static void log(const std::string& logString);
		
	private:
		static Engine* m_engine;

		friend Engine;

		Logger();

	};
}