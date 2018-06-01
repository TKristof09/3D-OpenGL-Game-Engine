#include "ForwardAmbient.h"
#include "..\Engine\Core\RenderingEngine.h"


ForwardAmbient::ForwardAmbient()
{
	AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\forward-ambient", GL_VERTEX_SHADER);
	AddShader("A:\\Programozas\\C++\\3DGameEngine\\3DGameEngine\\res\\forward-ambient", GL_FRAGMENT_SHADER);
}

void ForwardAmbient::UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material& material,
                                    RenderingEngine* renderingEngine) const
{
	material.GetTexture("albedo").Bind();
	material.GetTexture("normal").Bind(1);
	Shader::SetUniform("normalMap", 1);
	material.GetTexture("rougness").Bind(2);
	Shader::SetUniform("roughnessMap", 2);
	
	//Shader::SetUniform("irradianceMap", 3);
	const math::Matrix4x4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
	Shader::SetUniform("model", transform.GetModel());
	Shader::SetUniform("MVP", MVP);
	Shader::SetUniform("color", material.GetVector3("color"));
	Shader::SetUniform("ambientIntensity",
	                   renderingEngine->GetAmbientLightColor().ToVector3() * renderingEngine->GetAmbientLightIntensity());
}
