#include "ITaskInterface.h"

int IHitTask::Protocal(pro_hit_t& ph, DataHit& dh)
{
	if (!_IsProtocalStatus())
		return emME_OK;

	return vir_Protocal(ph, dh);
}
int IHitTask::Calculate(pro_hit_t& ph, DataHit& dh)
{
	if (!_IsCalculateStatus())
		return emME_OK;

	return vir_Calculate(ph, dh);
}
int IHitTask::Statistic(pro_hit_t& ph, DataHit& dh)
{
	if (!_IsStatisticStatus())
		return emME_OK;

	return vir_Statistic(ph, dh);
}

int IHitTask::Reward(pro_hit_t& ph, DataHit& dh)
{
	if (!_IsRewardStatus())
		return emME_OK;

	return vir_Reward(ph, dh);
}

int IHitTask::vir_Reward(pro_hit_t& ph, DataHit& dh)
{
	SY::PlayerHitIncoming syPlayerHitIncoming;			// 计算每个怪物的收益
	syPlayerHitIncoming.set_chairid(dh.m_nChairID);		// 座位号

	for (dh.m_MD.Begin(); !dh.m_MD.IsEnd(); dh.m_MD.Next())
	{
		const monster_info_t& info = dh.m_MD.GetSecond();
		
		if (info.m_bHasPay)	// 客户端有支付费用的情况
		{
			// 消失的怪物返还金币
			if (info.m_bIsDispear)
			{
				//-- 处理金币退还
				SY::MonsterIncoming* pMonsterIncoming = syPlayerHitIncoming.add_incominglist();
				pMonsterIncoming->set_monsterid(info.m_nID);
				pMonsterIncoming->set_killrate(-1);
				pMonsterIncoming->set_usermoneynum(0);
				pMonsterIncoming->set_userticketnum(0);
				pMonsterIncoming->set_weaponcostex((int)-dh.m_llWeaponCost);
			}
			else
			{
				// 免伤或没有收益怪物，可能需要追加扣费
				if (info.m_bMissHit || !info.m_bHasIncoming)
				{
					if (info.m_llKillCost - dh.m_llWeaponCost != 0)
					{
						SY::MonsterIncoming* pMonsterIncoming = syPlayerHitIncoming.add_incominglist();
						pMonsterIncoming->set_monsterid(info.m_nID);
						pMonsterIncoming->set_killrate(-1);
						pMonsterIncoming->set_usermoneynum(0);
						pMonsterIncoming->set_userticketnum(0);
						pMonsterIncoming->set_weaponcostex((int)(info.m_llKillCost - dh.m_llWeaponCost));
					}
				}
				else if (info.m_bHasIncoming)	// 给有收益的怪物返还金币，同时追加扣费
				{
					SY::MonsterIncoming* pMonsterIncoming = syPlayerHitIncoming.add_incominglist();
					pMonsterIncoming->set_monsterid(info.m_nID);
					pMonsterIncoming->set_killrate(info.m_nKillRate);
					pMonsterIncoming->set_usermoneynum((int)info.m_llMoney);
					pMonsterIncoming->set_userticketnum((int)info.m_llTicket);
					pMonsterIncoming->set_weaponcostex((int)(info.m_llKillCost - dh.m_llWeaponCost));
				}
			}			
		}
		else
		{	// 客户端没有扣费
			// 给有收益的怪物返还金币，不需要追加扣费
			if (info.m_bHasIncoming)
			{
				SY::MonsterIncoming* pMonsterIncoming = syPlayerHitIncoming.add_incominglist();
				pMonsterIncoming->set_monsterid(info.m_nID);
				pMonsterIncoming->set_killrate(info.m_nKillRate);
				pMonsterIncoming->set_usermoneynum((int)info.m_llMoney);
				pMonsterIncoming->set_userticketnum((int)info.m_llTicket);
				pMonsterIncoming->set_weaponcostex(0);
			}
		}

		// 计算总消费与收益
		dh.m_llCost += info.m_llKillCost;
		dh.m_llTicket += info.m_llTicket;
		dh.m_llMoney += info.m_llMoney;

		//-- 构造金币返回协议

	}

	return emME_OK;
}

bool IHitTask::_IsProtocalStatus()
{
	if (emTS_Protocal != m_emStatus)
		return false;
	m_emStatus = emTS_Calculate;
	return true;
}

bool IHitTask::_IsCalculateStatus()
{
	if (emTS_Calculate != m_emStatus)
		return false;
	m_emStatus = emTS_Statistic;
	return true;
}

bool IHitTask::_IsStatisticStatus()
{
	if (emTS_Statistic != m_emStatus)
		return false;
	m_emStatus = emTS_Reward;
	return true;
}

bool IHitTask::_IsRewardStatus()
{
	if (emTS_Reward != m_emStatus)
		return false;
	m_emStatus = emTS_None;
	return true;
}

//  计算某只怪物的收益
int IHitTask::vir_CalculateMonster(const SY::MonsterEx& pbMonster, emKillType emType, DataHit& dh)
{
	int					nID = pbMonster.monsterid();
	Monster*			monster = m_MM.FetchMonster(nID);
	monster_info_t		info;

	// 怪物击打有异常（怪物已经消失了，怪物已经死了，怪物没有被打死）
	if (!_IsValidHit(monster, emType))
	{	// 玩家支付了费用
		if (pbMonster.haspay())
		{
			info.m_nID = nID;
			info.m_bIsDispear = true;
			info.m_bHasPay = pbMonster.haspay();
			info.m_llKillCost = 0;
			dh.m_MD.Insert(nID, info);
		}
		return -1;
	}

	// 正常击杀怪物，
	monster->CalculateIncoming(dh.m_llWeaponCost);
	monster->GetInfo(info);
	m_MM.RecycleMonster(nID);
	info.m_bHasPay = pbMonster.haspay();
	dh.m_MD.Insert(nID, info);

	return emME_OK;
}

bool IHitTask::_IsValidHit(Monster* monster, emKillType emType)
{
	if (nullptr == monster)
		return false;

	if (emME_OK != monster->BeHit(emType))
		false;

	if (!monster->IsDeath())
		return false;

	return true;
}