#pragma once

#include "Protocal/GameMessage.pb.h"
#include "GameData/DataManager.h"
#include "MonsterManager/MonsterManager.h"

typedef struct _pro_hit_s
{
	SY::PlayerHitEx			Hit;
	// IGamePlayer*		Player
}pro_hit_t;

class ITask
{
public:
	virtual int Protocal(pro_hit_t& ph, DataHit& dh) = 0;
	virtual int Calculate(pro_hit_t& ph, DataHit& dh) = 0;
	virtual int Statistic(pro_hit_t& ph, DataHit& dh) = 0;
	virtual int Reward(pro_hit_t& ph, DataHit& dh) = 0;
};

class IHitTask : public ITask
{
public:
	IHitTask(MonsterManager& MM) :m_MM(MM) {}
	~IHitTask() {}

protected:
	MonsterManager		m_MM;
};