#pragma once

namespace viking
{
	class IUniformBuffer;
	class IComputePipeline
	{
	public:
		IComputePipeline(const char* path, unsigned int x, unsigned int y, unsigned int z);
		virtual void attachBuffer(IUniformBuffer* buffer) = 0;
		virtual void build() = 0;
		const char* getPath();
		unsigned int getX();
		unsigned int getY();
		unsigned int getZ();
	private:
		const char* m_path;
		unsigned int m_x;
		unsigned int m_y;
		unsigned int m_z;
	};
}