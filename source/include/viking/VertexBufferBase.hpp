#pragma once

#include <viking\VertexBinding.hpp>

#include <vector>

namespace viking
{
	struct VertexBufferBase
	{
	public:
		static std::vector<VertexBinding> vertex_bindings;
		static unsigned int size;
	};
}