#pragma once

#include "MonsterPool.h"
#include "../../Monster/Mole.h"

class MolePool : public MonsterPool
{
public:
	MolePool();
	~MolePool();

protected:
	Mole*		m_pMoles;

public:
	void Release();

public:
	virtual bool vir_Initialize(const monster_info_t& info);
};