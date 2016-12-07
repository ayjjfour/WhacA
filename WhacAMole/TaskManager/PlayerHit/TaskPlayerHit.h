#pragma once

#include "ITaskInterface.h"

class TaskPlayerHit
{
public:
	int TaskBegin(/*IGamePlayer *player*/, void* data, int nSize);

protected:
	vector<IProtocal*>		m_IProtocal;		// 处理协议数据接口数组
	vector<ICalculate*>		m_ICalculate;		// 计算收益接口数组
	vector<IStatistic*>		m_IStatistic;		// 统计接口数组
	vector<IReward*>		m_IReward;			// 给客户端反馈接口

protected:
	int _PraseProtocal(pro_hit_t& ph, void* data, int nSize);
	int _IProtocal(pro_hit_t& ph, DataHit& dh);
	int _ICalculate(pro_hit_t& ph, DataHit& dh);
	int _IStatistic(pro_hit_t& ph, DataHit& dh);
	int _IReward(pro_hit_t& ph, DataHit& dh);

};