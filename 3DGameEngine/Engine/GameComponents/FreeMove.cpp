#include "FreeMove.h"

#include "..\Core\Input.h"
#include <iostream>

FreeMove::FreeMove()
{
}

FreeMove::~FreeMove()
{
}

void FreeMove::Input()
{
    if (Input::GetKeyDown(SDL_SCANCODE_UP))
    {
        GetTransform()->Translate(GetTransform()->GetForward(), 0.1f);
    }
    if (Input::GetKeyDown(SDL_SCANCODE_DOWN))
    {
        GetTransform()->Translate(GetTransform()->GetForward(), -0.1f);
    }
    if (Input::GetKeyDown(SDL_SCANCODE_RIGHT))
    {
        GetTransform()->Translate(GetTransform()->GetRight(), 0.1f);
    }
    if (Input::GetKeyDown(SDL_SCANCODE_LEFT))
    {
        GetTransform()->Translate(GetTransform()->GetRight(), -0.1f);
    }
    if (Input::GetKeyDown(SDL_SCANCODE_SPACE))
    {
        GetTransform()->Translate(GetTransform()->GetUp(), 0.1f);
    }
    if (Input::GetKeyDown(SDL_SCANCODE_LCTRL))
    {
        GetTransform()->Translate(GetTransform()->GetUp(), -0.1f);
    }
}
