#pragma once

#include <viking/API.hpp>

namespace viking
{
	class IRenderer;
	class IBuffer
	{
	public:

		virtual void setData() {};
		virtual void setData(unsigned int count) {};
		virtual void setData(unsigned int startIndex, unsigned int count) {};

		virtual void resize(unsigned int elementCount) {};

		virtual void getData() {};
		virtual void getData(unsigned int count) {};
		virtual void getData(unsigned int startIndex, unsigned int count) {};

		void* getPtr();
		unsigned int getBufferSize();
		unsigned int getIndexSize();
		unsigned int getElementCount();
	protected:
		void* m_dataPtr;
		unsigned int m_bufferSize;
		unsigned int m_indexSize;
		unsigned int m_elementCount;
	};
}