#pragma once

#include <vulkan/vulkan.h>

#include <viking/vulkan/VulkanInstance.hpp>
#include <viking/vulkan/VulkanPhysicalDevice.hpp>
#include <viking/vulkan/VulkanDevice.hpp>
#include <viking/vulkan/VulkanWindow.hpp>
#include <viking/vulkan/IVulkanSurface.hpp>
#include <viking/vulkan/VulkanSwapchain.hpp>
#include <viking/vulkan/VulkanComputeProgram.hpp>

#include <viking/IRenderer.hpp>

namespace viking { namespace vulkan
{
    class VulkanRenderer : public IRenderer
    {
    public:
        VulkanRenderer();
        ~VulkanRenderer();
        virtual void render();
		virtual void start();
		virtual IComputePipeline* createComputePipeline(const char* path, unsigned int x, unsigned int y, unsigned int z);
		virtual IComputeProgram* createComputeProgram();
		virtual IGraphicsPipeline* createGraphicsPipeline(std::map<ShaderStage, const char*> shader_paths, VertexBufferBase* vertex);
		virtual IModelPool* createModelPool(VertexBufferBase* vertex, IBuffer* vertex_data, IBuffer*index_data);
		virtual IBuffer* createBuffer(void* dataPtr, unsigned int indexSize, unsigned int elementCount);
		virtual IUniformBuffer* createUniformBuffer(void* dataPtr, unsigned int indexSize, unsigned int elementCount, ShaderStage shader_stage, unsigned int binding);
		virtual ITextureBuffer* createTextureBuffer(void* dataPtr, unsigned int width, unsigned int height);
		VulkanPhysicalDevice* GetPhysicalDevice();
		VulkanDevice* GetDevice();
		IVulkanSurface* GetSurface();
    private:
        void setupVulkan();
        VulkanInstance * m_instance;
		VulkanWindow* m_vulkan_window;
		IVulkanSurface* m_vulkan_surface;
		VulkanPhysicalDevice* m_pdevice;
		VulkanDevice* m_device;
		VulkanSwapchain* m_swapchain;
    };
}}