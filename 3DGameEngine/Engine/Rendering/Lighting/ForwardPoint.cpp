#include "ForwardPoint.h"
#include "..\Engine\Core\RenderingEngine.h"
#include "..\Engine\GameComponents\Lighting.h"


ForwardPoint::ForwardPoint()
{
	AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\forward-point", GL_VERTEX_SHADER);
	AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\forward-point", GL_FRAGMENT_SHADER);
}


void ForwardPoint::UpdateUniforms(const Transform& transform, /*const Camera& camera,*/ const Material& material,
                                  RenderingEngine* renderingEngine) const
{
	material.GetTexture("diffuse").Bind();
	material.GetTexture("specular").Bind(1);
	Shader::SetUniform("specular", 1);
	const math::Matrix4x4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
	Shader::SetUniform("MVP", MVP);
	Shader::SetUniform("color", material.GetVector3("color"));
	Shader::SetUniform("model", transform.GetModel());
	Shader::SetUniform("specularExponent", material.GetFloat("specularExponent"));
	Shader::SetUniform("eyePos", renderingEngine->GetMainCamera()->GetTransform().GetWorldPosition());
	SetUniform("pointLight", *dynamic_cast<const PointLight*>(renderingEngine->GetActiveLight()));
}

void ForwardPoint::SetUniform(std::string uniform, const Attenuation& attenuation) const
{
	std::string exponent = uniform + ".exponent";

	Shader::SetUniform(exponent, attenuation.GetExponent());

	std::string linear = uniform + ".linear";

	Shader::SetUniform(linear, attenuation.GetLinear());

	std::string constant = uniform + ".constant";

	Shader::SetUniform(constant, attenuation.GetConstant());
}

void ForwardPoint::SetUniform(std::string uniform, const PointLight& pointLight) const
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
