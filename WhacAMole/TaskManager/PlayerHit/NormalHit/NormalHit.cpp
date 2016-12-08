#pragma once

#include "NormalHit.h"

int NormalHit::Protocal(pro_hit_t& ph, DataHit& dh)
{
	if (!ph.Hit.has_monsterid())
		return -3;

	monster_info_t	monster;
	monster.m_nID = ph.Hit.monsterid();

	dh.m_obj_normal.Insert(monster);	

	return emME_OK;
}

int NormalHit::Calculate(pro_hit_t& ph, DataHit& dh)
{

	for (dh.m_obj_normal.Begin(); !dh.m_obj_normal.IsEnd(); dh.m_obj_normal.Next())
	{
		monster_info_t&		monster = dh.m_obj_normal.GetSecond();
		

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