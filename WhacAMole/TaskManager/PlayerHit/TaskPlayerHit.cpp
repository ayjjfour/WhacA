#include "Error/MoleError.h"
#include "TaskPlayerHit.h"
#include "./NormalHit/NormalHit.h"
#include "MonsterManager/MonsterManager.h"

TaskPlayerHit::TaskPlayerHit(MonsterManager& MM):
	m_MonsterManager(MM), m_TaskNormal(MM),	m_TaskSkill(MM), m_TaskKing(MM)
{
}

TaskPlayerHit::~TaskPlayerHit()
{

}

int TaskPlayerHit::Initialize(void)
{
	m_mapITask.insert(make_pair(emTask_Normal, &m_TaskNormal));	// 正常打击任务
	m_mapITask.insert(make_pair(emTask_Skill, &m_TaskSkill));	// 技能打击任务
	m_mapITask.insert(make_pair(emTask_King, &m_TaskKing));		// 鼠王暴击任务

	return emME_OK;
}

int TaskPlayerHit::TaskBegin(/*IGamePlayer *player,*/ void* data, int nSize)
{
	int								res = emME_OK;
	pro_hit_t						ph;
	DataHit							dh;
	map<int, ITask*>::iterator		it;

	res = _PraseProtocal(ph, data, nSize, dh);
	if (emME_OK != res) 
		return res;

	it = m_mapITask.find(ph.Hit.hittype());
	if (m_mapITask.end() == it)
		return emME_OK;

	ITask*		Ip = (*it).second;
	if (nullptr == Ip)
		return emME_OK;

	Ip->Protocal(ph, dh);
	Ip->Calculate(ph, dh);
	Ip->Statistic(ph, dh);
	Ip->Reward(ph, dh);

	return res;
}

int TaskPlayerHit::_PraseProtocal(pro_hit_t& ph, void* data, int nSize, DataHit& dh)
{
	if (nullptr == data && nSize <= 0)
		return BUILD_ERRORCODE(0, emME_PROTOCAL_NULL);

	if (!ph.Hit.ParseFromArray(data, nSize))
		return BUILD_ERRORCODE(0, emME_PROTOCAL_PRASE);

	if (!ph.Hit.has_chairid())
		return BUILD_ERRORCODE(0, emME_HIT_CHAIRID);
	dh.m_nChairID = ph.Hit.chairid();

	if (!ph.Hit.has_weaponid())
		return  BUILD_ERRORCODE(0, emME_HIT_WEAPONID);
	dh.m_nWeaponId = ph.Hit.weaponid();
	
	return emME_OK;
}