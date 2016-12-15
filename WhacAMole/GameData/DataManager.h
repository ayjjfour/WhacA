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
	int					m_nChairID;			// �����λ��
	int					m_nWeaponId;		// ����ID
	long long			m_llWeaponCost;		// �����۸�
	bool				m_bIsCriticalHit;	// �����Ƿ񱩻�

	long long			m_llMoney;			// ���λ�ɱ������
	long long			m_llTicket;			// ���λ�ɱ����Ʊ��
	long long			m_llCost;			// ���λ�ɱ�ܻ���

	MonsterData			m_MD;				// ��ɱ�����������
};