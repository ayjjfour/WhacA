#include "MTracer.h"

MTracer::MTracer()
{
	m_pTrace = nullptr;
}

MTracer::~MTracer()
{
	m_pTrace = nullptr;
}

bool MTracer::SetTrace(Trace* pTrace)
{
	if (nullptr != m_pTrace)
		return false;

	m_pTrace = pTrace;
	return true;
}

Trace* MTracer::GetTrace()
{
	return m_pTrace;
}

Trace* MTracer::RemoveTrace()
{
	Trace* pTrace = m_pTrace;
	m_pTrace = nullptr;

	return m_pTrace;
}