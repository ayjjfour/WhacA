#pragma once
#include "MonsterPool.h"
#include "../../Monster/MTracer.h"

class MTracerPool : public MonsterPool
{
public:
	MTracerPool();
	~MTracerPool();

protected:
	MTracer*		m_pTracer;

public:
	void Release();

public:
	virtual bool vir_Initialize(const monster_info_t& info);
};