#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "GameComponent.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Material.h"
#include "../Rendering/Shader.h"
#include "../GameComponents/Animator.h"

class MeshRenderer : public GameComponent
{
public:
	MeshRenderer(Mesh* mesh, Material* material):
		mesh(mesh),
		material(material) {}

	void Render(const Shader* shader, RenderingEngine* renderingEngine) override
	{
		shader->Bind();
		shader->SetUniform("animated", int(false));
		shader->UpdateUniforms(*GetTransform(), *material, renderingEngine);

		mesh->Draw();
	};

	Mesh* mesh;
	Material* material;

};

class AnimatedMeshRenderer : public MeshRenderer
{
public:
    AnimatedMeshRenderer(AnimatedMesh* mesh, Material* material):
        MeshRenderer(mesh, material){}

    void Render(const Shader* shader, RenderingEngine* renderingEngine) override
    {
        shader->Bind();
		shader->SetUniform("animated", int(true));
		shader->SetUniform("bones", static_cast<AnimatedMesh*>(mesh)->GetBones());
        shader->UpdateUniforms(*GetTransform(), *material, renderingEngine, true);
        mesh->Draw();

    }

};

#endif // !MESHRENDERER_H
