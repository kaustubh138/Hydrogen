#pragma once

namespace Hydrogen
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vs_path, const std::string& fs_path, const std::string& name);
	};
}

