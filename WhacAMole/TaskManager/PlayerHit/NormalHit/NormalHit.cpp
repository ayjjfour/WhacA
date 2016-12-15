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
int NormalHit::vir_Protocal(pro_hit_t& ph, DataHit& dh)
{
	if (!ph.Hit.has_normalhit())
	{
		m_emStatus = emTS_None;
		return emME_OK;
	}

	return emME_OK;
}

// 计算收益
int NormalHit::vir_Calculate(pro_hit_t& ph, DataHit& dh)
{
	return vir_CalculateMonster(ph.Hit.normalhit().monster(), emKT_Normal, dh);
}

// 统计数据
int NormalHit::vir_Statistic(pro_hit_t& ph, DataHit& dh)
{
	for (dh.m_MD.Begin(); !dh.m_MD.IsEnd(); dh.m_MD.Next())
	{
		const monster_info_t& info = dh.m_MD.GetSecond();
		// 消失的怪物忽略不计
		if (info.m_bIsDispear)
			continue;

		if (info.m_bMissHit)	// 统计免伤
		{ }

		// if (info.m_nType)	// 统计怪物类型
	}

	return emME_OK;
}