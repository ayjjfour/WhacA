#include "TSpider.h"
#include "Tools/Random/Random.h"

TSpider::TSpider()
{

}

TSpider::~TSpider()
{

}

void TSpider::vir_BuildStartPoint(POINT& out_point)
{
	//////////////////////////////////////////////////////////////////////////
	// ��������
	// ��֩����˵��ֻ�ܴ��������
	int rtPlayZoneWidth = rtPlayZone.right - rtPlayZone.left;
	out_point.x = MRandom::Random(-rtPlayZoneWidth / 2, rtPlayZoneWidth / 2);
	out_point.y = defaultHeight / 2; // Screen.height; //rtOutOfScreenZone.yMax;
}

void TSpider::vir_BuildMovePoint(POINT& out_point)
{
	//////////////////////////////////////////////////////////////////////////
	// ��������
	int dist = MRandom::Random((int)(defaultHeight*0.4f), defaultHeight /*(int)rtPlayZone.height*/) + defaultHeight * (int)(fOuterDist + fBorderDist[1]);
	out_point.x = m_Point[0].x;
	out_point.y = m_Point[0].y - dist;
}

void TSpider::vir_BuildEscapePoint(POINT& out_point)
{
	//////////////////////////////////////////////////////////////////////////
	// ��������
	int dist = defaultHeight;
	out_point.x = m_Point[0].x;
	out_point.y = m_Point[0].y + defaultHeight;
}