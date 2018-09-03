#include <viking/opengl/OpenGLUniformBuffer.hpp>

using namespace viking::opengl;
using namespace viking;

viking::opengl::OpenGLUniformBuffer::OpenGLUniformBuffer(void * dataPtr, unsigned int indexSize, unsigned int elementCount, unsigned int binding) :
	IDescriptor(DescriptorType::UNIFORM, ShaderStage::VERTEX_SHADER, binding) // DescriptorType and Shader stage not needed for GL
{
	m_dataPtr = dataPtr;
	m_bufferSize = indexSize * elementCount;
	m_indexSize = indexSize;
	m_elementCount = elementCount;

	GLint max_buffer_size;
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &max_buffer_size);

	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, m_bufferSize > max_buffer_size ? max_buffer_size : m_bufferSize, 0, GL_STREAM_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLuint viking::opengl::OpenGLUniformBuffer::getUBO()
{
	return ubo;
}

void viking::opengl::OpenGLUniformBuffer::setData()
{
	/*glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
	memcpy(p, &m_dataPtr, m_bufferSize);
	glUnmapBuffer(GL_UNIFORM_BUFFER);*/
}

void viking::opengl::OpenGLUniformBuffer::setData(unsigned int count)
{
}

void viking::opengl::OpenGLUniformBuffer::setData(unsigned int startIndex, unsigned int count)
{
}

void * viking::opengl::OpenGLUniformBuffer::getDataPtr(unsigned int startIndex)
{
	return (char*)m_dataPtr + (m_indexSize * startIndex);
}