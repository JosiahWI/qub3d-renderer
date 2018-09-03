#pragma once

#include <viking\VertexBufferBase.hpp>
#include <viking\IBuffer.hpp>
#include <viking\IModel.hpp>
#include <viking\IUniformBuffer.hpp>
#include <viking\ITextureBuffer.hpp>

#include <vector>

namespace viking
{
	class IModelPool
	{
	public:
		IModelPool(viking::VertexBufferBase* base, IBuffer* vertex_data, IBuffer* index_data) : m_base(base), m_vertex_data(vertex_data), m_index_data(index_data){}
		virtual IModel* createModel() = 0;
		virtual void attachBuffer(unsigned int index, IUniformBuffer * buffer) = 0;
		virtual void attachBuffer(IUniformBuffer * buffer) = 0;
		virtual void attachBuffer(ITextureBuffer * buffer) = 0;
	protected:
		viking::VertexBufferBase* m_base;
		IBuffer* m_vertex_data;
		IBuffer* m_index_data;
	};
}