#pragma once

#include "../Arena/Arena.h"
#include <time.h>
#include <string.h>

enum emLiveStatus {
	emLS_Death = -1,
	emLS_None = 0,
	emLS_Born = 1,
};

// ������Ϣ�ṹ
typedef struct _monster_info_s {
	int					m_nMonsterID;				// ����ID
	emLiveStatus		m_emLiveStatus;				// ���������־��ȡֵ��Χ��ö��emLiveStatus��
	time_t				m_nBronTime;				// �������ʱ��
	char				m_Name[64];					// ��������
	int					m_nType;					// ��������
	int					m_nHPMax;					// ��������hp
	int					m_nHPCur;					// ����ĵ�ǰhp
	int					m_nRateMin;					// �������ͱ���
	int					m_nRateMax;					// �������߱���
	int					m_nMissRate;				// �������ˣ������� = MissRate/������
	int					m_nKillRate;				// ���ﱻ��ɱʱ�ı���
	bool				m_bHasIncoming;				// �����Ƿ�������
	bool				m_bCrazy;					// �Ƿ��

	_monster_info_s()
	{
		memset(this, 0, sizeof(_monster_info_s));
	}
} monster_info_t;

// �������
class Monster
{
protected:
	Monster();
	virtual ~Monster();

protected:
	Arena				*m_pArena;			// ��������
	monster_info_t		m_stInfo;			// �����ڲ�����

public:
	bool		vir_Born(monster_info_t& info);

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
};