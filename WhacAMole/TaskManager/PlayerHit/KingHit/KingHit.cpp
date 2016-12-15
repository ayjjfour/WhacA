#pragma once

#include "KingHit.h"
#include "Tools/Random/MT19937.h"

#define		IS_NOT_KING		-1
#define		IS_KING			0
#define		NOT_FOUND		1

KingHit::KingHit(MonsterManager& MM) : IHitTask(MM)
{
}

KingHit::~KingHit()
{
}

int KingHit::vir_Protocal(pro_hit_t& ph, DataHit& dh)
{
	// 是否有鼠王对象
	if (!ph.Hit.has_kinghit())
	{
		m_emStatus = emTS_None;
		return emME_OK;
	}

	// 判断是否鼠王
	int res = _IsKing(ph.Hit.kinghit().king().monsterid());
	if (IS_NOT_KING == res)
	{
		m_emStatus = emTS_None;	// 跳过后续的步骤
		return emME_OK;
	}

	m_emStatus = emTS_Calculate;

	return emME_OK;
}

int KingHit::vir_Calculate(pro_hit_t& ph, DataHit& dh)
{
	const SY::KingEx&		kingEx = ph.Hit.kinghit();
	int						list_size = kingEx.monster_list_size();
	
	// 先计算鼠王的收益和免伤
	const SY::MonsterEx& monster = kingEx.king();
	int res = IHitTask::vir_CalculateMonster(monster, emKT_King, dh);
	if (res != emME_OK)	// 鼠王是否正常击毙
	{
		m_emStatus = emTS_Reward;	// 跳过统计，直接到结算
		return emME_OK;
	}
		
	// 判断鼠王是否免伤
	if (_IsMissHit(monster.monsterid()))
		return emME_OK;

	// 计算是否暴击
	dh.m_bIsCriticalHit = _IsCriticalHit(list_size);
	if (!dh.m_bIsCriticalHit)
		return emME_OK;

	// 如果有暴击，计算每个怪物的收益
	for (int i = 0; i < list_size; i++)
	{
		const SY::MonsterEx&	monster = kingEx.monster_list(i);
		vir_CalculateMonster(monster, emKT_King, dh);
	}

	return emME_OK;
}

int KingHit::vir_Statistic(pro_hit_t& ph, DataHit& dh)
{
	return emME_OK;
}

int KingHit::vir_Reward(pro_hit_t& ph, DataHit& dh)
{
	IHitTask::vir_Reward(ph, dh);

	// 返回雷神之锤的消息
	// dh.m_bIsCriticalHit

	return emME_OK;
}

int KingHit::vir_CalculateMonster(const SY::MonsterEx& pbMonster, emKillType emType, DataHit& dh)
{
	int					nID = pbMonster.monsterid();
	Monster*			monster = m_MM.FetchMonster(nID);
	monster_info_t		info;

	if (nullptr == monster)
		return emME_OK;

	// 正常击杀怪物
	monster->CalculateIncoming(dh.m_llWeaponCost);
	monster->GetInfo(info);
	m_MM.RecycleMonster(nID);

	info.m_bHasPay = false;
	info.m_emKillType = emType;
	dh.m_MD.Insert(nID, info);

	return emME_OK;
}

int KingHit::_IsKing(int nID)
{
	Monster* king = m_MM.FetchMonster(nID);
	if (nullptr == king)
		return NOT_FOUND;

	monster_info_t	info;
	king->GetInfo(info);
	if (info.m_emType == mtMoleKing)
		return IS_KING;

	return IS_NOT_KING;
}

bool KingHit::_IsMissHit(int nID)
{
	Monster* king = m_MM.FetchMonster(nID);
	if (nullptr == king)
		return true;

	monster_info_t	info;
	king->GetInfo(info);
	if (info.m_bMissHit)
		return true;

	return false;
}

bool KingHit::_IsCriticalHit(int size)
{
	if (size <= 0)
		return false;

	double dRate = -1;

	dRate = 10000.0 / size;

	if ((genrand_real2() * 10000) >= dRate)
		return false;

	return true;
}