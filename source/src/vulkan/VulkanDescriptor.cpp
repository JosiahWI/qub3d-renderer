#include <viking/vulkan/VulkanDescriptor.hpp>

using namespace viking::vulkan;

viking::vulkan::VulkanDescriptor::VulkanDescriptor(DescriptorType descriptor_type, ShaderStage shader_stage, unsigned int binding) :
	IDescriptor(descriptor_type, shader_stage, binding)
{
	m_descriptor_type = ToVKDescriptorType(GetDescriptorType());
	m_shader_stage = ToVKShaderStage(GetShaderStage());
}

VkShaderStageFlags viking::vulkan::VulkanDescriptor::GetVKShaderStage()
{
	return m_shader_stage;
}

VkDescriptorType viking::vulkan::VulkanDescriptor::GetVKDescriptorType()
{
	return m_descriptor_type;
}

VkDescriptorImageInfo& viking::vulkan::VulkanDescriptor::GetDescriptorImageInfo()
{
	return m_image_info;
}

VkDescriptorBufferInfo& viking::vulkan::VulkanDescriptor::GetDescriptorBufferInfo()
{
	return m_buffer_info;
}

VkShaderStageFlags viking::vulkan::VulkanDescriptor::ToVKShaderStage(ShaderStage shader_stage)
{
	switch (shader_stage)
	{
	case ShaderStage::VERTEX_SHADER:
		return VK_SHADER_STAGE_VERTEX_BIT;
		break;
	case ShaderStage::FRAGMENT_SHADER:
		return VK_SHADER_STAGE_FRAGMENT_BIT;
		break;
	case ShaderStage::COMPUTE_SHADER:
		return VK_SHADER_STAGE_COMPUTE_BIT;
		break;
	case ShaderStage::GEOMETRY_SHADER:
		return VK_SHADER_STAGE_GEOMETRY_BIT;
		break;
	}
	return VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM;
}

VkDescriptorType viking::vulkan::VulkanDescriptor::ToVKDescriptorType(DescriptorType descriptor_type)
{
	switch (descriptor_type)
	{
	case DescriptorType::UNIFORM:
		return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		break;
	}
	return VK_DESCRIPTOR_TYPE_MAX_ENUM;
}
