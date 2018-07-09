#include "Core\CoreEngine.h"
#include "PhysicsTestGame.h"
#include "AssimpTestGame.h"
#include "AudioTestGame.h"
#include "ImGuiTestGame.h"

#ifdef __cplusplus
extern "C"
#endif

//For detecting memory leaks
//#define _CRTDBG_MAP_ALLOC  
//#include <stdlib.h>  
//#include <crtdbg.h>  



int main(int argc, char* argv[])
{
//	PhysicsTestGame testGame;
//	AssimpTestGame testGame;
//  AudioTestGame testGame;
//  ImGuiTestGame testGame;

	CoreEngine engine(800, 600, 60);

    engine.AddGame<PhysicsTestGame>("PhysicsTestGame");
    engine.AddGame<AssimpTestGame>("AssimpTestGame");
    engine.AddGame<AudioTestGame>("AudioTestGame");
    engine.AddGame<ImGuiTestGame>("ImGuiTestGame");

	engine.CreateWindow("3D Game Engine");
	engine.Start();

//	_CrtDumpMemoryLeaks();
	return 0;
}
