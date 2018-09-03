#include <viking/IComputeProgram.hpp>

using namespace viking;

viking::IComputeProgram::IComputeProgram()
{
}

void viking::IComputeProgram::attachPipeline(IComputePipeline * pipeline)
{
	m_pipelines.push_back(pipeline);
}
