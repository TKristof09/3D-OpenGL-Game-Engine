#ifndef TESTGAME_H
#define TESTGAME_H
#include "Core\Game.h"



class TestGame : public Game
{
public:
	TestGame();
	~TestGame() override;
	void Init() override;
private:
	
};

#endif // !TESTGAME_H