#pragma once

#include <viking\ShaderStage.hpp>

namespace viking 
{
	enum DescriptorType
	{
		UNIFORM
	};
	class IDescriptor
	{
	public:
		IDescriptor();
		IDescriptor(DescriptorType descriptor_type,ShaderStage shader_stage, unsigned int binding);
		~IDescriptor();
		ShaderStage GetShaderStage();
		DescriptorType GetDescriptorType();
		unsigned int GetBinding();
	private:
		DescriptorType m_descriptor_type;
		ShaderStage m_shader_stage;
		unsigned int m_binding;
	};
}