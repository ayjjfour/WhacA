#include "TSpiderPool.h"

TSpiderPool::TSpiderPool()
{
	Release();
}

TSpiderPool::~TSpiderPool()
{
	Release();
}

bool TSpiderPool::vir_Initialize(const arena_info_t& info)
{
	Release();

	memcpy(&m_stInfo, &info, sizeof(arena_info_t));

	m_nMax = 30; //--
	m_nExpStep = 10;
	
	return vir_Expend(m_nExpStep);
}

bool TSpiderPool::vir_Expend(int nCount)
{
	for (int i = 0; i < nCount; i++)
	{
		TSpider*	pTSpider = new TSpider;
		if (nullptr == pTSpider)
			return false;

		pTSpider->SetID(i);
		pTSpider->SetType(m_stInfo.m_nType);
		_AddToList(pTSpider);
	}

	return true;
}

void TSpiderPool::Release()
{
	ArenaPool::Release();
}