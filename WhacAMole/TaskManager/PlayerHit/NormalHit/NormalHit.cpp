#pragma once

#include "Error/MoleError.h"
#include "NormalHit.h"

NormalHit::NormalHit(MonsterManager& MM) : IHitTask(MM)
{

}

NormalHit::~NormalHit()
{

}

// У��Э��
int NormalHit::Protocal(pro_hit_t& ph, DataHit& dh)
{
	if (!ph.Hit.has_normalhit())
		return -3;

	return emME_OK;
}

// ��������
int NormalHit::Calculate(pro_hit_t& ph, DataHit& dh)
{
	int				nID = ph.Hit.normalhit().monsterid();
	monster_info_t	info;

	// ��ȡ����
	Monster* monster = m_MM.FetchMonster(nID);
	if (nullptr == monster)
	{
		// û���ҵ�������ǿͻ����Ѿ��۷���
		if (ph.Hit.normalhit().haspay())
		{
			info.m_nID			= nID;
			info.m_bIsDispear	= true;
			info.m_llWeaponCost = dh.m_nWeaponCost;
			dh.m_obj_normal.Insert(nID, info);
		}
		return -4;
	}

	if (emME_OK != monster->BeHit(emKT_Normal))
		return -5;

	if (!monster->IsDeath())
		return -6;

	monster->CalculateIncoming(dh.m_nWeaponCost);

	monster->GetInfo(info);
	m_MM.RecycleMonster(nID);

	dh.m_obj_normal.Insert(nID, info);
	
	return emME_OK;
}

// ͳ������
int NormalHit::Statistic(pro_hit_t& ph, DataHit& dh)
{
	for (dh.m_obj_normal.Begin(); !dh.m_obj_normal.IsEnd(); dh.m_obj_normal.Next())
	{
		const monster_info_t& info = dh.m_obj_normal.GetSecond();
		// ��ʧ�Ĺ�����Բ���
		if (info.m_bIsDispear)
			continue;

		if (info.m_bMissHit)	// ͳ������
		{ }

		// if (info.m_nType)	// ͳ�ƹ�������
	}

	return emME_OK;
}

// ��������
int NormalHit::Reward(pro_hit_t& ph, DataHit& dh)
{
	long long		llWeaponCost = 0;
	long long		llMoneyGain = 0;

	for (dh.m_obj_normal.Begin(); !dh.m_obj_normal.IsEnd(); dh.m_obj_normal.Next())
	{
		const monster_info_t& info = dh.m_obj_normal.GetSecond();
		// ��ʧ�Ĺ��ﷵ�����
		if (info.m_bIsDispear)
		{
			//-- �������˻�
			continue;
		}

		// ��������������
		llWeaponCost += info.m_llWeaponCost;
		llMoneyGain += info.m_llMoney;
			
		//-- �����ҷ���Э��

	}

	return emME_OK;
}