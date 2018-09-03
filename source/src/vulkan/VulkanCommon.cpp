#include <viking/vulkan/VulkanCommon.hpp>
#include <viking/vulkan/VulkanDevice.hpp>
#include <viking/vulkan/VulkanBuffer.hpp>
#include <viking/IDescriptor.hpp>

#include <fstream>

//#include <shaderc/shaderc.hpp>

using namespace viking::vulkan;

bool viking::vulkan::VulkanCommon::m_glslangInitialized = false;

void viking::vulkan::VulkanCommon::createImage(VulkanDevice* device, VkExtent2D extent, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage & image, VkDeviceMemory & image_memory)
{
	VkImageCreateInfo create_info = VulkanInitializers::imageCreateInfo(extent.width, extent.height, format, tiling, usage);
	bool success = VulkanInitializers::validate(vkCreateImage(
		device->GetVulkanDevice(),
		&create_info,
		nullptr,
		&image
	));

	VkMemoryRequirements mem_requirements;
	vkGetImageMemoryRequirements(
		device->GetVulkanDevice(),
		image,
		&mem_requirements
	);

	VkMemoryAllocateInfo alloc_info = VulkanInitializers::memoryAllocateInfo(mem_requirements.size, findMemoryType(
		device,
		mem_requirements.memoryTypeBits,
		properties
	));

    success = VulkanInitializers::validate(vkAllocateMemory(
		device->GetVulkanDevice(),
		&alloc_info,
		nullptr,
		&image_memory
	));

	vkBindImageMemory(
		device->GetVulkanDevice(),
		image,
		image_memory,
		0
	);
}

uint32_t viking::vulkan::VulkanCommon::findMemoryType(VulkanDevice* device, uint32_t type_filter, VkMemoryPropertyFlags properties)
{
	for (uint32_t i = 0; i < device->GetPhysicalDevice().getPhysicalDeviceMemoryProperties()->memoryTypeCount; i++)
	{
		if (type_filter & (1 << i) &&
			(device->GetPhysicalDevice().getPhysicalDeviceMemoryProperties()->memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}
	return -1;
}

void viking::vulkan::VulkanCommon::createImageView(VulkanDevice* device, VkImage image, VkFormat format, VkImageAspectFlags aspect_flags, VkImageView & view)
{
	VkImageViewCreateInfo create_info = VulkanInitializers::imageViewCreate(image, format, aspect_flags);
	bool success = VulkanInitializers::validate(vkCreateImageView(
		device->GetVulkanDevice(),
		&create_info,
		nullptr,
		&view
	));
}

VkCommandBuffer viking::vulkan::VulkanCommon::beginSingleTimeCommands(VulkanDevice* device, VkCommandPool command_pool)
{
	VkCommandBufferAllocateInfo alloc_info = VulkanInitializers::commandBufferAllocateInfo(
		command_pool,
		1
	);
	VkCommandBuffer command_buffer;
	bool success = VulkanInitializers::validate(vkAllocateCommandBuffers(
		device->GetVulkanDevice(),
		&alloc_info,
		&command_buffer
	));
	VkCommandBufferBeginInfo begin_info = VulkanInitializers::commandBufferBeginInfo(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    success = VulkanInitializers::validate(vkBeginCommandBuffer(
		command_buffer,
		&begin_info
	));
	return command_buffer;
}

void viking::vulkan::VulkanCommon::endSingleTimeCommands(VulkanDevice * device, VkCommandBuffer command_buffer, VkCommandPool command_pool)
{
	vkEndCommandBuffer(command_buffer);
	VkSubmitInfo submit_info = VulkanInitializers::submitInfo(command_buffer);
	vkQueueSubmit(
		*device->GetGraphicsQueue(),
		1,
		&submit_info,
		VK_NULL_HANDLE
	);
	vkQueueWaitIdle(
		*device->GetGraphicsQueue()
	);
	vkFreeCommandBuffers(
		device->GetVulkanDevice(),
		command_pool,
		1,
		&command_buffer
	);
}

void viking::vulkan::VulkanCommon::transitionImageLayout(VulkanDevice * device, VkImage image, VkFormat format, VkImageLayout old_layout, VkImageLayout new_layout)
{
	VkCommandBuffer command_buffer = beginSingleTimeCommands(device, *device->GetGraphicsCommandPool());

	VkImageMemoryBarrier barrier = VulkanInitializers::imageMemoryBarrier(image, format, old_layout, new_layout);

	vkCmdPipelineBarrier(
		command_buffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		0,
		0,
		nullptr,
		0,
		nullptr,
		1,
		&barrier
	);

	endSingleTimeCommands(device, command_buffer, *device->GetGraphicsCommandPool());
}

bool viking::vulkan::VulkanCommon::hasStencilComponent(VkFormat format)
{
	return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}

void viking::vulkan::VulkanCommon::createBuffer(VulkanDevice * device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VulkanBufferDataPacket& buffer)
{
	VkBufferCreateInfo buffer_info = VulkanInitializers::bufferCreateInfo(size, usage);

	bool success = VulkanInitializers::validate(vkCreateBuffer(
		device->GetVulkanDevice(),
		&buffer_info,
		nullptr,
		&buffer.buffer
	));

	VkMemoryRequirements mem_requirements;
	vkGetBufferMemoryRequirements(
		device->GetVulkanDevice(),
		buffer.buffer,
		&mem_requirements
	);

	VkMemoryAllocateInfo alloc_info = VulkanInitializers::memoryAllocateInfo(mem_requirements.size, findMemoryType(
		device,
		mem_requirements.memoryTypeBits,
		properties
	));


	buffer.size = mem_requirements.size;
	buffer.alignment = mem_requirements.alignment;


	success = VulkanInitializers::validate(vkAllocateMemory(
		device->GetVulkanDevice(),
		&alloc_info,
		nullptr,
		&buffer.buffer_memory
	));

	success = VulkanInitializers::validate(vkBindBufferMemory(
		device->GetVulkanDevice(),
		buffer.buffer,
		buffer.buffer_memory,
		0
	));

}

void viking::vulkan::VulkanCommon::mapBufferMemory(VulkanDevice * device, VulkanBufferDataPacket & buffer, VkDeviceSize size)
{
	bool success = VulkanInitializers::validate(vkMapMemory(device->GetVulkanDevice(), buffer.buffer_memory, 0, size, 0, &buffer.mapped_memory));
}

void viking::vulkan::VulkanCommon::unMapBufferMemory(VulkanDevice * device, VulkanBufferDataPacket & buffer)
{
	vkUnmapMemory(device->GetVulkanDevice(), buffer.buffer_memory);
	buffer.mapped_memory = nullptr;
}

void viking::vulkan::VulkanCommon::destroyBuffer(VulkanDevice * device, VulkanBufferDataPacket & buffer)
{
	unMapBufferMemory(device,buffer);

	vkDestroyBuffer(
		device->GetVulkanDevice(),
		buffer.buffer,
		nullptr
	);
	vkFreeMemory(
		device->GetVulkanDevice(),
		buffer.buffer_memory,
		nullptr
	);
}


std::string viking::vulkan::VulkanCommon::getFilePath(const std::string & str)
{
	size_t found = str.find_last_of("/\\");
	return str.substr(0, found);
}

VkShaderModule viking::vulkan::VulkanCommon::createShaderModule(VulkanDevice * device, const std::vector<unsigned int>& code)
{
	VkShaderModuleCreateInfo create_info = VulkanInitializers::shaderModuleCreateInfo(code);

	VkShaderModule shader_module;
	bool success = VulkanInitializers::validate(vkCreateShaderModule(
		device->GetVulkanDevice(),
		&create_info,
		nullptr,
		&shader_module
	));
	return shader_module;
}

VkShaderModule viking::vulkan::VulkanCommon::createShaderModule(VulkanDevice * device, const std::vector<char>& code)
{
	VkShaderModuleCreateInfo create_info = VulkanInitializers::shaderModuleCreateInfo(code);

	VkShaderModule shader_module;
	bool success = VulkanInitializers::validate(vkCreateShaderModule(
		device->GetVulkanDevice(),
		&create_info,
		nullptr,
		&shader_module
	));
	return shader_module;
}

std::vector<char> viking::vulkan::VulkanCommon::readFile(const std::string & filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		throw std::runtime_error("failed to open file!");
	}
	size_t file_size = (size_t)file.tellg();
	std::vector<char> buffer(file_size);
	file.seekg(0);
	file.read(buffer.data(), file_size);
	file.close();
	return buffer;
}
