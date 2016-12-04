#include "TFlying.h"
#include "../Tools/Random.h"

TFlying::TFlying()
{

}

TFlying::~TFlying()
{

}

void TFlying::vir_BuildStartPoint(POINT& out_point)
{
	//////////////////////////////////////////////////////////////////////////
	// 出生坐标
	//int x = 0, y = 0, z = -60;
	int dir = CRandom::Random(0, 4);
	if (dir == 0) //左
	{
		out_point.x = rtOutOfScreenZone.left;
		out_point.y = CRandom::Random(-defaultHeight / 2, defaultHeight / 2);
	}
	else if (dir == 1) //上
	{
		out_point.x = CRandom::Random(-defaultWidth / 2, defaultWidth / 2);
		out_point.y = rtOutOfScreenZone.top;   //TODO: 如果Y坐标有问题再修改
	}
	else if (dir == 2) //右
	{
		out_point.x = rtOutOfScreenZone.right;
		out_point.y = CRandom::Random(-defaultHeight / 2, defaultHeight / 2);
	}
	else if (dir == 3) //下
	{
		out_point.x = CRandom::Random(-defaultWidth / 2, defaultWidth / 2);
		out_point.y = rtOutOfScreenZone.bottom;
	}
}

void TFlying::vir_BuildMovePoint(POINT& out_point)
{
	//////////////////////////////////////////////////////////////////////////
	// 飞行坐标
	out_point.x = CRandom::Random(rtPlayZone.left, rtPlayZone.right);
	out_point.y = CRandom::Random(rtPlayZone.top, rtPlayZone.bottom);

}

void TFlying::vir_BuildEscapePoint(POINT& out_point)
{
	//////////////////////////////////////////////////////////////////////////
	// 逃跑坐标
	int dir = CRandom::Random(0, 4);
	if (dir == 0) //左
	{
		out_point.x = rtOutOfScreenZone.left;
		out_point.y = CRandom::Random(-defaultHeight / 2, defaultHeight / 2);
	}
	else if (dir == 1) //上
	{
		out_point.x = CRandom::Random(-defaultWidth / 2, defaultWidth / 2);
		out_point.y = rtOutOfScreenZone.top;
	}
	else if (dir == 2) //右
	{
		out_point.x = rtOutOfScreenZone.right;
		out_point.y = CRandom::Random(-defaultHeight / 2, defaultHeight / 2);
	}
	else if (dir == 3) //下
	{
		out_point.x = CRandom::Random(-defaultWidth / 2, defaultWidth / 2);
		out_point.y = rtOutOfScreenZone.bottom;
	}
}