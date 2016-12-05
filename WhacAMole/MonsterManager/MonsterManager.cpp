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
// 初始化接口
bool MonsterManager::Initialize()
{
	bool		res;

	do
	{
		// 初始化怪物组
		res = _Initialize_MonsterSeq();
		if (!res) break;

		// 初始化区域池
		res = _Initialize_ArenaPool();
		if (!res) break;

		// 初始化怪物池
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

// 初始化区域池
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

// 初始化怪物池
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
	//-- 从配置中取指定类型的怪物数据
	out_info.m_nType = nType;
	_snprintf_s(out_info.m_Name, sizeof(out_info.m_Name) - 1, "怪物%d", nType);
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
// 工作接口
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
	// 生产一只地鼠类怪物
	_CreateFromGroup(in_info, out_lMonster, m_MoleSeq);

	// 生产一只轨迹类怪物
	_CreateFromGroup(in_info, out_lMonster, m_OtherSeq);
}

// 从一组怪物中，随机产生一只怪物
// 参数列表：
//	in_info				[in] 生产怪物时的信息，如是否狂暴期间等
//	out_lMonster		[out] 生产怪物的输出列表
//	seq					[in] 怪物序列（从这组怪物中随机生产一个）
//	pAPool				[in] 区域池，每只怪物要匹配一个活动区域（如：地鼠匹配地洞，苍蝇匹配飞行轨迹等）
void MonsterManager::_CreateFromGroup(create_info_t& in_info, list<Monster*>& out_lMonster, vector<int>& seq)
{
	shuffle(seq.begin(), seq.end(), default_random_engine(m_seed));

	// 根据每只怪物配置的概率，随机选择一只
	int idx = _GetRandomMonsterType(seq);
	if (idx < 0)
		return;

	do
	{
		// 生产怪物
		int nType = seq[idx];
		Monster* pMonster = nullptr;
		int res = _CreateFromPool(nType, in_info, pMonster);
		if (emME_OK != res)
		{
			// 如果生产达到最大数目，继续下一只
			if (emME_OBJ_USEDOUT == GETPRO_ERROR(res))
			{ idx++; continue; }
			else
			{ break; }
		}

		// 将怪物放入输出列表
		out_lMonster.push_back(pMonster);
		break;
	} while (idx < (int)seq.size());

	return;
}

void MonsterManager::_RecycleMonster(int nID)												// 回收怪物
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
	//-- 获取怪物的算法要根据配置来
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
