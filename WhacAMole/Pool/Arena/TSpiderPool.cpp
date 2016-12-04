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
	m_pTSpiders = new TSpider[m_nMax];
	if (nullptr == m_pTSpiders)
		return false;

	for (int i = 0; i < m_nMax; i++)
	{
		m_pTSpiders[i].SetID(i);
		m_pTSpiders[i].SetType(m_stInfo.m_nType);
		_AddToList(m_pTSpiders + i);
	}

	return true;
}

void TSpiderPool::Release()
{
	if (nullptr != m_pTSpiders)
	{
		delete[] m_pTSpiders;
		m_pTSpiders = nullptr;
	}

	ArenaPool::Release();
}