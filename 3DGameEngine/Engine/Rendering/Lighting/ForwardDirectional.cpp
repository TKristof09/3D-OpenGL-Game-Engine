#include "ForwardDirectional.h"
#include "..\Engine\Core\RenderingEngine.h"
#include "..\Engine\GameComponents\Lighting.h"


ForwardDirectional::ForwardDirectional()
{
	AddShader(".\\res\\forward-directional", GL_VERTEX_SHADER);
	AddShader(".\\res\\forward-directional", GL_FRAGMENT_SHADER);
}

void ForwardDirectional::UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material& material,
                                        RenderingEngine* renderingEngine) const
{
	material.GetTexture("diffuse").Bind();

	const math::Matrix4x4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
	Shader::SetUniform("MVP", MVP);
	Shader::SetUniform("color", material.GetVector3("color"));
	Shader::SetUniform("model", transform.GetModel());
	Shader::SetUniform("specularIntensity", material.GetFloat("specularIntensity"));
	Shader::SetUniform("specularExponent", material.GetFloat("specularExponent"));
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
