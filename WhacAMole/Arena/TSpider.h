#pragma once

#include "Trace.h"

class TSpider : public Trace
{
public:
	TSpider();
	~TSpider();

protected:
	virtual void vir_BuildStartPoint(POINT& out_point);
	virtual void vir_BuildMovePoint(POINT& out_point);
	virtual void vir_BuildEscapePoint(POINT& out_point);
};