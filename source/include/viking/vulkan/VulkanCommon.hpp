#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include <viking/IDescriptor.hpp>

namespace viking {
	namespace vulkan {
		class VulkanDevice;
		struct VulkanBufferDataPacket;
		struct VulkanCommon
		{
			static void createImage(VulkanDevice* device, VkExtent2D extent, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage & image, VkDeviceMemory & image_memory);
		
			static uint32_t findMemoryType(VulkanDevice* device, uint32_t type_filter, VkMemoryPropertyFlags properties);

			static void createImageView(VulkanDevice* device, VkImage image, VkFormat format, VkImageAspectFlags aspect_flags, VkImageView & view);

			static VkCommandBuffer beginSingleTimeCommands(VulkanDevice* device, VkCommandPool command_pool);

			static void endSingleTimeCommands(VulkanDevice* device, VkCommandBuffer command_buffer, VkCommandPool command_pool);

			static void transitionImageLayout(VulkanDevice* device, VkImage image, VkFormat format, VkImageLayout old_layout, VkImageLayout new_layout);

			static bool hasStencilComponent(VkFormat format);

			static void createBuffer(VulkanDevice* device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VulkanBufferDataPacket& buffer);

			static void mapBufferMemory(VulkanDevice * device, VulkanBufferDataPacket & buffer, VkDeviceSize size);

			static void unMapBufferMemory(VulkanDevice * device, VulkanBufferDataPacket & buffer);

			static void destroyBuffer(VulkanDevice * device, VulkanBufferDataPacket & buffer);

			static std::string getFilePath(const std::string& str);

			static VkShaderModule createShaderModule(VulkanDevice * device, const std::vector<unsigned int>& code);

			static VkShaderModule createShaderModule(VulkanDevice * device, const std::vector<char>& code);

			static std::vector<char> readFile(const std::string & filename);

		private:
			static bool m_glslangInitialized;
		};
	}
}