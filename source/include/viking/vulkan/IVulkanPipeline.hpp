#pragma once

#include <vulkan/vulkan.h>
#include <SDL_vulkan.h>

namespace viking {
	namespace vulkan {
		class IVulkanPipeline
		{
		public:
			virtual ~IVulkanPipeline();
			VkPipeline& getPipeline();
		protected:
			virtual void createPipeline() = 0;
			virtual void destroyPipeline() = 0;
			void rebuildPipeline();
			VkPipeline m_pipeline;
		private:
			bool m_created = false;
		};
	}
}