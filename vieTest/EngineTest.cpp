#include "pch.h"

#include <vie/Engine.h>
#include <vie/Logger.h>

class MainClass : public vie::Engine
{
public:
	MainClass() :
		fatalErrorTestSuccess(false),
		logTestSuccess(false)
	{
		runEngine("", 600, 400, vie::WindowFlags::INVISIBLE);
	}

	void onCreate()
	{
		vie::Logger::log("Test log");
		vie::Logger::fatalError("Test fatal error");
	}

	void onFatalError(const std::string& errMsg)
	{
		fatalErrorTestSuccess = errMsg == "Test fatal error";
	}

	void onLog(const std::string& logMsg)
	{
		logTestSuccess = logMsg == "Test log";
	}

	bool fatalErrorTestSuccess;
	bool logTestSuccess;

private:

};

TEST(EngineTest, ShouldRun_OnLog)
{
	EXPECT_TRUE(MainClass().logTestSuccess);
}

TEST(EngineTest, ShouldRun_OnFatalError)
{
	EXPECT_TRUE(MainClass().fatalErrorTestSuccess);
}

TEST(EngineTest, ZZZ_Last)
{
}
