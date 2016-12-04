#include "MTracerPool.h"

MTracerPool::MTracerPool()
{
	m_nMax = 30;
	m_pTracer = nullptr;
}

MTracerPool::~MTracerPool()
{
	Release();
}

void MTracerPool::Release()
{
	if (nullptr != m_pTracer)
	{
		delete[] m_pTracer;
		m_pTracer = nullptr;
	}

	MonsterPool::Release();
}

bool MTracerPool::vir_Initialize(const monster_info_t& info)
{
	Release();

	memcpy(&m_stInfo, &info, sizeof(monster_info_t));
	m_nIDs = 1;
	m_nMax = 30;		//--
	m_pTracer = new MTracer[m_nMax];
	if (nullptr == m_pTracer)
		return false;

	for (int i = 0; i < m_nMax; i++)
		_AddToList(m_pTracer + i);

	return true;
}
