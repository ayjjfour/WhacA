#pragma once

#include "KingHit.h"
#include "Tools/Random/MT19937.h"

#define		IS_NOT_KING		-1
#define		IS_KING			0
#define		NOT_FOUND		1

KingHit::KingHit(MonsterManager& MM) : IHitTask(MM)
{
}

KingHit::~KingHit()
{
}

int KingHit::vir_Protocal(pro_hit_t& ph, DataHit& dh)
{
	// �Ƿ�����������
	if (!ph.Hit.has_kinghit())
	{
		m_emStatus = emTS_None;
		return emME_OK;
	}

	// �ж��Ƿ�����
	int res = _IsKing(ph.Hit.kinghit().king().monsterid());
	if (IS_NOT_KING == res)
	{
		m_emStatus = emTS_None;	// ���������Ĳ���
		return emME_OK;
	}

	m_emStatus = emTS_Calculate;

	return emME_OK;
}

int KingHit::vir_Calculate(pro_hit_t& ph, DataHit& dh)
{
	const SY::KingEx&		kingEx = ph.Hit.kinghit();
	int						list_size = kingEx.monster_list_size();
	
	// �ȼ������������������
	const SY::MonsterEx& monster = kingEx.king();
	int res = IHitTask::vir_CalculateMonster(monster, emKT_King, dh);
	if (res != emME_OK)	// �����Ƿ���������
	{
		m_emStatus = emTS_Reward;	// ����ͳ�ƣ�ֱ�ӵ�����
		return emME_OK;
	}
		
	// �ж������Ƿ�����
	if (_IsMissHit(monster.monsterid()))
		return emME_OK;

	// �����Ƿ񱩻�
	dh.m_bIsCriticalHit = _IsCriticalHit(list_size);
	if (!dh.m_bIsCriticalHit)
		return emME_OK;

	// ����б���������ÿ�����������
	for (int i = 0; i < list_size; i++)
	{
		const SY::MonsterEx&	monster = kingEx.monster_list(i);
		vir_CalculateMonster(monster, emKT_King, dh);
	}

	return emME_OK;
}

int KingHit::vir_Statistic(pro_hit_t& ph, DataHit& dh)
{
	return emME_OK;
}

int KingHit::vir_Reward(pro_hit_t& ph, DataHit& dh)
{
	IHitTask::vir_Reward(ph, dh);

	// ��������֮������Ϣ
	// dh.m_bIsCriticalHit

	return emME_OK;
}

int KingHit::vir_CalculateMonster(const SY::MonsterEx& pbMonster, emKillType emType, DataHit& dh)
{
	int					nID = pbMonster.monsterid();
	Monster*			monster = m_MM.FetchMonster(nID);
	monster_info_t		info;

	if (nullptr == monster)
		return emME_OK;

	// ������ɱ����
	monster->CalculateIncoming(dh.m_llWeaponCost);
	monster->GetInfo(info);
	m_MM.RecycleMonster(nID);

	info.m_bHasPay = false;
	info.m_emKillType = emType;
	dh.m_MD.Insert(nID, info);

	return emME_OK;
}

int KingHit::_IsKing(int nID)
{
	Monster* king = m_MM.FetchMonster(nID);
	if (nullptr == king)
		return NOT_FOUND;

	monster_info_t	info;
	king->GetInfo(info);
	if (info.m_emType == mtMoleKing)
		return IS_KING;

	return IS_NOT_KING;
}

bool KingHit::_IsMissHit(int nID)
{
	Monster* king = m_MM.FetchMonster(nID);
	if (nullptr == king)
		return true;

	monster_info_t	info;
	king->GetInfo(info);
	if (info.m_bMissHit)
		return true;

	return false;
}

bool KingHit::_IsCriticalHit(int size)
{
	if (size <= 0)
		return false;

	double dRate = -1;

	dRate = 10000.0 / size;

	if ((genrand_real2() * 10000) >= dRate)
		return false;

	return true;
}