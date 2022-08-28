#pragma once

namespace Hydrogen
{
	enum ShaderDataType
		: uint8_t
	{
		None = 0,
		Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Bool
	};

	static std::size_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::None:		return 0;
			
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;

			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;

			case ShaderDataType::Mat3:		return 4 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
		
			case ShaderDataType::Bool:		return 1;
		
			default:						H2_CORE_ASSERT(false, "Unknown Shader data type!"); return 0;
		}
	}
}