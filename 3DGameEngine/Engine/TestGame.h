#ifndef TESTGAME_H
#define TESTGAME_H
#include "Core\Game.h"
#include "Core\Input.h"
#include "Core\Transform.h"
#include "Rendering\Mesh.h"
#include "Rendering\Shader.h"
#include "Rendering\Texture.h"
#include "Rendering\PhongShader.h"
#include "Rendering\Material.h"
#include "Rendering\Lighting\DirectionalLight.h"
#include "Camera.h"
#include "Core\GameObject.h"
#include "GameComponents\MeshRenderer.h"

#include <glm\ext.hpp>



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
	MeshRenderer* meshRenderer2;

	//PhongShader* m_shader;
	Mesh* m_mesh;
	Mesh* mesh2;
	Camera* m_camera;
	Material* m_material;
	Material* material2;
	Texture* m_texture;
};

#endif // !TESTGAME_H