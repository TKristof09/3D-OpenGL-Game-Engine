#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "GameComponent.h"
#include "..\Rendering\Mesh.h"
#include "..\Rendering\Material.h"
#include "..\Rendering\Shader.h"

class MeshRenderer : public GameComponent
{
public:
	MeshRenderer(const Mesh& mesh, const Material& material):
        m_mesh(mesh),
		m_material(material)
    {}
	void Render(const Shader* shader, RenderingEngine* renderingEngine) override
	{
        shader->Bind();
		shader->UpdateUniforms(*GetTransform(), m_material, renderingEngine);

		m_mesh.Draw();
	};

private:
	Mesh m_mesh;
	Material m_material;
};

#endif // !MESHRENDERER_H
