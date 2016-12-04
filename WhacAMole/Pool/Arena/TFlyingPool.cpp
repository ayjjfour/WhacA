#include "TFlyingPool.h"

TFlyingPool::TFlyingPool()
{
	Release();
}

TFlyingPool::~TFlyingPool()
{
	Release();
}

bool TFlyingPool::vir_Initialize(const arena_info_t& info)
{
	Release();

	memcpy(&m_stInfo, &info, sizeof(arena_info_t));

	m_nMax = 30; //--
	m_nExpStep = 10;

	return vir_Expend(m_nExpStep);
}

bool TFlyingPool::vir_Expend(int nCount)
{
	for (int i = 0; i < nCount; i++)
	{
		TFlying* pTFlyings = new TFlying;
		if (nullptr == pTFlyings)
			return false;

		pTFlyings->SetID(i);
		pTFlyings->SetType(m_stInfo.m_nType);
		_AddToList(pTFlyings);
	}

	return true;
}

void TFlyingPool::Release()
{
	ArenaPool::Release();
}