#pragma once

#include "TaskManager/PlayerHIt/ITaskInterface.h"

class SkillHit : public IHitTask
{
public:
	SkillHit(MonsterManager& MM);
	~SkillHit();


protected:
	virtual int vir_Protocal(pro_hit_t& ph, DataHit& dh);
	virtual int vir_Calculate(pro_hit_t& ph, DataHit& dh);
	virtual int vir_Statistic(pro_hit_t& ph, DataHit& dh);
};