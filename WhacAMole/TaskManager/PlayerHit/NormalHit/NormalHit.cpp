#pragma once

#include "Error/MoleError.h"
#include "NormalHit.h"

NormalHit::NormalHit(MonsterManager& MM) : IHitTask(MM)
{

}

NormalHit::~NormalHit()
{

}

// 校验协议
int NormalHit::Protocal(pro_hit_t& ph, DataHit& dh)
{
	if (!ph.Hit.has_normalhit())
		return -3;

	return emME_OK;
}

// 计算收益
int NormalHit::Calculate(pro_hit_t& ph, DataHit& dh)
{
	int				nID = ph.Hit.normalhit().monsterid();
	monster_info_t	info;

	// 提取怪物
	Monster* monster = m_MM.FetchMonster(nID);
	if (nullptr == monster)
	{
		// 没有找到怪物，但是客户端已经扣费了
		if (ph.Hit.normalhit().haspay())
		{
			info.m_nID			= nID;
			info.m_bIsDispear	= true;
			info.m_llWeaponCost = dh.m_nWeaponCost;
			dh.m_obj_normal.Insert(nID, info);
		}
		return -4;
	}

	if (emME_OK != monster->BeHit(emKT_Normal))
		return -5;

	if (!monster->IsDeath())
		return -6;

	monster->CalculateIncoming(dh.m_nWeaponCost);

	monster->GetInfo(info);
	m_MM.RecycleMonster(nID);

	dh.m_obj_normal.Insert(nID, info);
	
	return emME_OK;
}

// 统计数据
int NormalHit::Statistic(pro_hit_t& ph, DataHit& dh)
{
	for (dh.m_obj_normal.Begin(); !dh.m_obj_normal.IsEnd(); dh.m_obj_normal.Next())
	{
		const monster_info_t& info = dh.m_obj_normal.GetSecond();
		// 消失的怪物忽略不计
		if (info.m_bIsDispear)
			continue;

		if (info.m_bMissHit)	// 统计免伤
		{ }

		// if (info.m_nType)	// 统计怪物类型
	}

	return emME_OK;
}

// 返还收益
int NormalHit::Reward(pro_hit_t& ph, DataHit& dh)
{
	long long		llWeaponCost = 0;
	long long		llMoneyGain = 0;

	for (dh.m_obj_normal.Begin(); !dh.m_obj_normal.IsEnd(); dh.m_obj_normal.Next())
	{
		const monster_info_t& info = dh.m_obj_normal.GetSecond();
		// 消失的怪物返还金币
		if (info.m_bIsDispear)
		{
			//-- 处理金币退还
			continue;
		}

		// 计算消费与收益
		llWeaponCost += info.m_llWeaponCost;
		llMoneyGain += info.m_llMoney;
			
		//-- 构造金币返回协议

	}

	return emME_OK;
}