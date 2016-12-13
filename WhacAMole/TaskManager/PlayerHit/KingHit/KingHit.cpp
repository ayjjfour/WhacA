#pragma once

#include "KingHit.h"

KingHit::KingHit(MonsterManager& MM) : IHitTask(MM)
{

}

KingHit::~KingHit()
{

}

int KingHit::Protocal(pro_hit_t& ph, DataHit& dh)
{
	return emME_OK;
}

int KingHit::Calculate(pro_hit_t& ph, DataHit& dh)
{
	return emME_OK;
}

int KingHit::Statistic(pro_hit_t& ph, DataHit& dh)
{
	return emME_OK;
}

int KingHit::Reward(pro_hit_t& ph, DataHit& dh)
{
	return emME_OK;
}