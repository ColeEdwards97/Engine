#pragma once

#include "engpch.h"

#include "Engine/Renderer/Texture.h"
#include <glad/glad.h>

namespace Engine
{

	class OpenGLTexture2D : public Texture2D
	{

	public:
		OpenGLTexture2D(int width, int height);
		OpenGLTexture2D(std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetTextureID() const override { return m_TextureID; }

		virtual void Bind(uint32_t slot = 0) const override;

	private:
		std::string m_Path;
		uint32_t m_TextureID;
		uint32_t m_Width, m_Height;
		uint32_t m_NChannels;
		GLenum m_InternalFormat, m_DataFormat;
	};

}