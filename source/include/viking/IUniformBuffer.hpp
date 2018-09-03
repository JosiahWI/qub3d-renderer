#pragma once

#include <viking/API.hpp>
#include <viking/IBuffer.hpp>
#include <viking/IDescriptor.hpp>

namespace viking
{
	class IRenderer;
	class IUniformBuffer : public virtual IBuffer, public virtual IDescriptor
	{
	};
}