#include <viking/vulkan/VulkanRenderer.hpp>
#include <viking/vulkan/VulkanSDLWindow.hpp>
#include <viking/vulkan/VulkanComputePipeline.hpp>
#include <viking/vulkan/VulkanUniformBuffer.hpp>
#include <viking/IWindow.hpp>

using namespace viking;
using namespace viking::vulkan;

VulkanRenderer::VulkanRenderer()
{

}

VulkanRenderer::~VulkanRenderer()
{
	delete m_swapchain;
	delete m_device;
    delete m_pdevice;
    delete m_instance;
}

void VulkanRenderer::render()
{
	m_swapchain->render();
}

void viking::vulkan::VulkanRenderer::start()
{
	switch (m_window->GetWindowingAPI())
	{
	case WindowingAPI::SDL:
		VulkanSDLWindow* vulkan_sdl_window = static_cast<vulkan::VulkanSDLWindow*>(m_window);
		m_vulkan_window = vulkan_sdl_window;
		m_vulkan_surface = vulkan_sdl_window;
		break;
	}
	setupVulkan();
}

IComputePipeline * viking::vulkan::VulkanRenderer::createComputePipeline(const char* path, unsigned int x, unsigned int y, unsigned int z)
{
	return new VulkanComputePipeline(m_device, path, x, y, z);
}

IComputeProgram * viking::vulkan::VulkanRenderer::createComputeProgram()
{
	return new VulkanComputeProgram(m_device);
}

IGraphicsPipeline * viking::vulkan::VulkanRenderer::createGraphicsPipeline(std::map<ShaderStage, const char*> shader_paths, VertexBufferBase* vertex)
{
	return nullptr;
}

IModelPool * viking::vulkan::VulkanRenderer::createModelPool(VertexBufferBase* base, IBuffer* vertex_data, IBuffer*index_data)
{
	return nullptr;
}

IBuffer * viking::vulkan::VulkanRenderer::createBuffer(void * dataPtr, unsigned int indexSize, unsigned int elementCount)
{
	return nullptr;
}

IUniformBuffer * viking::vulkan::VulkanRenderer::createUniformBuffer(void * dataPtr, unsigned int indexSize, unsigned int elementCount, ShaderStage shader_stage, unsigned int binding)
{
	return new vulkan::VulkanUniformBuffer(m_device, dataPtr, indexSize, elementCount, DescriptorType::UNIFORM, shader_stage, binding);
}

ITextureBuffer * viking::vulkan::VulkanRenderer::createTextureBuffer(void * dataPtr, unsigned int width, unsigned int height)
{
	return nullptr;
}

VulkanPhysicalDevice * viking::vulkan::VulkanRenderer::GetPhysicalDevice()
{
	return m_pdevice;
}

VulkanDevice * viking::vulkan::VulkanRenderer::GetDevice()
{
	return m_device;
}

IVulkanSurface * viking::vulkan::VulkanRenderer::GetSurface()
{
	return m_vulkan_surface;
}

void VulkanRenderer::setupVulkan()
{
    m_instance = new VulkanInstance();

    const char** extentions = NULL;
    unsigned int count = 0;
    // Get the total count of all required extentions
	count = m_vulkan_window->getExtensionsCount();

    // Add them to the instance
    for (unsigned int i = 0; i < count; i++)
    {
        m_instance->addExtenstion(m_vulkan_window->getExtensions()[i]);
    }

    m_instance->start();
	m_vulkan_surface->initilizeSurface(m_window, m_instance->getInstance());
    m_pdevice = VulkanPhysicalDevice::getSuitablePhysicalDevice(m_instance->getInstance(), m_vulkan_surface->GetSurface());

	m_device = new VulkanDevice(m_pdevice);

	m_swapchain = new VulkanSwapchain(m_device,m_window, m_vulkan_surface);
}
