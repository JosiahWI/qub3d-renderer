#pragma once

#include <viking/opengl/glad.h>
#include <viking/IModelPool.hpp>
#include <viking/opengl/OpenGLModel.hpp>
#include <viking/opengl/OpenGLUniformBuffer.hpp>
#include <viking/opengl/OpenGLTextureBuffer.hpp>

namespace viking
{
    namespace opengl
    {
        class OpenGLModelPool : public IModelPool
        {
        public:
			OpenGLModelPool(viking::VertexBufferBase* base, IBuffer* vertex_data, IBuffer* index_data);
			GLuint GetVAO();
			void render(GLuint programID);
			virtual IModel* createModel();
			virtual void attachBuffer(unsigned int index, IUniformBuffer * buffer);
			virtual void attachBuffer(IUniformBuffer * buffer);
			virtual void attachBuffer(ITextureBuffer * buffer);
		private:
			unsigned int m_current_index;
			viking::VertexBufferBase* m_base;
			std::map<unsigned int, OpenGLModel*> m_models;
			std::map<unsigned int, OpenGLUniformBuffer*> m_indexed_buffers;
			std::vector<OpenGLUniformBuffer*> m_buffers;
			std::vector<OpenGLTextureBuffer*> m_textureBuffers;
			GLuint vao;
			GLuint vbo;
			GLuint ibo;
        };
    }
}
