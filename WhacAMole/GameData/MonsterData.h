#pragma once

#include <time.h>

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