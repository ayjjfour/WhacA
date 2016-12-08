#pragma once

//SY::PlayerHit lMessage;

#include "MonsterManager/Monster/Monster.h"
#include <list>
#include <map>

using namespace std;

enum emHitType
{
	emHT_None	= 0,
	emHT_Normal,
	emHT_Skill,
	emHT_King,
};

class MonsterData
{
public:
	MonsterData();
	~MonsterData();

protected:
	map<int, monster_info_t>					m_map_monster;
	map<int, monster_info_t>::iterator			m_it_monster;

public:
	void Release(void);

public:
	int Insert(int nID, const monster_info_t& monster);
	int GetCount(void) const;
	void Begin(void);
	bool IsEnd(void);
	void Next(void);
	int GetFirst(void);
	const monster_info_t& GetSecond(void);
};

class DataHit
{
public:
	int					m_nChairID;			// 玩家座位号
	int					m_nWeaponId;		// 武器价格
	long long			m_nWeaponCost;		// 武器价格

	MonsterData			m_obj_normal;		// 正常击杀的怪物
	MonsterData			m_obj_skill;		// 技能击杀的怪物
	MonsterData			m_obj_king;			// 鼠王暴击的怪物
};