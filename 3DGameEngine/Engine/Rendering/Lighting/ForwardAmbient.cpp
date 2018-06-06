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
//	renderingEngine->brdfLUT->Bind(7);
	renderingEngine->envMap->Bind(5);
	Bind();
	material.GetTexture("albedo").Bind();
	renderingEngine->GetBackground()->Bind();
	Shader::SetUniform("albedoMap", 0);
	material.GetTexture("normal").Bind(1);
	Shader::SetUniform("normalMap", 1);
	material.GetTexture("metallic").Bind(2);
	Shader::SetUniform("metallicMap", 2);
	material.GetTexture("roughness").Bind(3);
	Shader::SetUniform("roughnessMap", 3);
	material.GetTexture("ao").Bind(4);
	Shader::SetUniform("aoMap", 4);

	
	Shader::SetUniform("irradianceMap", 5);
	Shader::SetUniform("prefilterMap", 6);
	Shader::SetUniform("brdfLUT", 7);
	
	const math::Matrix4x4 MVP = renderingEngine->GetMainCamera()->GetViewProjection() * transform.GetModel();
	Shader::SetUniform("model", transform.GetModel());
	Shader::SetUniform("MVP", MVP);
	Shader::SetUniform("eyePos", renderingEngine->GetMainCamera()->GetTransform().GetWorldPosition());
	//Shader::SetUniform("color", material.GetVector3("color"));
	//Shader::SetUniform("ambientIntensity",
	//                   renderingEngine->GetAmbientLightColor().ToVector3() * renderingEngine->GetAmbientLightIntensity());
}
