#include "ForwardSpot.h"
#include "..\Engine\Core\RenderingEngine.h"
#include "..\Engine\GameComponents\Lighting.h"


ForwardSpot::ForwardSpot()
{
	AddShader(".\\res\\forward-spot", GL_VERTEX_SHADER);
	AddShader(".\\res\\forward-spot", GL_FRAGMENT_SHADER);
}


void ForwardSpot::UpdateUniforms(const Transform& transform, /*const Camera& camera,*/ const Material& material,
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
	SetUniform("spotLight", *dynamic_cast<const SpotLight*>(renderingEngine->GetActiveLight()));
}

void ForwardSpot::SetUniform(std::string uniform, const Attenuation& attenuation) const
{
	std::string exponent = uniform + ".exponent";

	Shader::SetUniform(exponent, attenuation.GetExponent());

	std::string linear = uniform + ".linear";

	Shader::SetUniform(linear, attenuation.GetLinear());

	std::string constant = uniform + ".constant";

	Shader::SetUniform(constant, attenuation.GetConstant());
}

void ForwardSpot::SetUniform(std::string uniform, const PointLight& pointLight) const
{
	std::string color = uniform + ".base.color";
	Shader::SetUniform(color, pointLight.GetColor()->ToVector3());

	std::string intensity = uniform + ".base.intensity";

	Shader::SetUniform(intensity, *pointLight.GetIntensity());

	std::string attenuation = uniform + ".attenuation";

	SetUniform(attenuation, *pointLight.GetAttenuation());

	std::string range = uniform + ".range";

	Shader::SetUniform(range, *pointLight.GetRange());

	std::string position = uniform + ".position";

	Shader::SetUniform(position, pointLight.GetTransform().GetWorldPosition());
}


void ForwardSpot::SetUniform(std::string uniform, const SpotLight& spotLight) const
{
	std::string pointLight = uniform + ".pointLight";
	SetUniform(pointLight, *static_cast<const PointLight*>(&spotLight));


	std::string direction = uniform + ".direction";
	Shader::SetUniform(direction, spotLight.GetTransform().GetForward());

	std::string cutoff = uniform + ".cutoff";
	Shader::SetUniform(cutoff, *spotLight.GetCutoff());
}
