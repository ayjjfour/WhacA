#pragma once

#include "Trace.h"

class TFlying : public Trace
{
public:
	TFlying();
	~TFlying();

protected:
	virtual void vir_BuildStartPoint(POINT& out_point);
	virtual void vir_BuildMovePoint(POINT& out_point);
	virtual void vir_BuildEscapePoint(POINT& out_point);
};