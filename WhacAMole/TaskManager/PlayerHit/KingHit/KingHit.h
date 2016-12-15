#pragma once

#include "TaskManager/PlayerHIt/ITaskInterface.h"

class KingHit : public IHitTask
{
public:
	KingHit(MonsterManager& MM);
	~KingHit();

protected:
	virtual int vir_Protocal(pro_hit_t& ph, DataHit& dh);
	virtual int vir_Calculate(pro_hit_t& ph, DataHit& dh);
	virtual int vir_Statistic(pro_hit_t& ph, DataHit& dh);
	virtual int vir_Reward(pro_hit_t& ph, DataHit& dh);

protected:
	virtual int vir_CalculateMonster(const SY::MonsterEx& pbMonster, emKillType emType, DataHit& dh);

protected:
	int _IsKing(int nID);
	bool _IsMissHit(int nID);
	bool _IsCriticalHit(int size);
};