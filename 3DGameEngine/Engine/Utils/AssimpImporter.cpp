#include "AssimpImporter.h"
#include <iostream>
#include "../Core/GameObject.h"
#include "../GameComponents/MeshRenderer.h"
#include "../Core/time.h"

GameObject* AssimpImporter::LoadFile(const std::string& path)
{
	Assimp::Importer importer;
	double t = Time::GetTime();
	const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	t = Time::GetTime() - t;
	std::cout << "Assimp loaded: " << path << " in : " << t << " seconds" << std::endl;
	t = Time::GetTime();

	if(!scene)
	{
		std::cerr << importer.GetErrorString() << std::endl;
		return nullptr;
	}

	directory = path.substr(0, path.find_last_of('\\'));
	//process scene
	std::string name = path.substr(path.find_last_of('\\'), path.find_last_of('.'));
	GameObject* root = new GameObject(name);
	ProcessNode(scene->mRootNode, scene, root);
	t = Time::GetTime() - t;
	std::cout << "Processed: " << path << " in : " << t << " seconds" << std::endl;
	return root;
}

Mesh* AssimpImporter::AiMeshToMesh(aiMesh* mesh)
{
	Model model;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		if(mesh->HasTextureCoords(0))
		{
			vertex.textCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.textCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.textCoords = math::Vector2(0);
		}

		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;

		vertex.tangent.x = mesh->mTangents[i].x;
		vertex.tangent.y = mesh->mTangents[i].y;
		vertex.tangent.z = mesh->mTangents[i].z;

		model.vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; ++j)
		{
			model.indices.push_back(face.mIndices[j]);
		}
	}
	Mesh* result = new Mesh(model);
	return result;
	
}


void AssimpImporter::ProcessNode(const aiNode* node, const aiScene* scene, GameObject* gameObject)
{
	aiVector3D pos, scale;
	aiQuaternion rot;
	node->mTransformation.Decompose(scale, rot, pos);
	gameObject->GetTransform()->SetPosition(math::Vector3(pos.x, pos.y, pos.z));
	//need to divide scale by 100 because aiProcess_GlobalScale doesn't work for some reason so objects are way too big
	gameObject->GetTransform()->SetScale(math::Vector3(scale.x, scale.y, scale.z));
	gameObject->GetTransform()->SetRotation(math::Quaternion(rot.w, rot.x, rot.y, rot.z));

	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		
		gameObject->AddComponent(new MeshRenderer(AiMeshToMesh(mesh), ProcessMaterial(scene->mMaterials[mesh->mMaterialIndex])));
		
	}
	for (int i = 0; i < node->mNumChildren; ++i)
	{
		scene->mRootNode->mChildren[i]->mName.length;
		if(scene->mRootNode->mChildren[i]->mName.length != 0)
		{
			const char* name = scene->mRootNode->mChildren[i]->mName.C_Str();
			ProcessNode(node->mChildren[i], scene, gameObject->AddChild(new GameObject(name)));
		}
		else
			ProcessNode(node->mChildren[i], scene, gameObject->AddChild(new GameObject()));
	}
}

Material* AssimpImporter::ProcessMaterial(const aiMaterial* material)
{
	Material* result = new Material();

	aiString dName;	;
	if(material->GetTexture(aiTextureType_DIFFUSE, 0, &dName) == aiReturn_SUCCESS)
	{
		TextureConfig diffuseConfig;
		diffuseConfig.path = directory + "\\" + dName.C_Str();
		Texture* diffuse = new Texture(diffuseConfig);
		result->AddTexture("diffuse", diffuse);
	}

	aiString spName;	;
	if (material->GetTexture(aiTextureType_SPECULAR, 0, &spName) == aiReturn_SUCCESS)
	{
		TextureConfig specConfig;
		specConfig.path = directory + "\\" + spName.C_Str();
		Texture* specular = new Texture(specConfig);
		result->AddTexture("specular", specular);
	}
	result->AddFloat("specularExponent", 32);
	return result;

}


