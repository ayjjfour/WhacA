#pragma once

#include "ArenaConfig.h"

class Monster;

enum emAreanType {
	emAT_Hole = 1,
	emAT_TSpider = 2,
	emAT_TFlying = 3,
};

typedef	struct _arena_info_s {
	int			m_nID;
	int			m_nType;			// �������ͣ��ض���켣��
	_arena_info_s()
	{
		m_nID = 0;
		m_nType = 0;
	}
} arena_info_t;

class Arena
{
protected:
	Arena();
	virtual ~Arena();

protected:
	arena_info_t	m_stInfo;			// ������Ϣ
	Monster*		m_pMonster;			// �ó�����Ĺ���

public:
	virtual bool vir_Build(arena_info_t& info);

public:
	void SetID(int nID);
	int GetID(void);
	void SetType(int nType);
	int GetType(void);
	void SetMonster(Monster* pMonster);
	Monster* RemoveMonster(void);

};