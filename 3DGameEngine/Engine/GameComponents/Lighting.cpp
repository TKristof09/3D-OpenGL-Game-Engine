#include "Lighting.h"
#include "../Engine/Core/RenderingEngine.h"

#include "../Utils/DebuggingMacros.h"
#include "../Rendering/DebugDrawer.h"

void BaseLight::AddToRenderingEngine(RenderingEngine* renderingEngine)
{
#if DEBUG_LIGHT_DIRECTION == 1
	DebugLineDrawer::AddLine(math::rotate(math::Vector3(0, 0, -1), GetTransform()->GetWorldRotation()));
#endif

	renderingEngine->AddLight(*this);
}
