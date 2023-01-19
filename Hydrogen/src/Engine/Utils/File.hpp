#pragma once

#include "Logger.hpp"
#include "pch/pch.hpp"

namespace Hydrogen
{
	class File
	{
	public:
		static std::string Read(const std::string& path)
		{
			std::ifstream stream(path);
			if (stream)
				return std::string((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>()));
			else
				H2_CORE_WARN("Failed to read file {0}", path);
			return {};
		}
	};
}

