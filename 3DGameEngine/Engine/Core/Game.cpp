#include "Game.h"
#include "RenderingEngine.h"

void Game::Render(RenderingEngine* renderingEngine)
{
	renderingEngine->Render(m_root);
}

void Game::SetAmbientLightColor(const Color& color)
{
	m_renderingEngine->SetAmbientLightColor(color);
}

void Game::SetAmbientLightIntensity(float intensity)
{
	m_renderingEngine->SetAmbientLightIntensity(intensity);
}
