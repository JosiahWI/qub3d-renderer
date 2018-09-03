#include <viking/vulkan/VulkanSDLSurface.hpp>
#include <viking/vulkan/VulkanInstance.hpp>
#include <viking/IWindow.hpp>
#include <SDL.h>
#include <SDL_syswm.h>
#include <assert.h>

using namespace viking;
using namespace viking::vulkan;

void VulkanSDLSurface::initilizeSurface(IWindow* window, VkInstance & instance)
{
	SDLWindow* sdl_window = static_cast<SDLWindow*>(window);
    SDL_Vulkan_CreateSurface(sdl_window->GetSDLWindow(), instance, &m_surface);
}