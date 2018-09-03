#include <viking/IModel.hpp>


viking::IModel::IModel(unsigned int model_pool_index)
{
	m_model_pool_index = model_pool_index;
}

void viking::IModel::SetDataPointer(unsigned int index, void * data)
{
	m_data_pointers[index] = data;
}

void viking::IModel::SetData(unsigned int index, void * data, unsigned int size)
{
	memcpy(m_data_pointers[index], data, size);
}

unsigned int viking::IModel::GetModelPoolIndex()
{
	return m_model_pool_index;
}
