#include "Core/CoreEngine.h"
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


	CoreEngine engine(1280, 720, 60);

    engine.AddGame<PhysicsTestGame>("PhysicsTestGame");
    engine.AddGame<AssimpTestGame>("AssimpTestGame");
    engine.AddGame<AudioTestGame>("AudioTestGame");
    engine.AddGame<ImGuiTestGame>("ImGuiTestGame");

	engine.CreateWindow("3D Game Engine");
	engine.Start();

//	_CrtDumpMemoryLeaks();
	return 0;
}
