#pragma once

#include "Error/MoleError.h"
#include "SkillHit.h"

SkillHit::SkillHit(MonsterManager& MM) : IHitTask(MM)
{

}

SkillHit::~SkillHit()
{

}

int SkillHit::Protocal(pro_hit_t& ph, DataHit& dh)
{
	return emME_OK;
}

int SkillHit::Calculate(pro_hit_t& ph, DataHit& dh)
{
	return emME_OK;
}

int SkillHit::Statistic(pro_hit_t& ph, DataHit& dh)
{
	return emME_OK;
}

int SkillHit::Reward(pro_hit_t& ph, DataHit& dh)
{
	return emME_OK;
}