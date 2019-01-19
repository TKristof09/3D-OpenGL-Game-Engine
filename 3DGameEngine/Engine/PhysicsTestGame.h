#ifndef PHYSICSTESTGAME_H
#define PHYSICSTESTGAME_H

#include "Core/Game.h"

const int DEBUG_LIGHT_DIRECTION = 1;

class PhysicsTestGame : public Game
{
public:
	PhysicsTestGame() = default;
	void Init() override;
private:
};

#endif //!PHYSICSTESTGAME_H
