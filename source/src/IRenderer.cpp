#include <viking/IRenderer.hpp>
#include <viking/vulkan/VulkanRenderer.hpp>
#include <viking/opengl/OpenGLRenderer.hpp>

using namespace viking;

IRenderer* IRenderer::createRenderer(const RenderingAPI& api)
{
	switch(api)
	{
		case RenderingAPI::GL3: 
		case RenderingAPI::GL11:
			return new opengl::OpenGLRenderer();

		case RenderingAPI::Vulkan:
			return new vulkan::VulkanRenderer();
	}

	return nullptr;
}

void IRenderer::addWindow(IWindow* window)
{
	m_window = window;
}
