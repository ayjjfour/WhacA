#pragma once

#include "TaskManager/PlayerHIt/ITaskInterface.h"
#include "MonsterManager/MonsterManager.h"

class NormalHit : public IHitTask
{
public:
	NormalHit(MonsterManager& MM);
	~NormalHit();

protected:
	virtual int vir_Protocal(pro_hit_t& ph, DataHit& dh);
	virtual int vir_Calculate(pro_hit_t& ph, DataHit& dh);
	virtual int vir_Statistic(pro_hit_t& ph, DataHit& dh);
};