#include <viking/opengl/OpenGLRenderer.hpp>
#include <viking/opengl/OpenGLModelPool.hpp>
#include <viking/opengl/OpenGLGraphicsPipeline.hpp>
#include <viking/opengl/OpenGLBuffer.hpp>
#include <viking/opengl/OpenGLUniformBuffer.hpp>
#include <viking/opengl/OpenGLTextureBuffer.hpp>
#include <viking/opengl/glad.h>

using namespace viking::opengl;
using namespace viking;

void OpenGLRenderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto pipeline : m_graphics_pipeline)
	{
		pipeline->render();
	}
}

IComputePipeline * viking::opengl::OpenGLRenderer::createComputePipeline(const char* path, unsigned int x, unsigned int y, unsigned int z)
{
	return nullptr;
}

IComputeProgram * viking::opengl::OpenGLRenderer::createComputeProgram()
{
	return nullptr;
}

IGraphicsPipeline * viking::opengl::OpenGLRenderer::createGraphicsPipeline(std::map<ShaderStage, const char*> shader_paths, VertexBufferBase* vertex)
{
	OpenGLGraphicsPipeline* m_pipeline = new OpenGLGraphicsPipeline(shader_paths, vertex);
	m_graphics_pipeline.push_back(m_pipeline);
	return m_pipeline;
}

IModelPool * viking::opengl::OpenGLRenderer::createModelPool(VertexBufferBase* base, IBuffer* vertex_data, IBuffer*index_data)
{
	OpenGLModelPool* pool = new OpenGLModelPool(base, vertex_data, index_data);
	m_model_pool.push_back(pool);
	return pool;
}

IBuffer * viking::opengl::OpenGLRenderer::createBuffer(void * dataPtr, unsigned int indexSize, unsigned int elementCount)
{
	return new OpenGLBuffer(dataPtr, indexSize, elementCount);
}

IUniformBuffer * viking::opengl::OpenGLRenderer::createUniformBuffer(void * dataPtr, unsigned int indexSize, unsigned int elementCount, ShaderStage shader_stage, unsigned int binding)
{
	return new OpenGLUniformBuffer(dataPtr,indexSize,elementCount,binding);
}

ITextureBuffer * viking::opengl::OpenGLRenderer::createTextureBuffer(void * dataPtr, unsigned int width, unsigned int height)
{
	return new OpenGLTextureBuffer(dataPtr, width, height);
}

void OpenGLRenderer::start()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);
}