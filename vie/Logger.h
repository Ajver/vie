#pragma once

#include <string>

namespace vie
{

	class Logger
	{
	public:
		static void fatalError(const std::string& errorString);
		static void log(const std::string& logString);
		
	private:
		Logger();
	};
}