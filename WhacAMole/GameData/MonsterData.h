#pragma once

#include <time.h>

enum emLiveStatus {
	emLS_Death = -1,
	emLS_None = 0,
	emLS_Born = 1,
};

// 怪物信息结构
typedef struct _monster_info_s {
	int					m_nMonsterID;				// 怪物ID
	emLiveStatus		m_emLiveStatus;				// 怪物生存标志（取值范围见枚举emLiveStatus）
	time_t				m_nBronTime;				// 怪物出生时间
	char				m_Name[64];					// 怪物名称
	int					m_nType;					// 怪物类型
	int					m_nHPMax;					// 怪物的最大hp
	int					m_nHPCur;					// 怪物的当前hp
	int					m_nRateMin;					// 怪物的最低倍数
	int					m_nRateMax;					// 怪物的最高倍数
	int					m_nMissRate;				// 怪物免伤（免伤率 = MissRate/基数）
	int					m_nKillRate;				// 怪物被击杀时的倍数
	bool				m_bHasIncoming;				// 怪物是否有收益
	bool				m_bCrazy;					// 是否狂暴

	_monster_info_s()
	{
		memset(this, 0, sizeof(_monster_info_s));
	}
} monster_info_t;