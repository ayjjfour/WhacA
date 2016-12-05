#pragma once

#include <windows.h>

const static int MAX_HOLE = 9;  //地鼠的洞的数量
const static int defaultWidth = 1920;
const static int defaultHeight = 1080;
const static float fBorderDist[] = { 0.1614583f, 0.148148f, 0.1614583f, 0.148148f };
const static float fOuterDist = 0.092593f * 2;

const static RECT rtPlayZone = {
	LONG(defaultWidth * (-0.5f + fBorderDist[0])),
	LONG(defaultHeight * (-0.5f + fBorderDist[1])),
	LONG(defaultWidth * (0.5f - fBorderDist[2])),
	LONG(defaultHeight * (1.0f - fBorderDist[3])) };

const static RECT rtOutOfScreenZone = {
	LONG(defaultWidth * (-0.5f - fOuterDist)),
	LONG(defaultHeight * (-0.5f - fOuterDist)),
	LONG(defaultWidth * (0.5f + fOuterDist)),
	LONG(defaultHeight * (0.5f + fOuterDist)) };

const static int PrecisionNumber = 10000;     // 配制中的精度 小数点后4位
