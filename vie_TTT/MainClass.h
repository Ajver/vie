#include <vie/Engine.h>
#include "Tile.h"

class MainClass : public vie::Engine
{
public:
	MainClass();
	~MainClass();

	void onCreate();
	void onFatalError(const std::string& errMsg);

	void update(float et);
	void render(vie::Graphics* g);

private:
	Tile* board[3][3];
};