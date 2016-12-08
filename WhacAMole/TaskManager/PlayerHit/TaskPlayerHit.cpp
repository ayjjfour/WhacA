#include "Error/MoleError.h"
#include "TaskPlayerHit.h"
#include "./NormalHit/NormalHit.h"
#include "MonsterManager/MonsterManager.h"

TaskPlayerHit::TaskPlayerHit(MonsterManager& MM):m_MonsterManager(MM)
{
}

TaskPlayerHit::~TaskPlayerHit()
{

}

int TaskPlayerHit::Initialize(void)
{
	m_ITask.insert(&m_TaskNormal);	// 正常打击任务
	m_ITask.insert(&m_TaskSkill);	// 技能打击任务
	m_ITask.insert(&m_TaskKing);	// 鼠王暴击任务
}

int TaskPlayerHit::TaskBegin(/*IGamePlayer *player*/, void* data, int nSize)
{
	int								res;
	pro_hit_t						ph;
	DataHit							dh;
	vector<ITask*>::iterator		it;

	res = _PraseProtocal(ph, data, nSize, dh);
	if (emME_OK != res) break;

	for (it = m_ITask.begin(); it != m_ITask.end(); ++it)
	{
		ITask*		Ip = (*it);
		if (nullptr == Ip)
			continue;

		res = Ip->Protocal(ph, dh);
		if (emME_OK != res)
			continue;

		res = Ip->Calculate(ph, dh);
		if (emME_OK != res)
			continue;

		res = Ip->Statistic(ph, dh);
		if (emME_OK != res)
			continue;

		res = Ip->Reward(ph, dh);
		if (emME_OK != res)
			continue;
	}

	return res;
}

int TaskPlayerHit::_PraseProtocal(pro_hit_t& ph, void* data, int nSize, DataHit& dh)
{
	if (nullptr == data && nSize <= 0)
		return BUILD_ERRORCODE(0, emME_PROTOCAL_NULL);

	if (!ph.PlayerHit.ParseFromArray(data, nSize))
		return BUILD_ERRORCODE(0, emME_PROTOCAL_PRASE);

	if (!ph.Hit.has_chairid())
		return BUILD_ERRORCODE(0, emME_HIT_CHAIRID);
	dh.m_nChairID = ph.Hit.chairid();

	if (!ph.Hit.has_weaponid())
		return  BUILD_ERRORCODE(0, emME_HIT_WEAPONID);
	dh.m_nWeaponId = ph.Hit.weaponid();
	
	return emME_OK;
}