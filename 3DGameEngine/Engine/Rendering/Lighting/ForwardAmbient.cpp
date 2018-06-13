#include "ForwardAmbient.h"
#include "..\Engine\Core\RenderingEngine.h"


ForwardAmbient::ForwardAmbient()
{
	AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Shaders\\forward-ambient", GL_VERTEX_SHADER);
	AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Shaders\\forward-ambient-PBR", GL_FRAGMENT_SHADER);
}

void ForwardAmbient::UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material& material,
                                    RenderingEngine* renderingEngine) const
{
	material.GetTexture("albedo").Bind();
	renderingEngine->envMap->Bind();
	SetUniform("albedoMap", 0);
	material.GetTexture("normal").Bind(1);
	SetUniform("normalMap", 1);
	material.GetTexture("metallic").Bind(2);
	SetUniform("metallicMap", 2);
	material.GetTexture("roughness").Bind(3);
	SetUniform("roughnessMap", 3);
	material.GetTexture("ao").Bind(4);
	SetUniform("aoMap", 4);

	
	renderingEngine->envMap->Bind(5);
	renderingEngine->prefilterMap->Bind(6);
	renderingEngine->brdfLUT->Bind(7);
	SetUniform("irradianceMap", 5);
	SetUniform("prefilterMap", 6);
	SetUniform("brdfLUT", 7);
	
	

	const math::Matrix4x4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
	SetUniform("MVP", MVP);
	SetUniform("model", transform.GetModel());
	SetUniform("eyePos", renderingEngine->GetMainCamera()->GetTransform().GetWorldPosition());
}
