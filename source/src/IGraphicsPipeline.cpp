#include <viking/IGraphicsPipeline.hpp>
#include <viking/VertexBufferBase.hpp>

using namespace viking;

viking::IGraphicsPipeline::IGraphicsPipeline(std::map<ShaderStage, const char*> shader_paths, VertexBufferBase* vertex) :
	m_shader_paths(shader_paths) , m_vertex(vertex)
{
}