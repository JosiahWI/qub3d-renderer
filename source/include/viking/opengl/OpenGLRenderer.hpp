#pragma once

#include <viking/SDLWindow.hpp>
#include <viking/IRenderer.hpp>
#include <viking/IComputePipeline.hpp>
#include <viking/IComputeProgram.hpp>
#include <viking/opengl/OpenGLModelPool.hpp>
#include <viking/opengl/OpenGLGraphicsPipeline.hpp>

namespace viking
{
    namespace opengl
    {
        class OpenGLRenderer : public IRenderer
        {
        public:
            virtual void start();
			virtual void render();
			virtual IComputePipeline* createComputePipeline(const char* path, unsigned int x, unsigned int y, unsigned int z);
			virtual IComputeProgram* createComputeProgram();
			virtual IGraphicsPipeline* createGraphicsPipeline(std::map<ShaderStage, const char*> shader_paths, VertexBufferBase* vertex);
			virtual IModelPool* createModelPool(VertexBufferBase* vertex, IBuffer* vertex_data, IBuffer*index_data);
			virtual IBuffer* createBuffer(void* dataPtr, unsigned int indexSize, unsigned int elementCount);
			virtual IUniformBuffer* createUniformBuffer(void* dataPtr, unsigned int indexSize, unsigned int elementCount, ShaderStage shader_stage, unsigned int binding);
			virtual ITextureBuffer* createTextureBuffer(void* dataPtr, unsigned int width, unsigned int height);
		private:
			std::vector<OpenGLGraphicsPipeline*> m_graphics_pipeline;
			std::vector<OpenGLModelPool*> m_model_pool;
        };
    }
}
