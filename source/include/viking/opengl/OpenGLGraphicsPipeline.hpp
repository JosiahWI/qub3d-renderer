#pragma once

#include <viking/IGraphicsPipeline.hpp>
#include <viking/opengl/OpenGLModelPool.hpp>
#include <viking/opengl/glad.h>

namespace viking
{
    namespace opengl
    {
        class OpenGLGraphicsPipeline : public IGraphicsPipeline
        {
        public:
			OpenGLGraphicsPipeline(std::map<ShaderStage, const char*> shader_paths, VertexBufferBase* vertex);
			void build();
			void render();
			virtual void attachModelPool(IModelPool* pool);
		private:
			int GetGLShader(ShaderStage stage);
			std::string getFile(const char* path);
			GLuint program_id;
			std::vector<OpenGLModelPool*> m_pools;
			std::map<ShaderStage, GLuint> m_shaders;
        };
    }
}
