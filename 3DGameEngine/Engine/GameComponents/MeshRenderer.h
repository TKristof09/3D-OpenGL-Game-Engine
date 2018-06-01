#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "GameComponent.h"
#include "..\Rendering\Mesh.h"
#include "..\Rendering\Material.h"
#include "..\Rendering\Shader.h"

class MeshRenderer : public GameComponent
{
public:
	MeshRenderer(Mesh* mesh, Material* material):
		mesh(mesh),
		material(material) {}

	void Render(const Shader* shader, RenderingEngine* renderingEngine) override
	{
		shader->Bind();
		shader->UpdateUniforms(*GetTransform(), *material, renderingEngine);

		mesh->Draw();
	};

	
	Mesh* mesh;
	Material* material;

};

#endif // !MESHRENDERER_H
