#include "Core\CoreEngine.h"
#include "TestGame.h"
#include "PhysicsTestGame.h"

#ifdef __cplusplus
extern "C"
#endif

//For detecting memory leaks
//#define _CRTDBG_MAP_ALLOC  
//#include <stdlib.h>  
//#include <crtdbg.h>  

int main(int argc, char* argv[])
{
	TestGame testGame;
//	Game* game = &testGame;
	PhysicsTestGame physicsTestGame;
	Game* game = &physicsTestGame;
	{
		CoreEngine engine(800, 600, 60, game);
		engine.CreateWindow("3D Game Engine");
		engine.Start(); 
	}
//	_CrtDumpMemoryLeaks();
	return 0;
}
