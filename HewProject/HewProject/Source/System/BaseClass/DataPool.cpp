#include "DataPool.hpp"
#include <Windows.h>
std::shared_ptr<CDataPool> CDataPool::m_ins;

std::shared_ptr<CDataPool> CDataPool::GetIns()
{
	if(m_ins)
		return m_ins;
	m_ins.reset(new CDataPool());
}

void CDataPool::CreateIns()
{
	if (m_ins)
		return;
	m_ins.reset(new CDataPool());

}

void CDataPool::Destroy()
{
	if (m_ins != nullptr)
		return;
	m_ins.reset();
}

CDataPool::~CDataPool()
{

}

CDataPool::CDataPool()
{
	NULL_MODEL_SOURCE = "Assets/NullModel/NullModel.obj";
	GetModel(NULL_MODEL_SOURCE);
}

Model CDataPool::GetModel(const char* src, float scale, bool flip)
{
	if (m_models.count(src) != 0)
		return *(m_models[src].get());
	Model* tmp = new Model;
	bool result = tmp->Load(src, scale, flip);
	if (result == false)
		return *(m_models[NULL_MODEL_SOURCE].get());
	m_models[src].reset(tmp);
	return *(m_models[src]);
}
