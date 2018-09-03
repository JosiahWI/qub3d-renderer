#include <viking/vulkan/VulkanBuffer.hpp>
#include <viking/vulkan/VulkanCommon.hpp>

using namespace viking::vulkan;

viking::vulkan::VulkanBuffer::VulkanBuffer(VulkanDevice * device, void * dataPtr, unsigned int indexSize, unsigned int elementCount, VkBufferUsageFlags usage, VkMemoryPropertyFlags memory_propertys_flag)
{
	m_device = device;
	m_bufferSize = indexSize * elementCount;
	m_dataPtr = dataPtr;
	m_indexSize = indexSize;
	m_elementCount = elementCount;
	
	VulkanCommon::createBuffer(device, m_indexSize * m_elementCount, usage, memory_propertys_flag, m_buffer);
	VulkanCommon::mapBufferMemory(device, m_buffer, m_buffer.size);
}

viking::vulkan::VulkanBuffer::~VulkanBuffer()
{
	VulkanCommon::unMapBufferMemory(m_device, m_buffer);
	VulkanCommon::destroyBuffer(m_device, m_buffer);
}

void viking::vulkan::VulkanBuffer::setData()
{
	memcpy(m_buffer.mapped_memory, m_dataPtr, (::size_t)m_bufferSize);
}

void viking::vulkan::VulkanBuffer::setData(unsigned int count)
{
	memcpy(m_buffer.mapped_memory, m_dataPtr, (::size_t)m_indexSize * count);
}

void viking::vulkan::VulkanBuffer::setData(unsigned int startIndex, unsigned int count)
{
	memcpy(((char*)m_buffer.mapped_memory) + (startIndex * m_indexSize), ((char*)m_dataPtr) + (startIndex * m_indexSize), (::size_t)m_indexSize * count);
}

void viking::vulkan::VulkanBuffer::resize(unsigned int elementCount)
{
}

void viking::vulkan::VulkanBuffer::getData()
{
	memcpy(m_dataPtr, m_buffer.mapped_memory, (::size_t)m_bufferSize);
}

void viking::vulkan::VulkanBuffer::getData(unsigned int count)
{
	memcpy(m_dataPtr, m_buffer.mapped_memory, (::size_t)m_indexSize * count);
}

void viking::vulkan::VulkanBuffer::getData(unsigned int startIndex, unsigned int count)
{
	memcpy(((char*)m_dataPtr) + (startIndex * m_indexSize), ((char*)m_buffer.mapped_memory) + (startIndex * m_indexSize), (::size_t)m_indexSize * count);
}
