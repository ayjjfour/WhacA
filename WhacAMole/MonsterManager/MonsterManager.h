#pragma once

#include "Pool/HeadPool.h"
#include "CreateInfo.h"

#include <map>
#include <vector>
#include <list>

using namespace std;

// 怪物管理类
class MonsterManager
{
public:
	MonsterManager();
	~MonsterManager();

private:
	map<int, int>			m_mapType;				// 怪物ID到怪物类型的映射 ID -> type

	// 地鼠相关
	vector<int>				m_MoleSeq;
	HolePool				m_HolePool;				// 地鼠洞穴池
	MolePool				m_MolePersizPool;		// 波斯地鼠池
	MolePool				m_MoleNursePool;		// 护士地鼠池
	MolePool				m_MoleFlyingPool;		// 飞行地鼠池
	MolePool				m_MoleAdorablePool;		// 呆萌地鼠池
	MolePool				m_MoleMinerPool;		// 矿工地鼠池
	MolePool				m_MoleKingPool;			// 鼠王池
	
	// 其它怪物相关
	vector<int>				m_OtherSeq;
	TSpiderPool				m_TSpiderPool;			// 蜘蛛轨迹池
	TFlyingPool				m_TFlyingPool;			// 苍蝇轨迹池
	MTracerPool				m_SpiderPool;			// 蜘蛛池
	MTracerPool				m_FlyingPool;			// 苍蝇池

	// 程序控制相关
private:
	unsigned int m_seed;	// 随机数的种子

public:
	bool Initialize(void);
	void Release(void);

	void CreateMonster(create_info_t& in_info, list<Monster*>& out_lMonster);
	void RecycleMonster(int nID);
	void RecycleMonster(vector<int>& vec_type);
	void RecycleMonster(list<int>& list_type);

protected:
	// 进行一次怪物生产（每组怪物各生产一只）
	void _CreateOnce(create_info_t& in_info, list<Monster*>& out_lMonster);

	// 从一组怪物中，随机产生一只怪物
	// 参数列表：
	//	in_info				[in] 生产怪物时的信息，如是否狂暴期间等
	//	out_lMonster		[out] 生产怪物的输出列表
	//	seq					[in] 怪物序列（从这组怪物中随机生产一个）
	void _CreateFromGroup(create_info_t& in_info, list<Monster*>& out_lMonster, vector<int>& seq);

	// 回收怪物
	void _RecycleMonster(int nID);																				

	int _GetRandomMonsterType(const vector<int>& seq) const;
	int _CreateFromPool(int nType, create_info_t& in_info, Monster*& out_pMonster);

protected:
	bool _Initialize_MonsterSeq(void);
	bool _Initialize_ArenaPool(void);
	bool _initialize_MonsterPool(void);

	bool _initialize_ArenaPool(const arena_info_t& info, ArenaPool* pArenaPool);
	bool _initialize_MonsterPool(const monster_info_t& info, MonsterPool* pMonsterPool, ArenaPool* pArenaPool);
	bool _FetchMonsterInfo(int nType, monster_info_t& out_info);
};