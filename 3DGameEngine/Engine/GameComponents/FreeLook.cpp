#include "FreeLook.h"
#include "../Core/Input.h"
#include <iostream>

void FreeLook::Update()
{
	if (Input::GetKeyDown(SDL_SCANCODE_W))
	{
		GetTransform()->Rotate(math::ToRadians(-1.0f), GetTransform()->GetRight());
	}
	if (Input::GetKeyDown(SDL_SCANCODE_S))
	{
		GetTransform()->Rotate(math::ToRadians(1.0f), GetTransform()->GetRight());
	}
	if (Input::GetKeyDown(SDL_SCANCODE_D))
	{
		GetTransform()->Rotate(math::ToRadians(-1.0f), math::Vector3(0, 1, 0));
	}
	if (Input::GetKeyDown(SDL_SCANCODE_A))
	{
		GetTransform()->Rotate(math::ToRadians(1.0f), math::Vector3(0, 1, 0));
	}
	if (Input::GetKeyDown(SDL_SCANCODE_BACKSPACE))
	{
		std::cout << "Position: " << math::ToString(GetTransform()->GetWorldPosition()) << std::endl;
		std::cout << "Rotation: " << math::ToString(GetTransform()->GetRotation()) << std::endl;
		std::cout << "Forward: " << math::ToString(GetTransform()->GetForward()) << std::endl;
		std::cout << "Up: " << math::ToString(GetTransform()->GetUp()) << std::endl;
		std::cout << "Right: " << math::ToString(GetTransform()->GetRight()) << std::endl;
		std::cout << "\n" << std::endl;
	}
}
