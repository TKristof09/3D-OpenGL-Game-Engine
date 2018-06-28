#include "Game.h"
#include "RenderingEngine.h"

void Game::Render(RenderingEngine* renderingEngine)
{
	renderingEngine->Render(m_root);
}
