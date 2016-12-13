#pragma once

#include "TaskManager/PlayerHIt/ITaskInterface.h"
#include "MonsterManager/MonsterManager.h"

class NormalHit : public IHitTask
{
public:
	NormalHit(MonsterManager& MM);
	~NormalHit();

public:
	virtual int Protocal(pro_hit_t& ph, DataHit& dh);
	virtual int Calculate(pro_hit_t& ph, DataHit& dh);
	virtual int Statistic(pro_hit_t& ph, DataHit& dh);
	virtual int Reward(pro_hit_t& ph, DataHit& dh);
};