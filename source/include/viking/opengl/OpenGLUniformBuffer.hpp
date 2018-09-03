#pragma once

#include <viking/opengl/glad.h>
#include <viking/IUniformBuffer.hpp>

namespace viking
{
    namespace opengl
    {
        class OpenGLUniformBuffer : public IUniformBuffer
        {
        public:
			OpenGLUniformBuffer(void* dataPtr, unsigned int indexSize, unsigned int elementCount, unsigned int binding);
			GLuint getUBO();
			virtual void setData();
			virtual void setData(unsigned int count);
			virtual void setData(unsigned int startIndex, unsigned int count);

			void* getDataPtr(unsigned int startIndex);

		private:
			GLuint ubo = 0;
        };
    }
}
