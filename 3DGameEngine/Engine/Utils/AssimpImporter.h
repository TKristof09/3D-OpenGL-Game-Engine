#ifndef ASSIMPIMPORTER_H
#define ASSIMPIMPORTER_H
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Rendering/Mesh.h"
#include "../Rendering/Material.h"
class GameObject;

class AssimpImporter {
public:
	
	GameObject* LoadFile(const std::string& path);
private:
	Mesh* AiMeshToMesh(aiMesh* mesh);
	void ProcessNode(const aiNode* node ,const aiScene* scene, GameObject* gameObject);
	Material* ProcessMaterial(const aiMaterial* material);

	std::string directory;
	
};
#endif
