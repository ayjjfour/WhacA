#pragma once

#include "ITaskInterface.h"

class TaskPlayerHit
{
public:
	int TaskBegin(/*IGamePlayer *player*/, void* data, int nSize);

protected:
	vector<IProtocal*>		m_IProtocal;		// ����Э�����ݽӿ�����
	vector<ICalculate*>		m_ICalculate;		// ��������ӿ�����
	vector<IStatistic*>		m_IStatistic;		// ͳ�ƽӿ�����
	vector<IReward*>		m_IReward;			// ���ͻ��˷����ӿ�

protected:
	int _PraseProtocal(pro_hit_t& ph, void* data, int nSize);
	int _IProtocal(pro_hit_t& ph, DataHit& dh);
	int _ICalculate(pro_hit_t& ph, DataHit& dh);
	int _IStatistic(pro_hit_t& ph, DataHit& dh);
	int _IReward(pro_hit_t& ph, DataHit& dh);

};