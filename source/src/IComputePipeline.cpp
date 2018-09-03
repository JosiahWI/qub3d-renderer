#include <viking/IComputePipeline.hpp>

using namespace viking;

viking::IComputePipeline::IComputePipeline(const char * path, unsigned int x, unsigned int y, unsigned int z)
{
	m_path = path;
	m_x = x;
	m_y = y;
	m_z = z;
}

const char * viking::IComputePipeline::getPath()
{
	return m_path;
}

unsigned int viking::IComputePipeline::getX()
{
	return m_x;
}

unsigned int viking::IComputePipeline::getY()
{
	return m_y;
}

unsigned int viking::IComputePipeline::getZ()
{
	return m_z;
}
