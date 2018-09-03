#pragma once

#include <viking/opengl/glad.h>
#include <viking/IBuffer.hpp>

namespace viking
{
    namespace opengl
    {
        class OpenGLBuffer : public virtual IBuffer
        {
        public:
			OpenGLBuffer(void * dataPtr, unsigned int indexSize, unsigned int elementCount);
		private:

        };
    }
}
