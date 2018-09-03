#pragma once

#include <vulkan/vulkan.h>
#include <viking/IDescriptor.hpp>

namespace viking {
	namespace vulkan {
		class VulkanDescriptor : public virtual IDescriptor
		{
		public:
			VulkanDescriptor(DescriptorType descriptor_type, ShaderStage shader_stage, unsigned int binding);
			VkShaderStageFlags GetVKShaderStage();
			VkDescriptorType GetVKDescriptorType();
			VkDescriptorImageInfo& GetDescriptorImageInfo();
			VkDescriptorBufferInfo& GetDescriptorBufferInfo();
		protected:
			union
			{
				VkDescriptorImageInfo m_image_info;
				VkDescriptorBufferInfo m_buffer_info;
			};
		private:
			static VkShaderStageFlags ToVKShaderStage(ShaderStage shader_stage);
			static VkDescriptorType ToVKDescriptorType(DescriptorType descriptor_type);
			VkDescriptorType m_descriptor_type;
			VkShaderStageFlags m_shader_stage;
		};
	}
}