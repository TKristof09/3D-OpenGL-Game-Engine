#include "ForwardAmbient.h"
#include "../Engine/Core/RenderingEngine.h"
#include "../Engine/Utils/FileLoader.h"

ForwardAmbient::ForwardAmbient()
{
	AddShader(GetPath("Shaders/forward-ambient"), GL_VERTEX_SHADER);
	AddShader(GetPath("Shaders/forward-ambient-PBR"), GL_FRAGMENT_SHADER);
}

void ForwardAmbient::UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material& material,
                                    RenderingEngine* renderingEngine, bool animated) const
{
    SetUniform("animated", animated);

	material.GetTexture("albedo").Bind();
	SetUniform("albedoMap", 0);
	material.GetNormal("normal").Bind(1);
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
	SetUniform("ambientIntesnity", 1.0f);
	SetUniform("color", material.GetVector3("color"));
}
