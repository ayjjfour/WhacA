#pragma once

#include "ITaskInterface.h"
#include "./NormalHit/NormalHit.h"
#include "./SkillHit/SKillHit.h"
#include "./KingHit/KingHit.h"

class TaskPlayerHit
{
public:
	TaskPlayerHit(MonsterManager& MM);
	~TaskPlayerHit();

public:
	int Initialize(void);
	int TaskBegin(/*IGamePlayer *player*/, void* data, int nSize);

protected:
	vector<ITask*>			m_ITask;			// 处理协议数据接口数组

	NormalHit				m_TaskNormal;
	SkillHit				m_TaskSkill;
	KingHit					m_TaskKing;

protected:
	MonsterManager&			m_MonsterManager;

protected:
	int _PraseProtocal(pro_hit_t& ph, void* data, int nSize);
};