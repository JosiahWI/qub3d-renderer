#include <viking/IDescriptor.hpp>

using namespace viking;

viking::IDescriptor::IDescriptor()
{
	m_shader_stage = ShaderStage::VERTEX_SHADER;
	m_binding = 0;
}

viking::IDescriptor::IDescriptor(DescriptorType descriptor_type, ShaderStage shader_stage, unsigned int binding)
{
	m_descriptor_type = descriptor_type;
	m_shader_stage = shader_stage;
	m_binding = binding;
}

viking::IDescriptor::~IDescriptor()
{
}

ShaderStage viking::IDescriptor::GetShaderStage()
{
	return m_shader_stage;
}

DescriptorType viking::IDescriptor::GetDescriptorType()
{
	return m_descriptor_type;
}

unsigned int viking::IDescriptor::GetBinding()
{
	return m_binding;
}
