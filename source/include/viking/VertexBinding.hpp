#pragma once

#include <vector>

namespace viking
{
	struct VertexBinding
	{
	public:
		VertexBinding(unsigned int location, unsigned int size, unsigned int offset) : m_location (location) , m_size(size), m_offset(offset){}
		unsigned int GetLocation()
		{
			return m_location;
		}
		unsigned int GetOffset()
		{
			return m_offset;
		}
		unsigned int GetSize()
		{
			return m_size;
		}
	private:
		unsigned int m_location;
		unsigned int m_offset;
		unsigned int m_size;
	};
}