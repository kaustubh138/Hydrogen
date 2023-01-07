#pragma once
#include "Renderer/Texture.hpp"

#include "glad/glad.h"

namespace Hydrogen
{
	class OpenGLTexture2D
		: public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path, const std::string& debug_name);
		virtual ~OpenGLTexture2D();

		virtual std::size_t GetWidth() const override { return m_Width; };
		virtual std::size_t GetHeight() const override { return m_Height; };
	
		virtual void Bind(std::size_t slot = 0) const override;
	
	private:
		std::string m_TexturePath, m_DebugName;
		uint32_t m_RendererID;
		int m_Width, m_Height, m_BPP;
	};
}