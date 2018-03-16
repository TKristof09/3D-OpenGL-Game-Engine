#include "FreeLook.h"
#include "..\Core\Input.h"
#include <iostream>
#include <glm\ext.hpp>

FreeLook::FreeLook()
{
}

FreeLook::~FreeLook()
{
}

void FreeLook::Input()
{
    if(Input::GetKeyDown(SDL_SCANCODE_W))
    {
        GetTransform()->Rotate(glm::radians(1.0f), GetTransform()->GetRight());
    }
    if (Input::GetKeyDown(SDL_SCANCODE_S))
    {
        GetTransform()->Rotate(glm::radians(-1.0f), GetTransform()->GetRight());
    }
    if (Input::GetKeyDown(SDL_SCANCODE_D))
    {
        GetTransform()->Rotate(glm::radians(-1.0f), glm::vec3(0,1,0));
    }
    if (Input::GetKeyDown(SDL_SCANCODE_A))
    {
        GetTransform()->Rotate(glm::radians(1.0f), glm::vec3(0,1,0));
    }
    if (Input::GetKeyDown(SDL_SCANCODE_BACKSPACE))
    {
        std::cout << "Position: " << to_string(GetTransform()->GetPosition()) << std::endl;
        std::cout << "Rotation: " << to_string(GetTransform()->GetRotation()) << std::endl;
        std::cout << "Forward: " << to_string(GetTransform()->GetForward()) << std::endl;
        std::cout << "Up: " << to_string(GetTransform()->GetUp()) << std::endl;
        std::cout << "Right: " << to_string(GetTransform()->GetRight()) << std::endl;
        std::cout << "\n" << std::endl;
    }
}
