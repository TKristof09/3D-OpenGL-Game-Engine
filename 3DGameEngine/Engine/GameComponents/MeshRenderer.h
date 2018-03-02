#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "GameComponent.h"
#include "..\Rendering\Mesh.h"
#include "..\Rendering\Material.h"
#include "..\TestGame.h"

//extern Camera mainCamera;
class MeshRenderer : public GameComponent
{
public:
	MeshRenderer(Mesh& mesh, Material& material)
	{
		m_mesh = &mesh;
		m_material = &material;
	}
	void Render(const Transform& transform, Shader* shader, RenderingEngine* renderingEngine) override
	{
		shader->Bind();
		shader->UpdateUniforms(transform, *m_material, renderingEngine);

		m_mesh->Draw();
	};

private:
	Mesh* m_mesh;
	Material* m_material;
};

#endif // !MESHRENDERER_H
