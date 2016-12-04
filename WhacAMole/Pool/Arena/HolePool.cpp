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
	m_pHoles = new Hole[m_nMax];
	if (nullptr == m_pHoles)
		return false;

	for (int i = 0; i < m_nMax; i++)
	{
		m_pHoles[i].SetID(i);
		m_pHoles[i].SetType(m_stInfo.m_nType);
		_AddToList(m_pHoles + i);
	}

	return true;
}

void HolePool::Release()
{
	if (nullptr != m_pHoles)
	{
		delete[] m_pHoles;
		m_pHoles = nullptr;
	}

	ArenaPool::Release();
}