#pragma once

#include <vulkan/vulkan.h>
#include <viking\IComputeProgram.hpp>

namespace viking {
	namespace vulkan {
		class VulkanDevice;
		class VulkanComputeProgram : public IComputeProgram
		{
		public:
			VulkanComputeProgram(VulkanDevice * device);
			~VulkanComputeProgram();
			void build();
			void run();
		private:
			VulkanDevice * m_device;
			VkFence fence;
			VkCommandBuffer m_command_buffer;
		};
	}
}