#include <viking/vulkan/VulkanUniformBuffer.hpp>
#include <viking/vulkan/VulkanCommon.hpp>
#include <viking/vulkan/VulkanDevice.hpp>

using namespace viking::vulkan;

viking::vulkan::VulkanUniformBuffer::VulkanUniformBuffer(VulkanDevice* device, void* dataPtr, unsigned int indexSize, unsigned int elementCount, DescriptorType descriptor_type, ShaderStage shader_stage, unsigned int binding) :
	VulkanBuffer(device,dataPtr,indexSize,elementCount, 
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),
	VulkanDescriptor(descriptor_type,shader_stage, binding), IDescriptor(descriptor_type, shader_stage, binding)
{
	VkDeviceSize offset = 0;
	m_buffer_info = VulkanInitializers::descriptorBufferInfo(m_buffer.buffer, (uint32_t)m_buffer.size, offset);
}

viking::vulkan::VulkanUniformBuffer::~VulkanUniformBuffer()
{
}