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
	// 写成虚函数，如果某种怪物有特殊的创建方式，继承实现之
	virtual bool vir_Born(monster_info_t& info);

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

public:
	bool		CalculateIncoming(int nWeapon);

protected:
	// 以下方法写成虚函数，如果怪物有特殊算法，继承实现之
	virtual long long _vir_CalculateWeaponCost(void);		// 计算武器消耗
	virtual bool _vir_CalculateMissHit(void);				// 计算是否免伤
	virtual int _vir_CalculateKillRate(void);				// 计算击杀倍率
	virtual bool _vir_CalculateHasIncoming(void);			// 计算是否有收益
	virtual long long _vir_CalculateMoney(void);			// 计算金币收益
	virtual long long _vir_CalculateTicket(void);			// 计算礼票收益
};