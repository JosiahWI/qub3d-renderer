#pragma once

#include <vulkan\vulkan.h>
#include <viking/IBuffer.hpp>

namespace viking {
	namespace vulkan {
		struct VulkanBufferDataPacket
		{
			VkBuffer buffer;
			VkDeviceSize size;
			VkDeviceSize alignment;
			VkDeviceMemory buffer_memory;
			void* mapped_memory = nullptr;
		};
		class VulkanDevice;
		class VulkanBuffer : public virtual IBuffer
		{
		public:
			VulkanBuffer(VulkanDevice* device, void* dataPtr, unsigned int indexSize, unsigned int elementCount, VkBufferUsageFlags _usage, VkMemoryPropertyFlags _memory_propertys_flag);
			~VulkanBuffer();

			virtual void setData();
			virtual void setData(unsigned int count);
			virtual void setData(unsigned int startIndex, unsigned int count);

			virtual void resize(unsigned int elementCount);

			virtual void getData();
			virtual void getData(unsigned int count);
			virtual void getData(unsigned int startIndex, unsigned int count);
		protected:
			VulkanBufferDataPacket m_buffer;
		private:
			VulkanDevice * m_device;
		};
	}
}