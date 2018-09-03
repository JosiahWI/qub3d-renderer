#include <viking/opengl/OpenGLModelPool.hpp>
#include <viking/opengl/OpenGLModel.hpp>
#include <viking/opengl/OpenGLUniformBuffer.hpp>
#include <viking/opengl/glad.h>

using namespace viking::opengl;
using namespace viking;

viking::opengl::OpenGLModelPool::OpenGLModelPool(viking::VertexBufferBase* base, IBuffer * vertex_data, IBuffer * index_data) :
	IModelPool(base, vertex_data, index_data)
{
	m_current_index = 0;
	m_base = base;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_data->getBufferSize(), vertex_data->getPtr(), GL_STATIC_DRAW);
	

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data->getBufferSize(), index_data->getPtr(), GL_STATIC_DRAW);
}

GLuint viking::opengl::OpenGLModelPool::GetVAO()
{
	return vao;
}

void viking::opengl::OpenGLModelPool::render(GLuint programID)
{
	for (auto b : m_base->vertex_bindings)
	{
		glEnableVertexAttribArray(b.GetLocation());
		glVertexAttribPointer(b.GetLocation(), b.GetSize() / sizeof(float), GL_FLOAT, GL_FALSE, m_base->size, (GLvoid*)b.GetOffset());
	}
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (auto buffer : m_buffers)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, buffer->getUBO());
		glBufferSubData(GL_UNIFORM_BUFFER, 0, buffer->getBufferSize(), buffer->getPtr());
		glBindBufferRange(GL_UNIFORM_BUFFER, buffer->GetBinding(), buffer->getUBO(), 0, buffer->getBufferSize() * m_models.size());
	}

	for (auto tex_buffer : m_textureBuffers)
	{
		glBindTexture(GL_TEXTURE_2D, tex_buffer->GetId());
		
	}

	GLint max_buffer_size;
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &max_buffer_size);

	int totalToDraw = m_models.size();
	int maxPerDraw = totalToDraw;

	for (auto buffer = m_indexed_buffers.begin(); buffer != m_indexed_buffers.end(); buffer++)
	{
		if (buffer->second->getBufferSize() > max_buffer_size)
		{
			if (buffer->second->getBufferSize() > max_buffer_size)
			{
				int currentMax = max_buffer_size / buffer->second->getIndexSize();

				if (currentMax < maxPerDraw)
				{
					maxPerDraw = currentMax;
				}

			}
		}
	}

	int itterations = totalToDraw / maxPerDraw;

	for (int i = 0; i < itterations; i++)
	{


		for (auto buffer = m_indexed_buffers.begin(); buffer != m_indexed_buffers.end(); buffer++)
		{
			glBindBuffer(GL_UNIFORM_BUFFER, buffer->second->getUBO());
			glBufferSubData(GL_UNIFORM_BUFFER, 0, maxPerDraw * buffer->second->getIndexSize(), buffer->second->getDataPtr(i * maxPerDraw));
			glBindBufferRange(GL_UNIFORM_BUFFER, buffer->second->GetBinding(), buffer->second->getUBO(), 0, maxPerDraw * buffer->second->getIndexSize());
		}

		glBindVertexArray(vao);

		glDrawElementsInstanced(GL_TRIANGLES, m_index_data->getElementCount(), GL_UNSIGNED_SHORT, 0, totalToDraw < maxPerDraw ? totalToDraw : maxPerDraw);

		totalToDraw -= maxPerDraw;
	}


	for (auto b : m_base->vertex_bindings)
	{
		glDisableVertexAttribArray(b.GetLocation());
	}
}

IModel * viking::opengl::OpenGLModelPool::createModel()
{
	OpenGLModel* model = new OpenGLModel(m_current_index);
	m_models[m_current_index] = model;

	for (auto buffer = m_indexed_buffers.begin(); buffer != m_indexed_buffers.end(); buffer++)
	{
		void* data = buffer->second->getPtr();
		model->SetDataPointer(buffer->first, ((char*)data) + (buffer->second->getIndexSize() * m_current_index));
	}

	m_current_index++;
	return model;
}

void viking::opengl::OpenGLModelPool::attachBuffer(unsigned int index, IUniformBuffer * buffer)
{
	m_indexed_buffers[index] = dynamic_cast<OpenGLUniformBuffer*>(buffer);
}

void viking::opengl::OpenGLModelPool::attachBuffer(IUniformBuffer * buffer)
{
	m_buffers.push_back(dynamic_cast<OpenGLUniformBuffer*>(buffer));
}

void viking::opengl::OpenGLModelPool::attachBuffer(ITextureBuffer * buffer)
{
	m_textureBuffers.push_back(dynamic_cast<OpenGLTextureBuffer*>(buffer));
}
