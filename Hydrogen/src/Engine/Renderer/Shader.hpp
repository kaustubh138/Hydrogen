#pragma once

namespace Hydrogen
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual std::string GetName() const = 0;

		static Ref<Shader> Create(const std::string& vs_path, const std::string& fs_path, const std::string& name);
		static Ref<Shader> Create(const std::string& vs_path, const std::string& fs_path);
	};
	
	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& vsPath, const std::string& fsPath);
		Ref<Shader> Load(const std::string& vsPath, const std::string& fsPath, const std::string& name);
		Ref<Shader> Get(const std::string& name);

		inline bool Exists(const std::string& name) const { return m_Shaders.find(name) != m_Shaders.end(); };
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}

