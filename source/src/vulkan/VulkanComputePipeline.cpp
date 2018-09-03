#include <viking/vulkan/VulkanComputePipeline.hpp>

using namespace viking;
using namespace viking::vulkan;

viking::vulkan::VulkanComputePipeline::VulkanComputePipeline(VulkanDevice* device, const char* path, unsigned int x, unsigned int y, unsigned int z) :
	IComputePipeline(path,x,y,z)
{
	m_device = device;
}

viking::vulkan::VulkanComputePipeline::~VulkanComputePipeline()
{
}
#include <iostream>
void viking::vulkan::VulkanComputePipeline::createPipeline()
{
	m_descriptor_pool_sizes.clear();
	m_layout_bindings.clear();

	for (auto buffer : m_buffers)
	{
		m_descriptor_pool_sizes.push_back(VulkanInitializers::descriptorPoolSize(buffer->GetVKDescriptorType()));
		m_layout_bindings.push_back(VulkanInitializers::descriptorSetLayoutBinding(buffer->GetVKDescriptorType(), buffer->GetVKShaderStage(), buffer->GetBinding()));
	}

	VkDescriptorPoolCreateInfo descriptor_pool_create_info = VulkanInitializers::descriptorPoolCreateInfo(m_descriptor_pool_sizes, 1);
	bool success = VulkanInitializers::validate(vkCreateDescriptorPool(
		m_device->GetVulkanDevice(),
		&descriptor_pool_create_info,
		nullptr,
		&m_descriptor_pool
	));

	VkDescriptorSetLayoutCreateInfo layout_info = VulkanInitializers::descriptorSetLayoutCreateInfo(m_layout_bindings);
	success = VulkanInitializers::validate(vkCreateDescriptorSetLayout(
		m_device->GetVulkanDevice(),
		&layout_info,
		nullptr,
		&m_descriptor_set_layout
	));


	VkPipelineLayoutCreateInfo pipeline_layout_info = VulkanInitializers::pipelineLayoutCreateInfo(m_descriptor_set_layout);
	success = VulkanInitializers::validate(vkCreatePipelineLayout(
		m_device->GetVulkanDevice(),
		&pipeline_layout_info,
		nullptr,
		&m_compute_pipeline_layout
	));


	m_descriptor_set_layouts.clear();
	m_descriptor_set_layouts.push_back(m_descriptor_set_layout);
	VkDescriptorSetAllocateInfo descriptor_set_alloc_info = VulkanInitializers::descriptorSetAllocateInfo(m_descriptor_set_layouts, m_descriptor_pool);


	success = VulkanInitializers::validate(vkAllocateDescriptorSets(
		m_device->GetVulkanDevice(),
		&descriptor_set_alloc_info,
		&m_descriptor_set
	));

	std::vector<char> shaderCode = VulkanCommon::readFile(getPath());

	for (int i = 0; i < shaderCode.size(); i++)
	{
		//std::cout << shaderCode[i] << std::endl;
	}

	auto shader_module = VulkanCommon::createShaderModule(m_device, shaderCode);

	VkPipelineShaderStageCreateInfo shader_info = VulkanInitializers::pipelineShaderStageCreateInfo(shader_module, "main", VK_SHADER_STAGE_COMPUTE_BIT);
	VkComputePipelineCreateInfo compute_pipeline_create_info = VulkanInitializers::computePipelineCreateInfo(m_compute_pipeline_layout, shader_info);

	success = VulkanInitializers::validate(vkCreateComputePipelines(
		m_device->GetVulkanDevice(),
		0,
		1,
		&compute_pipeline_create_info,
		nullptr,
		&m_pipeline
	));


	VkDeviceSize offset = 0;
	m_write_descriptor_sets.clear();
	for (auto buffer : m_buffers)
	{
		if (buffer->GetDescriptorType() == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
		{
			m_write_descriptor_sets.push_back(VulkanInitializers::writeDescriptorSet(m_descriptor_set, buffer->GetDescriptorImageInfo(), buffer->GetVKDescriptorType(), buffer->GetBinding()));
		}
		else
		{
			m_write_descriptor_sets.push_back(VulkanInitializers::writeDescriptorSet(m_descriptor_set, buffer->GetDescriptorBufferInfo(), buffer->GetVKDescriptorType(), buffer->GetBinding()));
		}
	}
	vkUpdateDescriptorSets(m_device->GetVulkanDevice(), (uint32_t)m_write_descriptor_sets.size(), m_write_descriptor_sets.data(), 0, NULL);

}

void viking::vulkan::VulkanComputePipeline::destroyPipeline()
{
	vkDestroyPipelineLayout(m_device->GetVulkanDevice(), m_compute_pipeline_layout, nullptr);
	vkDestroyPipeline(m_device->GetVulkanDevice(), m_pipeline, nullptr);
}

void viking::vulkan::VulkanComputePipeline::attachBuffer(IUniformBuffer * buffer)
{
	m_buffers.push_back(dynamic_cast<VulkanUniformBuffer*>(buffer));
}

void viking::vulkan::VulkanComputePipeline::build()
{
	rebuildPipeline();
}

void viking::vulkan::VulkanComputePipeline::attachToCommandBuffer(VkCommandBuffer & command_buffer)
{
	vkCmdBindPipeline(
		command_buffer,
		VK_PIPELINE_BIND_POINT_COMPUTE,
		m_pipeline
	);
	vkCmdBindDescriptorSets(
		command_buffer,
		VK_PIPELINE_BIND_POINT_COMPUTE,
		m_compute_pipeline_layout,
		0,
		1,
		&m_descriptor_set,
		0,
		0
	);
	vkCmdDispatch(
		command_buffer,
		getX(),
		getY(),
		getZ()
	);
}
