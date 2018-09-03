#include <viking/IBuffer.hpp>

void * viking::IBuffer::getPtr()
{
	return m_dataPtr;
}

unsigned int viking::IBuffer::getBufferSize()
{
	return m_bufferSize;
}

unsigned int viking::IBuffer::getIndexSize()
{
	return m_indexSize;
}

unsigned int viking::IBuffer::getElementCount()
{
	return m_elementCount;
}
