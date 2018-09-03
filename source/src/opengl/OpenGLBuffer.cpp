#include <viking/opengl/OpenGLBuffer.hpp>

using namespace viking::opengl;
using namespace viking;

viking::opengl::OpenGLBuffer::OpenGLBuffer(void * dataPtr, unsigned int indexSize, unsigned int elementCount)
{
	m_dataPtr = dataPtr;
	m_indexSize = indexSize;
	m_elementCount = elementCount;
	m_bufferSize = indexSize * elementCount;
}
