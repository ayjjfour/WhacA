#include "MolePool.h"

MolePool::MolePool()
{
	m_nMax = 9;
	m_pMoles = nullptr;
}

MolePool::~MolePool()
{
	Release();
}

void MolePool::Release()
{
	if (nullptr != m_pMoles)
	{
		delete[] m_pMoles;
		m_pMoles = nullptr;
	}

	MonsterPool::Release();
}

bool MolePool::vir_Initialize(const monster_info_t& info)
{
	Release();

	memcpy(&m_stInfo, &info, sizeof(monster_info_t));
	m_nIDs = 1;
	m_nMax = 9;	//--
	m_pMoles = new Mole[m_nMax];
	if (nullptr == m_pMoles)
		return false;

	for (int i = 0; i < m_nMax; i++)
		_AddToList(m_pMoles + i);

	return true;
}