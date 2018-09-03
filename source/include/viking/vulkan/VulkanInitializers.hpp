#pragma once

#include <vector>
#include <array>
#include <vulkan/vulkan.h>
#include <viking/vulkan/VulkanCommon.hpp>
#include <viking/vulkan/VulkanQueueFamilyIndices.hpp>
#include <viking/vulkan/VulkanSwapChainConfiguration.hpp>

namespace viking { namespace vulkan 
{
    struct VulkanInitializers
    {
        static bool validate(VkResult result);

        static VkApplicationInfo applicationInfo(const char* app_name, uint32_t app_ver, const char* engine_name, uint32_t engine_ver, uint32_t api_version);

        static VkInstanceCreateInfo instanceCreateInfo(VkApplicationInfo & app_info, std::vector<const char*>& instance_extensions, std::vector<const char*>& instance_layers);

		static VkDeviceQueueCreateInfo deviceQueueCreate(uint32_t queue_family_index, float queue_priority);

		static VkDeviceCreateInfo deviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>& queue_create_infos, const std::vector<const char*>& device_extensions, VkPhysicalDeviceFeatures& device_features);

		static VkCommandPoolCreateInfo commandPoolCreateInfo(uint32_t queue_family_index, VkCommandPoolCreateFlags flags = 0);

		static VkSwapchainCreateInfoKHR swapchainCreateInfoKHR(VkSurfaceFormatKHR surface_format, VkExtent2D extent, VkPresentModeKHR present_mode, uint32_t image_count, VkSurfaceKHR surface, VulkanQueueFamilyIndices indices, VulkanSwapChainConfiguration swap_chain_support);

		static VkImageViewCreateInfo imageViewCreate(VkImage image, VkFormat format, VkImageAspectFlags aspect_flags);

		static VkSemaphoreCreateInfo semaphoreCreateInfo();

		static VkRenderPassBeginInfo renderPassBeginInfo(VkRenderPass render_pass, VkExtent2D swapchain_extent, std::array<VkClearValue, 2>& clear_values);

		static VkAttachmentDescription attachmentDescription(VkFormat format, VkAttachmentStoreOp store_op, VkImageLayout final_layout);

		static VkAttachmentReference attachmentReference(VkImageLayout layout, uint32_t attachment);

		static VkFramebufferCreateInfo framebufferCreateInfo(VkExtent2D& swap_chain_extent, std::vector<VkImageView>& attachments, VkRenderPass& render_pass);

		static VkSubpassDescription subpassDescription(VkAttachmentReference& color_attachment_refrence, VkAttachmentReference& depth_attachment_ref);

		static VkSubpassDependency subpassDependency();

		static VkRenderPassCreateInfo renderPassCreateInfo(std::vector<VkAttachmentDescription>& attachments, VkSubpassDescription& subpass, VkSubpassDependency& subpass_dependency);

		static VkImageCreateInfo imageCreateInfo(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, uint32_t mip_levels = 1);

		static VkMemoryAllocateInfo memoryAllocateInfo(VkDeviceSize size, uint32_t memory_type_index);

		static VkCommandBufferAllocateInfo commandBufferAllocateInfo(VkCommandPool pool, uint32_t command_buffer_count);

		static VkCommandBufferBeginInfo commandBufferBeginInfo(VkCommandBufferUsageFlags flag);

		static VkImageMemoryBarrier imageMemoryBarrier();

		static VkImageMemoryBarrier imageMemoryBarrier(VkImage& image, VkFormat& format, VkImageLayout& old_layout, VkImageLayout& new_layout);

		static VkSubmitInfo submitInfo(VkCommandBuffer& buffer);

		static VkBufferCreateInfo bufferCreateInfo(VkDeviceSize size, VkBufferUsageFlags usage);

		static VkDescriptorPoolSize descriptorPoolSize(VkDescriptorType type);

		static VkDescriptorSetLayoutBinding descriptorSetLayoutBinding(VkDescriptorType type, VkShaderStageFlags stage_flags, uint32_t binding);

		static VkDescriptorPoolCreateInfo descriptorPoolCreateInfo(std::vector<VkDescriptorPoolSize> & pool_sizes, uint32_t max_sets);

		static VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo(std::vector<VkDescriptorSetLayoutBinding>& layout_bindings);

		static VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo(VkDescriptorSetLayout & descriptor_set_layout);

		static VkDescriptorSetAllocateInfo descriptorSetAllocateInfo(std::vector<VkDescriptorSetLayout>& layouts, VkDescriptorPool & pool);

		static VkShaderModuleCreateInfo shaderModuleCreateInfo(const std::vector<unsigned int>& code);

		static VkShaderModuleCreateInfo shaderModuleCreateInfo(const std::vector<char>& code);

		static VkPipelineShaderStageCreateInfo pipelineShaderStageCreateInfo(VkShaderModule & shader, const char* main, VkShaderStageFlagBits flag);

		static VkComputePipelineCreateInfo computePipelineCreateInfo(VkPipelineLayout& layout, VkPipelineShaderStageCreateInfo& shader_stage);

		static VkWriteDescriptorSet writeDescriptorSet(VkDescriptorSet d_set, VkDescriptorBufferInfo& buffer_info, VkDescriptorType type, int binding);

		static VkWriteDescriptorSet writeDescriptorSet(VkDescriptorSet d_set, VkDescriptorImageInfo& buffer_info, VkDescriptorType type, int binding);

		static VkDescriptorBufferInfo descriptorBufferInfo(VkBuffer buffer, uint32_t size, VkDeviceSize& offset);

		static VkFenceCreateInfo createFenceInfo();

    };
}}