
#include "Random.h"
#include <time.h>

int CRandom::Random(int nMin, int nMax)
{
	return (nMin == nMax) ? nMin : (int)(rand() % (nMax - nMin)) + nMin;
}