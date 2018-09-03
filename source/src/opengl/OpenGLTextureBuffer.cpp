#include <viking/opengl/OpenGLTextureBuffer.hpp>

using namespace viking::opengl;
using namespace viking;

viking::opengl::OpenGLTextureBuffer::OpenGLTextureBuffer(void * dataPtr, unsigned int width, unsigned int height)
 : OpenGLBuffer(dataPtr, 1, 1)
{
	glGenTextures(1, &m_texutre_id);
	glBindTexture(GL_TEXTURE_2D, m_texutre_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, dataPtr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint viking::opengl::OpenGLTextureBuffer::GetId()
{
	return m_texutre_id;
}
