#pragma once

#include "MonsterPool.h"
#include "../../Monster/Mole.h"

class MolePool : public MonsterPool
{
public:
	MolePool();
	~MolePool();

public:
	void Release();

public:
	virtual bool vir_Initialize(const monster_info_t& info);

protected:
	virtual bool vir_Expend(int nCount);
};