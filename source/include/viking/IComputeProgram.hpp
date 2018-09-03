#pragma once
#include <vector>

namespace viking
{
	class IComputePipeline;
	class IComputeProgram
	{
	public:
		IComputeProgram();
		void attachPipeline(IComputePipeline* pipeline);
		virtual void build() = 0;
		virtual void run() = 0;
	protected:
		std::vector<IComputePipeline*> m_pipelines;
	};
}