#pragma once

#include <time.h>

enum emLiveStatus {
	emLS_Death = -1,
	emLS_None = 0,
	emLS_Born = 1,
};

enum emKillType {
	emKT_None	= 0,
	emKT_Normal,
	emKT_Light,
	emKT_Fire,
	emKT_Water,
	emKT_Aerolite,
	emKT_King,
};

#define		NORMAL_RATE			1000

// 怪物信息结构
typedef struct _monster_info_s {
	// 怪物出生时设置的属性
	int					m_nID;						// 怪物ID
	emLiveStatus		m_emLiveStatus;				// 怪物生存标志（取值范围见枚举emLiveStatus）
	time_t				m_nBronTime;				// 怪物出生时间
	int					m_nCrazyRate;				// 狂暴倍率（放大1000倍）

	// 从配置中读取的属性，基本不变
	char				m_Name[64];					// 怪物名称
	int					m_nType;					// 怪物类型
	int					m_nHPMax;					// 怪物的最大hp
	int					m_nHPCur;					// 怪物的当前hp
	int					m_nRateMin;					// 怪物的最低倍数
	int					m_nRateMax;					// 怪物的最高倍数
	int					m_nMissRate;				// 怪物免伤指数（免伤率 = 免伤指数/免伤基数）
	
	// 怪物被击杀后，计算的数据
	bool				m_bIsDispear;				// 怪物是否已经消失(服务器已经处理掉了)
	bool				m_bHasIncoming;				// 怪物是否有收益
	bool				m_bMissHit;					// 怪物是否发生免伤
	emKillType			m_emKillType;				// 被击杀方式
	int					m_nKillRate;				// 怪物被击杀时的倍数
	long long			m_llMoney;					// 击杀怪物的金币收益
	long long			m_llTicket;					// 击杀怪物的礼票收益
	long long			m_llWeaponCost;				// 击杀怪物的武器消费

	_monster_info_s()
	{
		memset(this, 0, sizeof(_monster_info_s));
	}

	_monster_info_s& operator=(_monster_info_s& in)
	{
		memcpy(this, &in, sizeof(_monster_info_s));
		return *this;
	}
} monster_info_t;