#include "Trace.h"

Trace::Trace()
{
	m_pMonster = nullptr;
}

Trace::~Trace()
{
	m_pMonster = nullptr;
}

bool Trace::vir_Build(arena_info_t& info)
{
	POINT		point;

	vir_BuildStartPoint(point);
	SetPoints(point, 0);

	vir_BuildMovePoint(point);
	SetPoints(point, 1);

	vir_BuildEscapePoint(point);
	SetPoints(point, 2);

	return true;
}

bool Trace::SetPoints(POINT& point, int nIndex)
{
	if (nIndex < 0 || nIndex > MAX_POINT)
		return false;

	m_Point[nIndex] = point;

	return true;
}

POINT& Trace::GetPoint(int nIndex)
{
	if (nIndex < 0 || nIndex > MAX_POINT)
		nIndex = 0;

	return m_Point[nIndex];
}