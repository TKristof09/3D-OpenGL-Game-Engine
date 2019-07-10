#include "AssimpImporter.h"
#include <iostream>
#include <assimp/cimport.h>
#include "../Core/GameObject.h"
#include "../GameComponents/MeshRenderer.h"
#include "../Core/Time.h"
#include "../GameComponents/Animator.h"
#include "../Core/Game.h"


GameObject* AssimpImporter::LoadFile(const std::string& path, Game* game, const std::string& name)
{
	m_game = game;
	Assimp::Importer importer;
	double t = Time::GetTime();
	const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	//aiApplyPostProcessing(scene, aiProcess_CalcTangentSpace);
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
	//std::string name = path.substr(path.find_last_of('\\') + 1, path.find_last_of('.'));
	GameObject* root;
	if(name == "")
		root = new GameObject(scene->mRootNode->mName.C_Str());
	else
		root = new GameObject(name);
	std::cout<<scene->mNumAnimations<<std::endl;
	m_globalInverse = math::Matrix4x4(scene->mRootNode->mTransformation.Inverse());
	ProcessNode(scene->mRootNode, scene, root);
	m_game->AddToScene(root);
	ProcessAnimations(scene);	
	t = Time::GetTime() - t;
	std::cout << "Processed: " << path << " in : " << t << " seconds" << std::endl;
	return root;
}

Animation* AssimpImporter::LoadAnimation(aiAnimation* animation)
{
	std::cout << "LOADED ANIMATION: " << animation->mName.C_Str() << std::endl;
	Animation* result = new Animation(animation->mName.C_Str(), animation->mDuration, animation->mTicksPerSecond);
	for(size_t i = 0; i < animation->mNumChannels; i++)
	{
		auto currentChannel = animation->mChannels[i];
		std::cout << i << currentChannel->mNodeName.C_Str()<<std::endl;
		std::vector<KeyFrame> keyframes;
		unsigned int numPosKeys = currentChannel->mNumPositionKeys;
		unsigned int numRotKeys = currentChannel->mNumRotationKeys;
		unsigned int numScaleKeys = currentChannel->mNumScalingKeys;
		math::Vector3 pos, scale;
		math::Quaternion rot;
		assert(numPosKeys == numRotKeys && numPosKeys == numScaleKeys);
		for(unsigned int i = 0; i < currentChannel->mNumPositionKeys - 1; i++)
		{
			auto poskey = currentChannel->mPositionKeys[i];
			pos = math::Vector3(poskey.mValue);
			auto rotkey = currentChannel->mRotationKeys[i];
			rot = math::normalize(math::Quaternion(rotkey.mValue));
			auto scalekey = currentChannel->mScalingKeys[i];
			scale = math::Vector3(scalekey.mValue);
			KeyFrame kf(currentChannel->mPositionKeys[i].mTime, pos, rot, scale);
			keyframes.push_back(kf);
		}
		auto go = m_nodes[currentChannel->mNodeName.C_Str()];
		AnimationChannel* channel = new AnimationChannel(go, m_bones[currentChannel->mNodeName.C_Str()], keyframes);
		result->AddChannel(channel);
	}
	return result;

}

Mesh* AssimpImporter::AiMeshToMesh(aiMesh* mesh)
{
	Model model;
	model.vertices.resize(mesh->mNumVertices);
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

		model.vertices[i] = vertex;
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; ++j)
		{
			model.indices.push_back(face.mIndices[j]);
		}
	}

	std::vector<Bone*> bones;
	std::vector<VertexBoneData> boneData;
	// Load the bones for skeletal animation if the mesh has any
    if(mesh->HasBones())
    {
		unsigned int boneIndex = 0;
		bones.reserve(mesh->mNumBones);
		boneData.resize(mesh->mNumVertices);
        for (unsigned int i = 0; i < mesh->mNumBones; ++i)
        {
            Bone* bone = new Bone();
            aiBone* currentBone = mesh->mBones[i];
			m_bones[currentBone->mName.C_Str()] = bone;
			bone->offsetMatrix = currentBone->mOffsetMatrix;

            for (unsigned int j = 0; j < currentBone->mNumWeights; ++j)
            {
				// TODO got a feeling that there will be a prob with this
				unsigned int vertexID = currentBone->mWeights[j].mVertexId;
				float weight = currentBone->mWeights[j].mWeight;
				boneData[vertexID].AddData(boneIndex, weight);
            }

			bones.push_back(bone);
			boneIndex++;
        }
    }

	Mesh* result = nullptr;
	if(mesh->mNumBones != 0)
	{
		std::cout << "Animated mesh : " << mesh->mName.C_Str() << std::endl;
		result = new AnimatedMesh(model, bones, boneData);
	}
	else
		result = new Mesh(model);
	return result;

}

void AssimpImporter::ProcessAnimations(const aiScene* scene)
{
	if(!scene->HasAnimations())
		return;

	for (size_t i = 0; i < scene->mNumAnimations; i++)
	{
		GameObject* object = m_game->FindGameObject(scene->mAnimations[i]->mChannels[0]->mNodeName.C_Str());
		object->AddComponent(new Animator(LoadAnimation(scene->mAnimations[i]), m_globalInverse));
	}
}

void AssimpImporter::ProcessNode(const aiNode* node, const aiScene* scene, GameObject* gameObject)
{
	m_nodes[node->mName.C_Str()] = gameObject;
	aiVector3D pos, scale;
	aiQuaternion rot;
	node->mTransformation.Decompose(scale, rot, pos);
	if(math::Vector3(100.f) == math::Vector3(scale))
	{
		std::cout << gameObject->name << " has a scale of " << math::ToString(math::Vector3(scale)) << " might be a bug of assimp, dividing scale by 100" << std::endl;
		scale /= 100.f;
	}
	gameObject->GetTransform()->SetPosition(math::Vector3(pos));
	//need to divide scale by 100 because aiProcess_GlobalScale doesn't work for some reason so objects are way too big
	std::cout << gameObject->name << " : " << math::ToString(math::Vector3(scale)) << std::endl;
	gameObject->GetTransform()->SetScale(math::Vector3(scale));
	gameObject->GetTransform()->SetRotation(math::Quaternion(rot));

	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		if(mesh->mNumBones == 0)
			gameObject->AddComponent(new MeshRenderer(AiMeshToMesh(mesh), ProcessMaterial(scene->mMaterials[mesh->mMaterialIndex])));
		else
		{
			gameObject->AddComponent(new AnimatedMeshRenderer((AnimatedMesh*)AiMeshToMesh(mesh), ProcessMaterial(scene->mMaterials[mesh->mMaterialIndex])));
			m_animatedObject = gameObject;
		}

	}
	for (int i = 0; i < node->mNumChildren; ++i)
	{
		if(node->mChildren[i]->mName.length != 0)
		{
			const char* name = node->mChildren[i]->mName.C_Str();
			ProcessNode(node->mChildren[i], scene, gameObject->AddChild(new GameObject(name)));
		}
		else
			ProcessNode(node->mChildren[i], scene, gameObject->AddChild(new GameObject()));
	}
}

Material* AssimpImporter::ProcessMaterial(const aiMaterial* material)
{
	Material* result = new Material();

	aiString dName;
	if(material->GetTexture(aiTextureType_DIFFUSE, 0, &dName) == aiReturn_SUCCESS)
	{
		TextureConfig diffuseConfig;
		diffuseConfig.path = GetPath(dName.C_Str());
		Texture* diffuse = new Texture(diffuseConfig);
		result->AddTexture("albedo", diffuse);
	}

	aiString normalName;
	if (material->GetTexture(aiTextureType_NORMALS, 0, &normalName) == aiReturn_SUCCESS)
	{
		TextureConfig normalConfig;
        normalConfig.path = GetPath(normalName.C_Str());
		Texture* normal = new Texture(normalConfig);
		result->AddTexture("normal", normal);
	}

	return result;

}


