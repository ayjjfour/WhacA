#pragma once

#include "../Arena/Arena.h"

#include "GameData/MonsterData.h"

// �������
class Monster
{
public:
	Monster();
	virtual ~Monster();

protected:
	Arena				*m_pArena;			// ��������
	monster_info_t		m_stInfo;			// �����ڲ�����

public:
	// д���麯�������ĳ�ֹ���������Ĵ�����ʽ���̳�ʵ��֮
	virtual bool vir_Born(monster_info_t& info);

public:
	bool		IsDeath(void) const;
	int			BeHit(void);
	void		Destory(void);
	void		Reset(void);
	void		SetID(int nID);
	int			GetID(void) const;
	void		GetInfo(monster_info_t& info) const;
	void		SetArena(Arena* pArena);
	Arena*		GetArena(void) const;
	Arena*		RemoveArena(void);

public:
	bool		CalculateIncoming(int nWeapon);

protected:
	// ���·���д���麯������������������㷨���̳�ʵ��֮
	virtual long long _vir_CalculateWeaponCost(void);		// ������������
	virtual bool _vir_CalculateMissHit(void);				// �����Ƿ�����
	virtual int _vir_CalculateKillRate(void);				// �����ɱ����
	virtual bool _vir_CalculateHasIncoming(void);			// �����Ƿ�������
	virtual long long _vir_CalculateMoney(void);			// ����������
	virtual long long _vir_CalculateTicket(void);			// ������Ʊ����
};