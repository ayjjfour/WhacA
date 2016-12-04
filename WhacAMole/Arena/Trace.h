#pragma once

#include "Arena.h"
#include <Windows.h>

#define		MAX_POINT		3

class Trace : public Arena
{
protected:
	Trace();
	~Trace();

protected:
	POINT		m_Point[MAX_POINT];

public:
	bool SetPoints(POINT& point, int nIndex);
	POINT& GetPoint(int nIndex);

public:
	virtual bool vir_Build(arena_info_t& info);

protected:
	virtual void vir_BuildStartPoint(POINT& out_point) = 0;
	virtual void vir_BuildMovePoint(POINT& out_point) = 0;
	virtual void vir_BuildEscapePoint(POINT& out_point) = 0;
};