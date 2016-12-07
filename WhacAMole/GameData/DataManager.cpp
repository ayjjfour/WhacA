#include "DataManager.h"
#include "Error/MoleError.h"

MonsterData::MonsterData()
{
	Release();
}

MonsterData::~MonsterData()
{
	Release();
}

void MonsterData::Release(void)
{
	m_map_monster.clear();
}

int MonsterData::Insert(int nID, const monster_info_t& monster)
{
	pair<map<int, monster_info_t>::iterator, bool>	ret;

	ret = m_map_monster.insert(make_pair(nID, monster));

	if (!ret.second)
		return -1;

	return emME_OK;
}

int MonsterData::GetCount(void) const
{
	return (int)m_map_monster.size();
}

void MonsterData::Begin(void)
{
	m_it_monster = m_map_monster.begin();
}

bool MonsterData::IsEnd(void)
{
	return (m_it_monster == m_map_monster.end());
}

void MonsterData::Next(void)
{
	m_it_monster++;
}

int MonsterData::GetFirst(void)
{
	return (*m_it_monster).first;
}

const monster_info_t& MonsterData::GetSecond(void)
{
	return (*m_it_monster).second;
}