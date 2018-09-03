#include <viking/opengl/OpenGL.hpp>
#include <viking/opengl/glad.h>
using namespace viking::opengl;
using namespace viking;

OpenGLSDLWindow::OpenGLSDLWindow(WindowDescriptor descriptor): SDLWindow(WindowingAPI::SDL)
{
    m_window = SDL_CreateWindow(descriptor.title, descriptor.windowposX, descriptor.windowposY, descriptor.width, descriptor.height, SDL_WINDOW_OPENGL);
    SDL_ShowWindow(m_window);
    m_context = SDL_GL_CreateContext(m_window);
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
}
