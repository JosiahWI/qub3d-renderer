#pragma once

#include <viking/SDLWindow.hpp>
#include <viking/IRenderer.hpp>
#include <viking/IComputePipeline.hpp>

namespace viking
{
    namespace opengl
    {
        class OpenGLSDLWindow : public SDLWindow
        {
        public:
            OpenGLSDLWindow(WindowDescriptor descriptor);
        };
    }
}
