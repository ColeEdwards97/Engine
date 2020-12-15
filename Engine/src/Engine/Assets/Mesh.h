#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Renderer/Buffer.h"

namespace Engine
{

	class Mesh
	{

	public:

		Mesh() {}
		Mesh(float* vertices, uint32_t* indices)
			: m_Vertices(vertices), m_Indices(indices)
		{}

		~Mesh() {}

		float& GetVertices() { return *m_Vertices; }
		uint32_t& GetIndices() { return *m_Indices; }

	private:

		float* m_Vertices;
		uint32_t* m_Indices;

	};

}