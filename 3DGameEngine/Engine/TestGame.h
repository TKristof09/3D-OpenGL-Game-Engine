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
#include "Rendering\Lighting\BaseLight.h"
#include "Rendering\Lighting\DirectionalLight.h"
#include "Camera.h"

#include <glm\ext.hpp>
class TestGame : public Game
{
public:
	TestGame();
	~TestGame();
	void Init() override;
	void Render() override;
	void Update() override;
	void Input() override;
private:
	PhongShader* m_shader;
	Mesh* m_mesh;
	Transform* m_transform;
	Camera* m_camera;
	Material* m_material;
	Texture* m_texture;
	DirectionalLight directionalLight;
	PointLight pointLights[2] = {};
	SpotLight spotLights[1] = {};
};

#endif // !TESTGAME_H