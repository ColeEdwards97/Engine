#include "engpch.h"

#include "OpenGLTexture.h"

#include <stb_image.h>

namespace Engine
{

	OpenGLTexture2D::OpenGLTexture2D(int width, int height)
		: m_Width(width), m_Height(height)
	{

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
		m_NChannels = 4;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}

	OpenGLTexture2D::OpenGLTexture2D(std::string& path)
		: m_Path(path)
	{

		// Load the specified image
		stbi_uc* data = nullptr;
		int width, height, nChannels;

		data = stbi_load(path.c_str(), &width, &height, &nChannels, 0);
		ENGINE_CORE_ASSERT(data, "Failed to load texture at!");
		
		m_Width = width;
		m_Height = height;
		m_NChannels = nChannels;

		// Determine format to use
		GLenum internalFormat = 0;
		GLenum dataFormat = 0;

		if (nChannels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		if (nChannels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		// Create and Bind GL Texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}
	
	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	}

}