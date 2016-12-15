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
	DataHit() {
		m_nChairID = -1;
		m_nWeaponId = -1;
		m_llWeaponCost = 0;
		m_bIsCriticalHit = false;
		m_llMoney = 0;
		m_llTicket = 0;
		m_llCost = 0;
		m_MD.Release();
	}
	virtual ~DataHit() {}

public:
	int					m_nChairID;			// 玩家座位号
	int					m_nWeaponId;		// 武器ID
	long long			m_llWeaponCost;		// 武器价格
	bool				m_bIsCriticalHit;	// 鼠王是否暴击

	long long			m_llMoney;			// 本次击杀总收益
	long long			m_llTicket;			// 本次击杀总礼票数
	long long			m_llCost;			// 本次击杀总花费

	MonsterData			m_MD;				// 击杀怪物结算数据
};