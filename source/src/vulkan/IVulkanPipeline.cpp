#include <viking/vulkan/IVulkanPipeline.hpp>

using namespace viking::vulkan;

viking::vulkan::IVulkanPipeline::~IVulkanPipeline()
{

}

VkPipeline& viking::vulkan::IVulkanPipeline::getPipeline()
{
	return m_pipeline;
}

void viking::vulkan::IVulkanPipeline::rebuildPipeline()
{
	if(m_created)destroyPipeline();
	createPipeline();
	m_created = true;
}
