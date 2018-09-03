#include <viking/opengl/OpenGLGraphicsPipeline.hpp>
#include <viking/opengl/OpenGLModelPool.hpp>
#include <viking/opengl/glad.h>
#include <fstream>
#include <string>


using namespace viking::opengl;
using namespace viking;

viking::opengl::OpenGLGraphicsPipeline::OpenGLGraphicsPipeline(std::map<ShaderStage, const char*> shader_paths, VertexBufferBase* vertex)
	: IGraphicsPipeline(shader_paths, vertex)
{
	
}

void viking::opengl::OpenGLGraphicsPipeline::build()
{
	GLint res = GL_FALSE;
	int log;
	for (auto it = m_shader_paths.begin();it!= m_shader_paths.end(); it++)
	{
		m_shaders[it->first] = glCreateShader(GetGLShader(it->first));
		std::string codeString = getFile(it->second);
		char const * code = codeString.c_str();

		glShaderSource(m_shaders[it->first], 1, &code, NULL);
		glCompileShader(m_shaders[it->first]);


		glGetShaderiv(m_shaders[it->first], GL_COMPILE_STATUS, &res);
		glGetShaderiv(m_shaders[it->first], GL_INFO_LOG_LENGTH, &log);

		// Error checking
		//.....
		if (log > 0)
		{
			std::vector<char> VertexShaderErrorMessage(log + 1);
			glGetShaderInfoLog(m_shaders[it->first], log, NULL, &VertexShaderErrorMessage[0]);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}
	}

	program_id = glCreateProgram();

	for (auto it = m_shader_paths.begin(); it != m_shader_paths.end(); it++)
	{
		glAttachShader(program_id, m_shaders[it->first]);
	}

	glLinkProgram(program_id);

	glGetProgramiv(program_id, GL_LINK_STATUS, &res);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log);

	// Error checking
	//.....


	for (auto it = m_shader_paths.begin(); it != m_shader_paths.end(); it++)
	{
		glDetachShader(program_id, m_shaders[it->first]);
		glDeleteShader(m_shaders[it->first]);
	}


}

void viking::opengl::OpenGLGraphicsPipeline::render()
{
	glUseProgram(program_id);
	for (auto pool : m_pools)
	{
		pool->render(program_id);
	}
}

void viking::opengl::OpenGLGraphicsPipeline::attachModelPool(IModelPool * pool)
{
	m_pools.push_back(static_cast<OpenGLModelPool*>(pool));
}

int viking::opengl::OpenGLGraphicsPipeline::GetGLShader(ShaderStage stage)
{
	switch (stage)
	{
	case VERTEX_SHADER:
		return GL_VERTEX_SHADER;
		break;
	case FRAGMENT_SHADER:
		return GL_FRAGMENT_SHADER;
		break;
	case GEOMETRY_SHADER:
		return GL_GEOMETRY_SHADER;
		break;
	}
	return 0;
}

std::string viking::opengl::OpenGLGraphicsPipeline::getFile(const char * path)
{
	std::string finalLine;
	std::string line;
	std::ifstream myfile(path);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			finalLine += line + "\n";
		}
	}
	return finalLine;
}
