#include "Arena.h"

Arena::Arena()
{
	memset(&m_stInfo, 0, sizeof(arena_info_t));
	m_pMonster = nullptr;
}

Arena::~Arena()
{
	memset(&m_stInfo, 0, sizeof(arena_info_t));
	m_pMonster = nullptr;
}

bool Arena::vir_Build(arena_info_t& info)
{
	// 目前什么事情都不需要做，派生类自己去实现
	return true;
}

void Arena::SetID(int nID)
{
	m_stInfo.m_nID = nID;
}

int Arena::GetID()
{
	return m_stInfo.m_nID;
}

void Arena::SetType(int nType)
{
	m_stInfo.m_nType = nType;
}

int Arena::GetType()
{
	return m_stInfo.m_nType;
}

void Arena::SetMonster(Monster* pMonster)
{
	m_pMonster = pMonster;
}

Monster* Arena::RemoveMonster()
{
	Monster*	pMonster = m_pMonster;

	m_pMonster = nullptr;

	return pMonster;
}