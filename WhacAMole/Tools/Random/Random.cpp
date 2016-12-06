
#include "MT19937.h"
#include "Random.h"
#include <Windows.h>
#include <time.h>
#include <math.h>

extern const int PrecisionNumber;

int MRandom::Random(int nMin, int nMax)
{
	//ASSERT(nMax >= nMin);
	return (nMin == nMax) ? nMin : (int)(genrand_real2() * (nMax - nMin)) + nMin;
}

float MRandom::Random(float fMin, float fMax)
{
	//ASSERT(fMin >= fMin);
	if (abs(fMax - fMin) < 0.0001)
		return fMin;

	return (float)((genrand_real2() * (int)((fMax - fMin) * PrecisionNumber)) / PrecisionNumber) + fMin;

	//return (float)(rand() % (int)((fMax - fMin) * PrecisionNumber)) / PrecisionNumber + fMin;
}

bool MRandom::Prob(int nCheck, int nMax)
{
	if (nCheck == 0 || nMax == 0) 
		return false;
	return (Random(0, nMax) < nCheck);
}