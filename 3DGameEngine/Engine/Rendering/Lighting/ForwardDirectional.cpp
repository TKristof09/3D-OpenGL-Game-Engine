#include "ForwardDirectional.h"
#include "../Engine/Core/RenderingEngine.h"
#include "../Engine/GameComponents/Lighting.h"
#include "../Engine/Utils/FileLoader.h"


ForwardDirectional::ForwardDirectional()
{
	AddShader(GetPath("Shaders/forward-directional"), GL_VERTEX_SHADER);
	AddShader(GetPath("Shaders/forward-directional-PBR"), GL_FRAGMENT_SHADER);
}

void ForwardDirectional::UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material& material,
                                        RenderingEngine* renderingEngine, bool animated) const
{
    Shader::SetUniform("animated", animated);

	material.GetTexture("albedo").Bind();
	material.GetNormal("normal").Bind(1);
	Shader::SetUniform("normalMap", 1);
	material.GetTexture("metallic").Bind(2);
	Shader::SetUniform("metallicMap", 2);
	material.GetTexture("roughness").Bind(3);
	Shader::SetUniform("roughnessMap", 3);
	material.GetTexture("ao").Bind(4);
	Shader::SetUniform("aoMap", 4);


	math::Matrix4x4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
	Shader::SetUniform("MVP", MVP);
	Shader::SetUniform("color", material.GetVector3("color"));
	Shader::SetUniform("model", transform.GetModel());
	Shader::SetUniform("eyePos", renderingEngine->GetMainCamera()->GetTransform().GetWorldPosition());
	SetUniform("directionalLight", *static_cast<const DirectionalLight*>(renderingEngine->GetActiveLight()));
}

void ForwardDirectional::SetUniform(std::string uniform, const DirectionalLight& directionalLight) const
{
	std::string color = uniform + ".base.color";
	Shader::SetUniform(color, directionalLight.GetColor()->ToVector3());

	std::string intensity = uniform + ".base.intensity";
	Shader::SetUniform(intensity, *directionalLight.GetIntensity());

	std::string direction = uniform + ".direction";
	Shader::SetUniform(direction, directionalLight.GetTransform().GetForward());

	
}
