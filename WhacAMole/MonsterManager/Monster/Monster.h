#pragma once

#include "../Arena/Arena.h"

#include "GameData/MonsterData.h"

// 怪物基类
class Monster
{
public:
	Monster();
	virtual ~Monster();

protected:
	Arena				*m_pArena;			// 怪物活动场所
	monster_info_t		m_stInfo;			// 怪物内部属性

public:
	bool		vir_Born(monster_info_t& info);

public:
	bool		IsDeath(void) const;
	int			BeHit(void);
	void		Destory(void);
	void		Reset(void);
	void		SetID(int nID);
	int			GetID(void) const;
	void		GetInfo(monster_info_t& info) const;
	void		SetArena(Arena* pArena);
	Arena*		GetArena(void) const;
	Arena*		RemoveArena(void);
};