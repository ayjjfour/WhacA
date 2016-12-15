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
	SY::PlayerHitIncoming syPlayerHitIncoming;			// ����ÿ�����������
	syPlayerHitIncoming.set_chairid(dh.m_nChairID);		// ��λ��

	for (dh.m_MD.Begin(); !dh.m_MD.IsEnd(); dh.m_MD.Next())
	{
		const monster_info_t& info = dh.m_MD.GetSecond();
		
		if (info.m_bHasPay)	// �ͻ�����֧�����õ����
		{
			// ��ʧ�Ĺ��ﷵ�����
			if (info.m_bIsDispear)
			{
				//-- �������˻�
				SY::MonsterIncoming* pMonsterIncoming = syPlayerHitIncoming.add_incominglist();
				pMonsterIncoming->set_monsterid(info.m_nID);
				pMonsterIncoming->set_killrate(-1);
				pMonsterIncoming->set_usermoneynum(0);
				pMonsterIncoming->set_userticketnum(0);
				pMonsterIncoming->set_weaponcostex((int)-dh.m_llWeaponCost);
			}
			else
			{
				// ���˻�û��������������Ҫ׷�ӿ۷�
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
				else if (info.m_bHasIncoming)	// ��������Ĺ��ﷵ����ң�ͬʱ׷�ӿ۷�
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
		{	// �ͻ���û�п۷�
			// ��������Ĺ��ﷵ����ң�����Ҫ׷�ӿ۷�
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

		// ����������������
		dh.m_llCost += info.m_llKillCost;
		dh.m_llTicket += info.m_llTicket;
		dh.m_llMoney += info.m_llMoney;

		//-- �����ҷ���Э��

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

//  ����ĳֻ���������
int IHitTask::vir_CalculateMonster(const SY::MonsterEx& pbMonster, emKillType emType, DataHit& dh)
{
	int					nID = pbMonster.monsterid();
	Monster*			monster = m_MM.FetchMonster(nID);
	monster_info_t		info;

	// ����������쳣�������Ѿ���ʧ�ˣ������Ѿ����ˣ�����û�б�������
	if (!_IsValidHit(monster, emType))
	{	// ���֧���˷���
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

	// ������ɱ���
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