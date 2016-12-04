#pragma once

#include "../../Monster/Monster.h"
#include "../Arena/ArenaPool.h"
#include "../Pool.h"
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
	ArenaPool*				m_pAreaPool;				// �����ع����������(�������ض���������Ӭ������������)
	monster_info_t			m_stInfo;					// ������еĹ�������

public:
	void Release(void);
	void SetArenaPool(ArenaPool* pAPool);
	ArenaPool* GetArenaPool(void) const;

public:
	virtual bool vir_Initialize(const monster_info_t& info) = 0;
	virtual int vir_Create(Monster* pMonster, void* in_pData, int& out_nID);
	virtual void vir_SetMonsterInfo(monster_info_t& out_info, void* in_pData);

protected:
	virtual int vir_CreateID(void);
	virtual void vir_Recyle(Monster* pMonster);
};