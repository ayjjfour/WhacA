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
	m_pTFlyings = new TFlying[m_nMax];
	if (nullptr == m_pTFlyings)
		return false;

	for (int i = 0; i < m_nMax; i++)
	{
		m_pTFlyings[i].SetID(i);
		m_pTFlyings[i].SetType(m_stInfo.m_nType);
		_AddToList(m_pTFlyings + i);
	}

	return true;
}

void TFlyingPool::Release()
{
	if (nullptr != m_pTFlyings)
	{
		delete[] m_pTFlyings;
		m_pTFlyings = nullptr;
	}

	ArenaPool::Release();
}