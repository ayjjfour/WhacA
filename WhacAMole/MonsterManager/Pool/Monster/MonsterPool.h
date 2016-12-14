#pragma once

#include "../../Monster/Monster.h"
#include "../Arena/ArenaPool.h"
#include "../../../Pool/Pool.h"
#include <map>
#include <list>

using namespace std;

const int g_c_nMaxMonsterID = 0x00FFFFFF;
#define BUILD_MONSTERID(_type_, _num_)		((((int)(_type_))<<24) | ((0xFFFFFF) & (_num_)))

class MonsterPool : public Pool<Monster>
{
protected:
	MonsterPool();
	~MonsterPool();

protected:
	ArenaPool*				m_pAreaPool;				// 与怪物池关联的区域池(如地鼠与地洞关联，苍蝇与飞行区域关联)
	monster_info_t			m_stInfo;					// 怪物池中的怪物属性

public:
	void Release(void);
	void SetArenaPool(ArenaPool* pAPool);
	ArenaPool* GetArenaPool(void) const;

public:
	virtual bool vir_Initialize(const monster_info_t& info) = 0;

protected:
	// 创建怪物
	virtual int vir_Create(Monster* pMonster, void* in_pData, int& out_nID);
	// 创建怪物时，设置怪物信息
	virtual void vir_SetMonsterInfo(monster_info_t& out_info, void* in_pData);
	// 生成怪物ID
	virtual int vir_CreateID(void);
	// 回收怪物
	virtual void vir_Recyle(Monster* pMonster);
};