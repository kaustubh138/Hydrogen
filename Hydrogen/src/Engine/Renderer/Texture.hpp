#pragma once

namespace Hydrogen
{
	class Texture
	{
	public: 
		virtual ~Texture() = default;
		
		virtual std::size_t GetWidth() const = 0;
		virtual std::size_t GetHeight() const = 0;

		virtual void Bind(std::size_t slot = 0) const = 0;
	};

	class Texture2D
		: public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string & path, const std::string& debug_name);
	};
}