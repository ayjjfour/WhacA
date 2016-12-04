#include "HolePool.h"

HolePool::HolePool()
{
	Release();
}

HolePool::~HolePool()
{
	Release();
}

bool HolePool::vir_Initialize(const arena_info_t& info)
{
	Release();

	memcpy(&m_stInfo, &info, sizeof(arena_info_t));

	m_nMax = 9; //--

	return vir_Expend(m_nMax);
}

bool HolePool::vir_Expend(int nCount)
{
	for (int i = 0; i < nCount; i++)
	{
		Hole*	pHole = new Hole;
		if (nullptr == pHole)
			return false;

		pHole->SetID(i);
		pHole->SetType(m_stInfo.m_nType);
		_AddToList(pHole);
	}

	return true;
}

void HolePool::Release()
{
	ArenaPool::Release();
}