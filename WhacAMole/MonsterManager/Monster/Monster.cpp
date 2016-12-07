#include "Monster.h"
#include "string.h"
#include "Tools/Random/Random.h"

Monster::Monster()
{
	m_stInfo.m_emLiveStatus = emLS_None;
}

Monster::~Monster()
{
	m_stInfo.m_emLiveStatus = emLS_Death;
}

bool Monster::vir_Born(monster_info_t& info)
{
	if (emLS_None != m_stInfo.m_emLiveStatus)
		return false;

	if (info.m_nHPCur <= 0)
		return false;

	memcpy(&m_stInfo, &info, sizeof(monster_info_t));

	m_stInfo.m_nBronTime = time(NULL);
	m_stInfo.m_emLiveStatus = emLS_Born;

	return true;
}

bool Monster::IsDeath() const
{
	return (m_stInfo.m_emLiveStatus != emLS_Born || 0 >= m_stInfo.m_nHPCur);
}

int	Monster::BeHit()
{
	// �ж��Ƿ��Ѿ�����
	if (0 >= m_stInfo.m_nHPCur || m_stInfo.m_emLiveStatus != emLS_Born)
		return -1;

	m_stInfo.m_nHPCur--;
	if (0 >= m_stInfo.m_nHPCur)
		m_stInfo.m_emLiveStatus = emLS_Death;

	return 0;
}

void Monster::Destory()
{
	memset(&m_stInfo, 0, sizeof(monster_info_t));
	m_stInfo.m_emLiveStatus = emLS_None;
}

void Monster::Reset()
{
	memset(&m_stInfo, 0, sizeof(monster_info_t));
	m_stInfo.m_emLiveStatus = emLS_None;
}

void Monster::SetID(int nID)
{
	m_stInfo.m_nMonsterID = nID;
}

int	Monster::GetID(void) const
{
	return m_stInfo.m_nMonsterID;
}

void Monster::GetInfo(monster_info_t& info) const
{
	memcpy(&info, &m_stInfo, sizeof(monster_info_t));
}

void Monster::SetArena(Arena* pArena)
{
	m_pArena = pArena;
}

Arena* Monster::GetArena(void) const
{
	return m_pArena;
}

Arena* Monster::RemoveArena(void)
{
	Arena* pArena = m_pArena;
	m_pArena = nullptr;

	return pArena;
}

// ��������
bool Monster::CalculateIncoming(int nWeapon)
{
	// �ж��Ƿ�����
	if (!IsDeath())
		return false;

	// ������������
	m_stInfo.m_llWeaponCost = _vir_CalculateWeaponCost(nWeapon);

	// ��������
	m_stInfo.m_bMissHit = _vir_CalculateMissHit();
	if (m_stInfo.m_bMissHit)
		return false;

	// �����ɱ����
	m_stInfo.m_nKillRate = _vir_CalculateKillRate();

	// �����Ƿ�������
	m_stInfo.m_bHasIncoming = _vir_CalculateHasIncoming();
	if (!m_stInfo.m_bHasIncoming)
		return false;
	
	// ����������
	m_stInfo.m_llMoney = _vir_CalculateMoney();

	// ������Ʊ����
	m_stInfo.m_llTicket = _vir_CalculateTicket();

	return true;
}

// ������������
long long Monster::_vir_CalculateWeaponCost(int nWeapon)
{
	return (long long)(nWeapon * ((float)m_stInfo.m_nCrazyRate / NORMAL_RATE));
}

// �����Ƿ�����
bool Monster::_vir_CalculateMissHit(void)
{
	return MRandom::Prob(m_stInfo.m_nMissRate, PrecisionNumber);
}

// �����ɱ����
int Monster::_vir_CalculateKillRate(void)
{
	return MRandom::Random(m_stInfo.m_nRateMin, m_stInfo.m_nRateMax + 1);
}

// �����Ƿ�������
bool Monster::_vir_CalculateHasIncoming(void)
{
	return MRandom::Prob(1, m_stInfo.m_nKillRate);
}

// ����������
long long Monster::_vir_CalculateMoney(void)
{
	return m_stInfo.m_llWeaponCost * m_stInfo.m_nKillRate;
}

// ������Ʊ����
long long Monster::_vir_CalculateTicket(void)
{
	return 0;
}