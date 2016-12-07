#include "Error/MoleError.h"
#include "TaskPlayerHit.h"


int TaskPlayerHit::TaskBegin(/*IGamePlayer *player*/, void* data, int nSize)
{
	int				res;
	pro_hit_t		ph;
	DataHit			dh;

	do 
	{
		res = _PraseProtocal(ph, data, nSize);
		if (emME_OK != res) break;

		res = _IProtocal(ph, dh);
		if (emME_OK != res) break;

		res = _ICalculate(ph, dh);
		if (emME_OK != res) break;

		res = _IStatistic(ph, dh);
		if (emME_OK != res) break;

		res = _IReward(ph, dh);
		if (emME_OK != res) break;
	} while (0);

	return res;
}

int TaskPlayerHit::_PraseProtocal(pro_hit_t& ph, void* data, int nSize)
{
	if (nullptr == data && nSize <= 0)
		return BUILD_ERRORCODE(0, emME_PROTOCAL_NULL);

	if (!ph.PlayerHit.ParseFromArray(data, nSize))
		return BUILD_ERRORCODE(0, emME_PROTOCAL_PRASE);

	return emME_OK;
}

int TaskPlayerHit::_IProtocal(pro_hit_t& ph, DataHit& dh)
{
	vector<IProtocal*>::iterator			it;

	for (it = m_IProtocal.begin(); it != m_IProtocal.end(); ++it)
	{
		IProtocal*	pI = (*it);
		if (nullptr != pI)
			pI->Protocal(ph, dh);
	}

	return emME_OK;
}

int TaskPlayerHit::_ICalculate(pro_hit_t& ph, DataHit& dh)
{
	vector<ICalculate*>::iterator			it;

	for (it = m_ICalculate.begin(); it != m_ICalculate.end(); ++it)
	{
		ICalculate*		pI = (*it);
		if (nullptr != pI)
			pI->Calculate(ph, dh);
	}

	return emME_OK;
}

int TaskPlayerHit::_IStatistic(pro_hit_t& ph, DataHit& dh)
{
	vector<IStatistic*>::iterator			it;

	for (it = m_IStatistic.begin(); it != m_IStatistic.end(); ++it)
	{
		IStatistic*		pI = (*it);
		if (nullptr != pI)
			pI->Statistic(ph, dh);
	}

	return emME_OK;
}

int TaskPlayerHit::_IReward(pro_hit_t& ph, DataHit& dh)
{
	vector<IReward*>::iterator			it;

	for (it = m_IReward.begin(); it != m_IReward.end(); ++it)
	{
		IReward*		pI = (*it);
		if (nullptr != pI)
			pI->Reward(ph, dh);
	}

	return emME_OK;
}