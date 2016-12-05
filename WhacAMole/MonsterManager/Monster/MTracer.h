#pragma once

#include "Monster.h"
#include "../Arena/Trace.h"

class MTracer : public Monster
{
public:
	MTracer();
	~MTracer();

private:
	Trace*			m_pTrace;

public:
	bool	SetTrace(Trace* pTrace);
	Trace*	GetTrace(void);
	Trace*	RemoveTrace(void);
};