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
	map<int, Monster*>					m_map_monster;
	map<int, Monster*>::iterator		m_it_monster;

public:
	void Release(void);

public:
	int Insert(int nID, const Monster* monster);
	int GetCount(void) const;
	void Begin(void);
	bool IsEnd(void);
	void Next(void);
	int GetFirst(void);
	const Monster* GetSecond(void);
};

class DataManager
{
public:
	int					m_nWeaponCost;		// �����۸�
	MonsterData			m_obj_normal;		// ������ɱ�Ĺ���
	MonsterData			m_obj_skill;		// ���ܻ�ɱ�Ĺ���
	MonsterData			m_obj_king;			// ���������Ĺ���
};