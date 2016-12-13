#pragma once

#include "Error/MoleError.h"
#include "NormalHit.h"

NormalHit::NormalHit(MonsterManager& MM) : IHitTask(MM)
{

}

NormalHit::~NormalHit()
{

}

int NormalHit::Protocal(pro_hit_t& ph, DataHit& dh)
{
	if (!ph.Hit.has_monsterid())
		return -3;

	monster_info_t	monster;
	monster.m_nID = ph.Hit.monsterid();

	dh.m_obj_normal.Insert(monster.m_nID, monster);	

	return emME_OK;
}

// º∆À„ ’“Ê
int NormalHit::Calculate(pro_hit_t& ph, DataHit& dh)
{

	for (dh.m_obj_normal.Begin(); !dh.m_obj_normal.IsEnd(); dh.m_obj_normal.Next())
	{
		const monster_info_t&	monster = dh.m_obj_normal.GetSecond();
		
		m_MonsterManager.
	}
	return emME_OK;
}

int NormalHit::Statistic(pro_hit_t& ph, DataHit& dh)
{
	return emME_OK;
}

int NormalHit::Reward(pro_hit_t& ph, DataHit& dh)
{
	return emME_OK;
}