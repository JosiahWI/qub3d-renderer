#pragma once

#include <viking/IWindow.hpp>
#include <viking/IComputePipeline.hpp>
#include <viking/IComputeProgram.hpp>
#include <viking/VertexBufferBase.hpp>
#include <viking/IGraphicsPipeline.hpp>
#include <viking/ITextureBuffer.hpp>
#include <viking/IModelPool.hpp>
#include <viking/IBuffer.hpp>
#include <viking/ShaderStage.hpp>
#include <viking/API.hpp>

#include <map>

namespace viking 
{
	class IRenderer
	{
	public:

		static IRenderer* createRenderer(const RenderingAPI& api);
		void addWindow(IWindow* window);
		virtual void start() = 0;
		virtual void render() = 0;
		virtual IComputePipeline* createComputePipeline(const char* path, unsigned int x, unsigned int y, unsigned int z) = 0;
		virtual IComputeProgram* createComputeProgram() = 0;
		virtual IGraphicsPipeline* createGraphicsPipeline(std::map<ShaderStage, const char*> shader_paths, VertexBufferBase* vertex) = 0;
		virtual IModelPool* createModelPool(VertexBufferBase* vertex, IBuffer* vertex_data, IBuffer*index_data) = 0;
		virtual IBuffer* createBuffer(void* dataPtr, unsigned int indexSize, unsigned int elementCount) = 0;
		virtual IUniformBuffer* createUniformBuffer(void* dataPtr, unsigned int indexSize, unsigned int elementCount, ShaderStage shader_stage, unsigned int binding) = 0;
		virtual ITextureBuffer* createTextureBuffer(void* dataPtr, unsigned int width, unsigned int height) = 0;
	protected:
		// Just storing a single window for now
		IWindow * m_window;
	};
}