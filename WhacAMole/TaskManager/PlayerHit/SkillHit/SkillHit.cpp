#pragma once

#include "Error/MoleError.h"
#include "SkillHit.h"

SkillHit::SkillHit(MonsterManager& MM) : IHitTask(MM)
{

}

SkillHit::~SkillHit()
{

}

int SkillHit::vir_Protocal(pro_hit_t& ph, DataHit& dh)
{
	if (!ph.Hit.has_skillhit() || 0 >= ph.Hit.skillhit().skill_list_size())
	{
		m_emStatus = emTS_None;
		return emME_OK;
	}

	return emME_OK;
}

int SkillHit::vir_Calculate(pro_hit_t& ph, DataHit& dh)
{
	int	list_size = ph.Hit.skillhit().skill_list_size();

	for (int i = 0; i < list_size; i++)
	{
		const SY::SkillList&	skill_list = ph.Hit.skillhit().skill_list(i);
		int						monster_size = skill_list.monster_list_size();
		for (int j = 0; j < monster_size; j++)
		{
			const SY::MonsterEx&	monster = skill_list.monster_list(j);
			vir_CalculateMonster(monster, (emKillType)skill_list.skillid(), dh);
		}
	}
	
	return emME_OK;
}

int SkillHit::vir_Statistic(pro_hit_t& ph, DataHit& dh)
{
	return emME_OK;
}