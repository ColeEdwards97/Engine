#include "engpch.h"

#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>


namespace Engine
{

	Model* ModelLoader::LoadModel(const std::string& path)
	{

		Assimp::Importer importer;
		const aiScene* paiscene = importer.ReadFile(path.c_str(), (aiProcess_Triangulate | aiProcess_FlipUVs));

		if (!paiscene || paiscene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !paiscene->mRootNode)
		{
			ENGINE_CORE_ERROR("Error Loading Model: {0}\n{1}", path.c_str(), importer.GetErrorString());
			return nullptr; // TODO;
		}

		return &ProcessAssimpNode(paiscene->mRootNode, paiscene);

	}

	Model ModelLoader::ProcessAssimpNode(const aiNode* painode, const aiScene* paiscene)
	{
		Model model;

		// process this nodes meshes
		for (unsigned int i = 0; i < painode->mNumMeshes; i++)
		{
			aiMesh* paimesh = paiscene->mMeshes[painode->mMeshes[i]];
			model.m_Meshes.push_back(&ProcessAssimpMesh(paimesh));
		}

		// process the nodes child nodes
		for (unsigned int i = 0; i < painode->mNumChildren; i++)
		{
			ProcessAssimpNode(painode->mChildren[i], paiscene);
		}
	}

	Mesh ModelLoader::ProcessAssimpMesh(const aiMesh* paimesh)
	{
		// vertices & normals
		std::vector<float> vertices;
		for (unsigned int i = 0; i < paimesh->mNumVertices; i += 6)
		{
			// layout
			vertices.push_back(paimesh->mVertices[i].x);
			vertices.push_back(paimesh->mVertices[i].y);
			vertices.push_back(paimesh->mVertices[i].z);
			vertices.push_back(paimesh->mNormals[i].x);
			vertices.push_back(paimesh->mNormals[i].y);
			vertices.push_back(paimesh->mNormals[i].z);
		}

		// texture coords
		// TODO:
		if (paimesh->mTextureCoords[0])
		{
			//glm::vec2 vec;
			//vec.x = mesh->mTextureCoords[0][i].x;
			//vec.y = mesh->mTextureCoords[0][i].y;
			//vertex.TexCoords = vec;
		}
		else
		{
			//vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		// indices
		std::vector<uint32_t> indices;
		for (unsigned int i = 0; i < paimesh->mNumFaces; i++)
		{
			aiFace aiface = paimesh->mFaces[i];
			for (unsigned int j = 0; j < aiface.mNumIndices; j++)
			{
				indices.push_back(aiface.mIndices[j]);
			}
		}

		Mesh mesh(&vertices[0], &indices[0]);
		return mesh;
	}

}