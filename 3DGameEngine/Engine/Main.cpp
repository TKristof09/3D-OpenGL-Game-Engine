#include "Core\CoreEngine.h"
#include "TestGame.h"

#ifdef __cplusplus
extern "C"
#endif


int main(int argc, char *argv[])
{
	TestGame testGame;
	Game* game = &testGame;
	CoreEngine engine(800, 600, 60, game);
	engine.CreateWindow("3D Game Engine");
	engine.Start();

	return 0;
}
