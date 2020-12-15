#pragma once

#include "Engine/Assets/Model.h"

#include <assimp/scene.h>

namespace Engine
{

	class ModelLoader
	{

	public:

		static Model* LoadModel(const std::string& path);

	private:

		static Model ProcessAssimpNode(const aiNode* painode, const aiScene* paiscene);
		static Mesh ProcessAssimpMesh(const aiMesh* paimesh);

	};

}