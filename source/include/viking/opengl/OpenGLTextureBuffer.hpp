#pragma once

#include <viking/opengl/glad.h>
#include <viking/ITextureBuffer.hpp>
#include <viking/opengl/OpenGLBuffer.hpp>

namespace viking
{
    namespace opengl
    {
        class OpenGLTextureBuffer : public virtual ITextureBuffer , public virtual OpenGLBuffer
        {
        public:
			OpenGLTextureBuffer(void* dataPtr, unsigned int width, unsigned int height);
			GLuint GetId();
		private:
			GLuint m_texutre_id;
        };
    }
}
