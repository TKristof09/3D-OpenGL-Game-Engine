#ifndef TESTGAME_H
#define TESTGAME_H
#include "Core\Game.h"
#include "Rendering\Mesh.h"
#include "Rendering\Texture.h"
#include "Rendering\Material.h"
#include "Core\GameObject.h"
#include "GameComponents\MeshRenderer.h"


class TestGame : public Game
{
public:
	TestGame();
	~TestGame() override;
	void Init() override;
	void Update() override;
	void Input() override;
private:
	GameObject* m_root;
	MeshRenderer* m_meshRenderer;
	MeshRenderer* m_meshRenderer2;

	Mesh* m_mesh;
	Mesh* m_mesh2;
	Material* m_material;
	Material* m_material2;
	Texture* m_texture;
    Texture* m_texture2;
};

#endif // !TESTGAME_H