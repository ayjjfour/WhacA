#include "Monster.h"
#include "string.h"

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
	// 判断是否已经死了
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