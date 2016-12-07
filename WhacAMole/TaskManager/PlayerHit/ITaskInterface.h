#pragma once

#include "Protocal/GameMessage.pb.h"
#include "GameData/DataManager.h"

using namespace SY;

typedef struct _pro_hit_s
{
	PlayerHit			Hit;
	// IGamePlayer*		Player
}pro_hit_t;

class IProtocal
{
public:
	virtual int Protocal(pro_hit_t& ph, DataHit& dh) = 0;
};

class ICalculate
{
public:
	virtual int Calculate(pro_hit_t& ph, DataHit& dh) = 0;
};

class IStatistic
{
public:
	virtual int Statistic(pro_hit_t& ph, DataHit& dh) = 0;
};

class IReward
{
public:
	virtual int Reward(pro_hit_t& ph, DataHit& dh) = 0;
};