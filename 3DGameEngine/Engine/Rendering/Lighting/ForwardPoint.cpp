#include "ForwardPoint.h"
#include "..\Engine\Core\RenderingEngine.h"
#include "..\Engine\GameComponents\Lighting.h"


ForwardPoint::ForwardPoint()
{
	AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Shaders\\forward-point", GL_VERTEX_SHADER);
	AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\Shaders\\forward-point-PBR", GL_FRAGMENT_SHADER);
}


void ForwardPoint::UpdateUniforms(const Transform& transform, /*const Camera& camera,*/ const Material& material,
                                  RenderingEngine* renderingEngine) const
{
	material.GetTexture("albedo").Bind();
	material.GetTexture("normal").Bind(1);
	Shader::SetUniform("normalMap", 1);
	material.GetTexture("metallic").Bind(2);
	Shader::SetUniform("metallicMap", 2);
	material.GetTexture("roughness").Bind(3);
	Shader::SetUniform("roughnessMap", 3);
	material.GetTexture("ao").Bind(4);
	Shader::SetUniform("aoMap", 4);

	const math::Matrix4x4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
	Shader::SetUniform("MVP", MVP);
	Shader::SetUniform("color", material.GetVector3("color"));
	Shader::SetUniform("model", transform.GetModel());
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
