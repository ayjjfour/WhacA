#pragma once

#include "./NormalHit/NormalHit.h"
#include "./SkillHit/SkillHit.h"
#include "./KingHit/KingHit.h"

enum emTaskType
{
	emTask_None		= 0,
	emTask_Normal	= 1,
	emTask_Skill,
	emTask_King,
	emTask_All,
};

class TaskPlayerHit
{
public:
	TaskPlayerHit(MonsterManager& MM);
	~TaskPlayerHit();

public:
	int Initialize(void);
	int TaskBegin(/*IGamePlayer *player,*/ void* data, int nSize);

protected:
	map<int, ITask*>		m_mapITask;			// 处理协议数据接口数组

	NormalHit				m_TaskNormal;
	SkillHit				m_TaskSkill;
	KingHit					m_TaskKing;

protected:
	MonsterManager&			m_MonsterManager;

protected:
	int _PraseProtocal(pro_hit_t& ph, void* data, int nSize, DataHit& dh);
};