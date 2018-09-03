#pragma once

#include <vector>

#include <vulkan/vulkan.h>
#include <viking/vulkan/VulkanDevice.hpp>
#include <viking/vulkan/VulkanUniformBuffer.hpp>
#include <viking/vulkan/IVulkanPipeline.hpp>
#include <viking/vulkan/VulkanInitializers.hpp>
#include <viking/IComputePipeline.hpp>

namespace viking {
	namespace vulkan {
		class VulkanComputePipeline : public IVulkanPipeline, public IComputePipeline
		{
		public:
			VulkanComputePipeline(VulkanDevice* device, const char* path, unsigned int x, unsigned int y, unsigned int z);
			~VulkanComputePipeline();
			virtual void createPipeline();
			virtual void destroyPipeline();
			virtual void attachBuffer(IUniformBuffer* buffer);
			virtual void build();
			virtual void attachToCommandBuffer(VkCommandBuffer & command_buffer);
		private:
			VulkanDevice * m_device;
			std::vector<VkDescriptorSetLayoutBinding> m_layout_bindings;
			std::vector<VkDescriptorPoolSize> m_descriptor_pool_sizes;
			std::vector<VkDescriptorSetLayout> m_descriptor_set_layouts;
			std::vector<VkWriteDescriptorSet> m_write_descriptor_sets;

			VkDescriptorPool m_descriptor_pool;
			VkDescriptorSetLayout m_descriptor_set_layout;
			VkDescriptorSet m_descriptor_set;
			VkPipelineLayout m_compute_pipeline_layout;

			std::vector<VulkanUniformBuffer*> m_buffers;
		};
	}
}