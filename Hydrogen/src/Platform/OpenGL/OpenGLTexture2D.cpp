#include "pch.hpp"
#include "OpenGLTexture2D.hpp"

#include <stb_image.h>

namespace Hydrogen
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, const std::string& debug_name = "")
		: m_TexturePath(path), m_DebugName(debug_name), m_BPP(0)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		H2_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(std::size_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}