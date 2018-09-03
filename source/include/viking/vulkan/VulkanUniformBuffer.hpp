#pragma once

#include <vulkan\vulkan.h>
#include <viking/vulkan/VulkanBuffer.hpp>
#include <viking/vulkan/VulkanDescriptor.hpp>
#include <viking/IUniformBuffer.hpp>

namespace viking {
	namespace vulkan {
		class VulkanDevice;
		class VulkanUniformBuffer : public IUniformBuffer, public VulkanBuffer, public VulkanDescriptor
		{
		public:
			VulkanUniformBuffer(VulkanDevice* device, void* dataPtr, unsigned int indexSize, unsigned int elementCount, DescriptorType descriptor_type, ShaderStage shader_stage, unsigned int binding);
			~VulkanUniformBuffer();

		private:
		};
	}
}