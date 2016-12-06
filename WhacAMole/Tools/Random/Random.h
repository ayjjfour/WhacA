#pragma once

#include <Windows.h>

class MRandom
{
public:
	static int Random(int start, int end);
	static float Random(float fMin, float fMax);
	static bool Prob(int nCheck, int nMax);
};