#pragma once

#include <map>

namespace viking
{
	class IModel
	{
	public:
		IModel(unsigned int model_pool_index);
		void SetDataPointer(unsigned int index, void* data);
		void SetData(unsigned int index, void* data, unsigned int size);
		template <class T>
		void SetData(unsigned int index, T* data);
		unsigned int GetModelPoolIndex();
	protected:
		unsigned int m_model_pool_index;
		std::map<unsigned int, void*> m_data_pointers;
	};
	template<class T>
	inline void IModel::SetData(unsigned int index, T* data)
	{
		memcpy(m_data_pointers[index], data, sizeof(T));
	}
}