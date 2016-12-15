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

enum emTaskStatus
{
	emTS_None	= 0,
	emTS_Protocal,
	emTS_Calculate,
	emTS_Statistic,
	emTS_Reward,
	emTS_All,
};

class IHitTask : public ITask
{
public:
	IHitTask(MonsterManager& MM) :m_MM(MM) {
		m_emStatus = emTS_Protocal;
	}

	~IHitTask() {}

protected:
	MonsterManager		m_MM;
	emTaskStatus		m_emStatus;

public:
	virtual int Protocal(pro_hit_t& ph, DataHit& dh);
	virtual int Calculate(pro_hit_t& ph, DataHit& dh);
	virtual int Statistic(pro_hit_t& ph, DataHit& dh);
	virtual int Reward(pro_hit_t& ph, DataHit& dh);

protected:
	virtual int vir_Protocal(pro_hit_t& ph, DataHit& dh) = 0;
	virtual int vir_Calculate(pro_hit_t& ph, DataHit& dh) = 0;
	virtual int vir_Statistic(pro_hit_t& ph, DataHit& dh) = 0;
	virtual int vir_Reward(pro_hit_t& ph, DataHit& dh);
	
protected:
	bool _IsProtocalStatus();
	bool _IsCalculateStatus();
	bool _IsStatisticStatus();
	bool _IsRewardStatus();

protected:
	//  计算某只怪物的收益
	virtual int vir_CalculateMonster(const SY::MonsterEx& pbMonster, emKillType emType, DataHit& dh);
	bool _IsValidHit(Monster* monster, emKillType emType);
};