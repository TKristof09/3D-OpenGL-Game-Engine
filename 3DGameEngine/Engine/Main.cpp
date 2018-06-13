#include "Core\CoreEngine.h"
#include "PhysicsTestGame.h"
#include "AssimpTestGame.h"

#ifdef __cplusplus
extern "C"
#endif

//For detecting memory leaks
//#define _CRTDBG_MAP_ALLOC  
//#include <stdlib.h>  
//#include <crtdbg.h>  

int main(int argc, char* argv[])
{
	glewExperimental = GL_TRUE;
//	PhysicsTestGame testGame;
	AssimpTestGame testGame;

	Game* game = &testGame;
	{
		CoreEngine engine(800, 600, 60, game);
		engine.CreateWindow("3D Game Engine");
		engine.Start(); 
	}
//	_CrtDumpMemoryLeaks();
	return 0;
}
