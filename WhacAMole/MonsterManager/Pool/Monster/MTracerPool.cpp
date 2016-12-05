#include "MTracerPool.h"

MTracerPool::MTracerPool()
{
	m_nMax = 30;
}

MTracerPool::~MTracerPool()
{
	Release();
}

void MTracerPool::Release()
{
	MonsterPool::Release();
}

bool MTracerPool::vir_Initialize(const monster_info_t& info)
{
	Release();

	memcpy(&m_stInfo, &info, sizeof(monster_info_t));
	m_nIDs = 1;
	m_nMax = 30;		//--
	m_nExpStep = 10;

	return vir_Expend(m_nExpStep);
}

bool MTracerPool::vir_Expend(int nCount)
{
	for (int i = 0; i < nCount; i++)
	{
		MTracer*	pTracer = new MTracer;
		if (nullptr == pTracer)
			return false;

		_AddToList(pTracer);
	}

	return true;
}
