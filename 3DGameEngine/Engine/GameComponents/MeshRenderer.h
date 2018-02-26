#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "GameComponent.h"
#include "..\Rendering\Mesh.h"
#include "..\Rendering\Material.h"
#include "..\Rendering\BasicShader.h"

class MeshRenderer : public GameComponent
{
public:
	MeshRenderer(Mesh* mesh, Material& material)
	{
		m_mesh = mesh;
		m_material = &material;
	}
	void Render(const Transform& transform, const Camera& camera) override
	{
		BasicShader shader = BasicShader();
		shader.Bind();
		shader.Update(transform, camera, *m_material);

		m_mesh->Draw();
	};

private:
	Mesh* m_mesh;
	Material* m_material;
};

#endif // !MESHRENDERER_H
