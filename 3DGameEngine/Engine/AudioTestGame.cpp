#include "AudioTestGame.h"
#include "GameComponents/FreeMove.h"
#include "GameComponents/FreeLook.h"
#include "GameComponents/Camera.h"
#include "Audio/AudioListener.h"
#include "Audio/AudioSource.h"

class TestA : public GameComponent
{
public:
    void Start() override
    {
        audioSource = GetGameObject()->GetComponent<AudioSource>();
        audioSource->Play();
    }
    AudioSource* audioSource;
};

void AudioTestGame::Init()
{
    auto cameraOBJ = new GameObject("camera");
    auto audioOBJ = new GameObject("audio");

    //--------------------------------------------------------------------------------------------------------------------------------------
    //Camera
    //--------------------------------------------------------------------------------------------------------------------------------------

    cameraOBJ->AddComponent(new Camera(
        60.0f, static_cast<float>(*Window::GetWidth()) / static_cast<float>(*Window::GetHeight()), 0.001f, 1000.0f));
    cameraOBJ->GetTransform()->SetPosition(math::Vector3(0, 0, 5));
    cameraOBJ->AddComponent(new FreeLook());
    cameraOBJ->AddComponent(new FreeMove());
    cameraOBJ->AddComponent(new AudioListener());
    AddToScene(cameraOBJ);

    audioOBJ->AddComponent(new AudioSource("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Ed Sheeran - Afire Love.mp3", 1));
    audioOBJ->AddComponent(new TestA());
    AddToScene(audioOBJ);

}
