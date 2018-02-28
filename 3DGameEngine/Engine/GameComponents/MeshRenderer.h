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
	void Render(const Transform& transform, Shader* shader) override
	{
		shader->Bind();
		shader->Update(transform, *m_material);

		m_mesh->Draw();
	};

private:
	Mesh* m_mesh;
	Material* m_material;
};

#endif // !MESHRENDERER_H
