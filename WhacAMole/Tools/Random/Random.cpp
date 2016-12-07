
#include "MT19937.h"
#include "Random.h"
#include <Windows.h>
#include <time.h>
#include <math.h>

int MRandom::Random(int nMin, int nMax)
{
	//ASSERT(nMax >= nMin);
	return (nMin == nMax) ? nMin : (int)(genrand_real2() * (nMax - nMin)) + nMin;
}

bool MRandom::Prob(int nCheck, int nMax)
{
	if (nCheck == 0 || nMax == 0) 
		return false;
	return (Random(0, nMax) < nCheck);
}