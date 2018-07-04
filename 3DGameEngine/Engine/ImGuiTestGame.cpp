#include "ImGuiTestGame.h"
#include "Rendering/DebugUI.h"
#include "Audio/AudioListener.h"
#include "GameComponents/FreeMove.h"
#include "GameComponents/FreeLook.h"

void ImGuiTestGame::Init()
{
    auto cameraOBJ = new GameObject("camera");

    cameraOBJ->AddComponent(new Camera(
        60.0f, static_cast<float>(*Window::GetWidth()) / static_cast<float>(*Window::GetHeight()), 0.001f, 1000.0f));
    cameraOBJ->GetTransform()->SetPosition(math::Vector3(0, 0, 5));
    cameraOBJ->AddComponent(new FreeLook());
    cameraOBJ->AddComponent(new FreeMove());
    cameraOBJ->AddComponent(new AudioListener());
    AddToScene(cameraOBJ);

    DebugUIWindow* window = new DebugUIWindow();
    Text* text = new Text("This is a test text");
    SliderVector3* sliderVector3 = new SliderVector3(0, 1);

    window->AddElement(text);
    window->AddElement(sliderVector3);

    DebugUIWindow* window2 = new DebugUIWindow("second");
    Text* text2 = new Text("This is a second \n test text");
    ColorEdit3* colorEdit3 = new ColorEdit3();

    window2->AddElement(text2);
    window2->AddElement(colorEdit3);

    AddToDebugUI(window);
    AddToDebugUI(window2);

}
