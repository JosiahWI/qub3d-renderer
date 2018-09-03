#include <viking/vulkan/VulkanComputeProgram.hpp>
#include <viking/vulkan/VulkanComputePipeline.hpp>
#include <viking/vulkan/VulkanDevice.hpp>

viking::vulkan::VulkanComputeProgram::VulkanComputeProgram(VulkanDevice * device)
{
	m_device = device;

	VkFenceCreateInfo fenceCreateInfo = VulkanInitializers::createFenceInfo();
	bool succsess = VulkanInitializers::validate(vkCreateFence(device->GetVulkanDevice(), &fenceCreateInfo, NULL, &fence));
}

viking::vulkan::VulkanComputeProgram::~VulkanComputeProgram()
{
	vkDestroyFence(m_device->GetVulkanDevice(), fence, NULL);
}

void viking::vulkan::VulkanComputeProgram::build()
{
	m_command_buffer = VulkanCommon::beginSingleTimeCommands(m_device, *m_device->GetGraphicsCommandPool());
	for (auto cp : m_pipelines)
	{
		VulkanComputePipeline* vcp = dynamic_cast<VulkanComputePipeline*>(cp);
		vcp->attachToCommandBuffer(m_command_buffer);
	}
	bool succsess = VulkanInitializers::validate(vkEndCommandBuffer(
		m_command_buffer
	));
}

void viking::vulkan::VulkanComputeProgram::run()
{
	VkSubmitInfo submitInfo = VulkanInitializers::submitInfo(m_command_buffer);

	bool succsess = VulkanInitializers::validate(vkQueueSubmit(*m_device->GetComputeQueue(), 1, &submitInfo, fence));
	succsess = VulkanInitializers::validate(vkWaitForFences(m_device->GetVulkanDevice(), 1, &fence, VK_TRUE, LONG_MAX));
}
