#ifndef ASSIMPIMPORTER_H
#define ASSIMPIMPORTER_H
#include <string>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "../Rendering/Mesh.h"
#include "../Rendering/Material.h"
#include "../GameComponents/Animation.h"

class Game;
class GameObject;

class AssimpImporter {
public:

	GameObject* LoadFile(const std::string& path, Game* game, const std::string& name="");
private:
	Animation* LoadAnimation(aiAnimation* animation);
	Mesh* AiMeshToMesh(aiMesh* mesh);
	void ProcessAnimations(const aiScene* scene);
	void ProcessNode(const aiNode* node ,const aiScene* scene, GameObject* gameObject);
	Material* ProcessMaterial(const aiMaterial* material);

	std::string directory;
	Game* m_game;

	std::map<std::string, GameObject*> m_nodes;
	std::map<std::string, Bone*> m_bones;
	GameObject* m_animatedObject = nullptr;
	math::Matrix4x4 m_globalInverse;

};
#endif
