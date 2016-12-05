#include "MonsterManager.h"
#include "GameData/GameConfig.h"

#include <stdio.h>

#include <algorithm>
#include <random> // std::default_random_engine  
#include <chrono> // std::chrono::system_clock  
#include <vector>

using namespace std;

MonsterManager::MonsterManager()
{
	m_seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
	m_mapType.clear();
}

MonsterManager::~MonsterManager()
{
	Release();
}

void MonsterManager::Release()
{
	return;
}

//////////////////////////////////////////////////////////////////////////
// ��ʼ���ӿ�
bool MonsterManager::Initialize()
{
	bool		res;

	do
	{
		// ��ʼ��������
		res = _Initialize_MonsterSeq();
		if (!res) break;

		// ��ʼ�������
		res = _Initialize_ArenaPool();
		if (!res) break;

		// ��ʼ�������
		res = _initialize_MonsterPool();
		if (!res) break;
		
	} while (0);
	
	return res;
}

bool MonsterManager::_Initialize_MonsterSeq(void)
{
	vector<int>		MoleSeq{ mtMolePersia, mtMoleAdorable, mtMoleFlying, mtMoleNurse, mtMoleMiner, mtMoleKing };
	m_MoleSeq.insert(m_MoleSeq.end(), MoleSeq.begin(), MoleSeq.end());

	vector<int>		OtherSeq{ mtSpider, mtFly };
	m_OtherSeq.insert(m_OtherSeq.end(), OtherSeq.begin(), OtherSeq.end());

	return true;
}

// ��ʼ�������
bool MonsterManager::_Initialize_ArenaPool(void)
{
	bool				res;
	arena_info_t		info;

	do 
	{
		info.m_nType = emAT_Hole;
		res = _initialize_ArenaPool(info, &m_HolePool);
		if (!res) break;

		info.m_nType = emAT_TSpider;
		res = _initialize_ArenaPool(info, &m_TSpiderPool);
		if (!res) break;

		info.m_nType = emAT_TFlying;
		res = _initialize_ArenaPool(info, &m_TFlyingPool);
		if (!res) break;
	} while (0);

	return res;
}

bool MonsterManager::_initialize_ArenaPool(const arena_info_t& info, ArenaPool* pArenaPool)
{
	return pArenaPool->vir_Initialize(info);
}

// ��ʼ�������
bool MonsterManager::_initialize_MonsterPool(void)
{
	bool				res;
	monster_info_t		info;

	do 
	{
		res = _FetchMonsterInfo(mtMolePersia, info);
		if (!res) break;
		res = _initialize_MonsterPool(info, &m_MolePersizPool, &m_HolePool);
		if (!res) break;

		res = _FetchMonsterInfo(mtMoleAdorable, info);
		if (!res) break;
		res = _initialize_MonsterPool(info, &m_MoleAdorablePool, &m_HolePool);
		if (!res) break;

		res = _FetchMonsterInfo(mtMoleFlying, info);
		if (!res) break;
		res = _initialize_MonsterPool(info, &m_MoleFlyingPool, &m_HolePool);
		if (!res) break;

		res = _FetchMonsterInfo(mtMoleNurse, info);
		if (!res) break;
		res = _initialize_MonsterPool(info, &m_MoleNursePool, &m_HolePool);
		if (!res) break;

		res = _FetchMonsterInfo(mtMoleMiner, info);
		if (!res) break;
		res = _initialize_MonsterPool(info, &m_MoleMinerPool, &m_HolePool);
		if (!res) break;

		res = _FetchMonsterInfo(mtMoleKing, info);
		if (!res) break;
		res = _initialize_MonsterPool(info, &m_MoleKingPool, &m_HolePool);
		if (!res) break;

		res = _FetchMonsterInfo(mtSpider, info);
		if (!res) break;
		res = _initialize_MonsterPool(info, &m_SpiderPool, &m_TSpiderPool);
		if (!res) break;

		res = _FetchMonsterInfo(mtFly, info);
		if (!res) break;
		res = _initialize_MonsterPool(info, &m_FlyingPool, &m_TFlyingPool);
		if (!res) break;
	} while (0);

	return res;
}

bool MonsterManager::_FetchMonsterInfo(int nType, monster_info_t& out_info)
{
	//-- ��������ȡָ�����͵Ĺ�������
	out_info.m_nType = nType;
	_snprintf_s(out_info.m_Name, sizeof(out_info.m_Name) - 1, "����%d", nType);
	out_info.m_nHPMax = 2;
	out_info.m_nHPCur = out_info.m_nHPMax;
	out_info.m_nRateMin = 1;
	out_info.m_nRateMax = 20;
	out_info.m_nMissRate = 10;

	return true;
}

bool MonsterManager::_initialize_MonsterPool(const monster_info_t& info, MonsterPool* pMonsterPool, ArenaPool* pArenaPool)
{
	if (!pMonsterPool->vir_Initialize(info))
		return false;

	pMonsterPool->SetArenaPool(pArenaPool);
	return true;
}

//////////////////////////////////////////////////////////////////////////
// �����ӿ�
void MonsterManager::CreateMonster(create_info_t& in_info, list<Monster*>& out_lMonster)
{
	for (int i = 0; i < in_info.nCount; i++)
		_CreateOnce(in_info, out_lMonster);
}

void MonsterManager::RecycleMonster(int nID)
{
	_RecycleMonster(nID);
}

void MonsterManager::RecycleMonster(vector<int>& vec_nID)
{
	vector<int>::iterator		it;

	for (it = vec_nID.begin(); it != vec_nID.end(); ++it)
	{
		_RecycleMonster((int)(*it));
	}
}

void MonsterManager::RecycleMonster(list<int>& list_nID)
{
	list<int>::iterator		it;

	for (it = list_nID.begin(); it != list_nID.end(); ++it)
	{
		_RecycleMonster((int)(*it));
	}
}

void MonsterManager::_CreateOnce(create_info_t& in_info, list<Monster*>& out_lMonster)
{
	// ����һֻ���������
	_CreateFromGroup(in_info, out_lMonster, m_MoleSeq);

	// ����һֻ�켣�����
	_CreateFromGroup(in_info, out_lMonster, m_OtherSeq);
}

// ��һ������У��������һֻ����
// �����б�
//	in_info				[in] ��������ʱ����Ϣ�����Ƿ���ڼ��
//	out_lMonster		[out] �������������б�
//	seq					[in] �������У�������������������һ����
//	pAPool				[in] ����أ�ÿֻ����Ҫƥ��һ��������磺����ƥ��ض�����Ӭƥ����й켣�ȣ�
void MonsterManager::_CreateFromGroup(create_info_t& in_info, list<Monster*>& out_lMonster, vector<int>& seq)
{
	shuffle(seq.begin(), seq.end(), default_random_engine(m_seed));

	// ����ÿֻ�������õĸ��ʣ����ѡ��һֻ
	int idx = _GetRandomMonsterType(seq);
	if (idx < 0)
		return;

	do
	{
		// ��������
		int nType = seq[idx];
		Monster* pMonster = nullptr;
		int res = _CreateFromPool(nType, in_info, pMonster);
		if (emME_OK != res)
		{
			// ��������ﵽ�����Ŀ��������һֻ
			if (emME_OBJ_USEDOUT == GETPRO_ERROR(res))
			{ idx++; continue; }
			else
			{ break; }
		}

		// �������������б�
		out_lMonster.push_back(pMonster);
		break;
	} while (idx < (int)seq.size());

	return;
}

void MonsterManager::_RecycleMonster(int nID)												// ���չ���
{
	map<int, int>::iterator			it;
	it = m_mapType.find(nID);
	if (it == m_mapType.end())
		return;

	int nType = (*it).second;
	m_mapType.erase(it);

	switch (nType)
	{
	case mtMolePersia:
		m_MolePersizPool.Recycle(nID);	break;
	case mtMoleAdorable:
		m_MoleAdorablePool.Recycle(nID); break;
	case mtMoleFlying:
		m_MoleFlyingPool.Recycle(nID); break;
	case mtMoleNurse:
		m_MoleNursePool.Recycle(nID); break;
	case mtMoleMiner:
		m_MoleMinerPool.Recycle(nID); break;
	case mtMoleKing:
		m_MoleKingPool.Recycle(nID); break;
	case mtSpider:
		m_SpiderPool.Recycle(nID); break;
	case mtFly:
		m_FlyingPool.Recycle(nID); break;
	default:
		break;
	}
}

int MonsterManager::_GetRandomMonsterType(const vector<int>& seq) const
{
	//-- ��ȡ������㷨Ҫ����������
	if (seq.size() <= 0)
		return -1;

	return rand() % seq.size();
}

int MonsterManager::_CreateFromPool(int nType, create_info_t& in_info, Monster*& pMonster)
{
	int res = BUILD_ERRORCODE(0, emME_MONSTER_TYPE);

	switch (nType)
	{
	case mtMolePersia:
		res = m_MolePersizPool.Create(&in_info, pMonster); break;
	case mtMoleAdorable:
		res = m_MoleAdorablePool.Create(&in_info, pMonster); break;
	case mtMoleFlying:
		res = m_MoleFlyingPool.Create(&in_info, pMonster); break;
	case mtMoleNurse:
		res = m_MoleNursePool.Create(&in_info, pMonster); break;
	case mtMoleMiner:
		res = m_MoleMinerPool.Create(&in_info, pMonster); break;
	case mtMoleKing:
		res = m_MoleKingPool.Create(&in_info, pMonster); break;
	case mtSpider:
		res = m_SpiderPool.Create(&in_info, pMonster); break;
	case mtFly:
		res = m_FlyingPool.Create(&in_info, pMonster); break;
	default:
		break;
	}

	if (nullptr != pMonster)
		m_mapType.insert(make_pair(pMonster->GetID(), nType));

	return res;
}
