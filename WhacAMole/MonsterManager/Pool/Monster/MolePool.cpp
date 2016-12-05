#include "MolePool.h"

MolePool::MolePool()
{
	m_nMax = 9;
}

MolePool::~MolePool()
{
	Release();
}

void MolePool::Release()
{
	MonsterPool::Release();
}

bool MolePool::vir_Initialize(const monster_info_t& info)
{
	Release();

	memcpy(&m_stInfo, &info, sizeof(monster_info_t));
	m_nIDs = 1;
	m_nMax = 9;	//--
	m_nExpStep = 3;

	return vir_Expend(m_nExpStep);
}

bool MolePool::vir_Expend(int nCount)
{
	for (int i = 0; i < nCount; i++)
	{
		Mole*		pMole = new Mole;
		if (nullptr == pMole)
			return false;

		_AddToList(pMole);
	}
		
	return true;
}