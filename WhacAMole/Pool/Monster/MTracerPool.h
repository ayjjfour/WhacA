#pragma once
#include "MonsterPool.h"
#include "../../Monster/MTracer.h"

class MTracerPool : public MonsterPool
{
public:
	MTracerPool();
	~MTracerPool();

public:
	void Release();

public:
	virtual bool vir_Initialize(const monster_info_t& info);

protected:
	virtual bool vir_Expend(int nCount);
};