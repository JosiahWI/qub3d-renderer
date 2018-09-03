#include <viking/opengl/OpenGLSDLWindow.hpp>
#include <viking/opengl/glad.h>
using namespace viking::opengl;
using namespace viking;

OpenGLSDLWindow::OpenGLSDLWindow(WindowDescriptor descriptor): SDLWindow(WindowingAPI::SDL)
{
    m_window = SDL_CreateWindow(descriptor.title, descriptor.windowposX, descriptor.windowposY, descriptor.width, descriptor.height, SDL_WINDOW_OPENGL);
    SDL_ShowWindow(m_window);
    m_context = SDL_GL_CreateContext(m_window);
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);


	// Set our OpenGL version.
	// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}
