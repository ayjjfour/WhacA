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
	int					m_nChairID;			// �����λ��
	int					m_nWeaponId;		// �����۸�
	long long			m_nWeaponCost;		// �����۸�

	MonsterData			m_obj_normal;		// ������ɱ�Ĺ���
	MonsterData			m_obj_skill;		// ���ܻ�ɱ�Ĺ���
	MonsterData			m_obj_king;			// ���������Ĺ���
};