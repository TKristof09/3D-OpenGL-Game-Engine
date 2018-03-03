#include "Lighting.h"
#include "..\Engine\Core\RenderingEngine.h"

void BaseLight::AddToEngine(RenderingEngine* renderingEngine)
{
    renderingEngine->AddLight(*this);
}