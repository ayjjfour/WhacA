#pragma once

#include <time.h>

enum emLiveStatus {
	emLS_Death = -1,
	emLS_None = 0,
	emLS_Born = 1,
};

enum emKillType {
	emKT_None	= 0,
	emKT_Normal,
	emKT_Light,
	emKT_Fire,
	emKT_Water,
	emKT_Aerolite,
	emKT_King,
};

#define		NORMAL_RATE			1000

// ������Ϣ�ṹ
typedef struct _monster_info_s {
	// �������ʱ���õ�����
	int					m_nID;						// ����ID
	emLiveStatus		m_emLiveStatus;				// ���������־��ȡֵ��Χ��ö��emLiveStatus��
	time_t				m_nBronTime;				// �������ʱ��
	int					m_nCrazyRate;				// �񱩱��ʣ��Ŵ�1000����

	// �������ж�ȡ�����ԣ���������
	char				m_Name[64];					// ��������
	int					m_nType;					// ��������
	int					m_nHPMax;					// ��������hp
	int					m_nHPCur;					// ����ĵ�ǰhp
	int					m_nRateMin;					// �������ͱ���
	int					m_nRateMax;					// �������߱���
	int					m_nMissRate;				// ��������ָ���������� = ����ָ��/���˻�����
	
	// ���ﱻ��ɱ�󣬼��������
	bool				m_bIsDispear;				// �����Ƿ��Ѿ���ʧ(�������Ѿ��������)
	bool				m_bHasIncoming;				// �����Ƿ�������
	bool				m_bMissHit;					// �����Ƿ�������
	emKillType			m_emKillType;				// ����ɱ��ʽ
	int					m_nKillRate;				// ���ﱻ��ɱʱ�ı���
	long long			m_llMoney;					// ��ɱ����Ľ������
	long long			m_llTicket;					// ��ɱ�������Ʊ����
	long long			m_llWeaponCost;				// ��ɱ�������������

	_monster_info_s()
	{
		memset(this, 0, sizeof(_monster_info_s));
	}

	_monster_info_s& operator=(_monster_info_s& in)
	{
		memcpy(this, &in, sizeof(_monster_info_s));
		return *this;
	}
} monster_info_t;