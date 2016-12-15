#include "MonsterPool.h"
#include "GameData/GameConfig.h"
#include "MonsterManager/CreateInfo.h"

MonsterPool::MonsterPool()
{
	Release();
}

MonsterPool::~MonsterPool()
{
	Release();
}

void MonsterPool::Release(void)
{
	memset(&m_stInfo, 0, sizeof(monster_info_t));
	m_pAreaPool = NULL;

	Pool<Monster>::Release();
}

int MonsterPool::vir_Create(Monster* pMonster, void* in_pData, int& out_nID)
{
	// 判断是否有空闲的区域
	if (m_pAreaPool->IsPoolFull())
		return BUILD_ERRORCODE(0, emME_ARENA_FULL);

	// 创建怪物，设置怪物信息
	monster_info_t		info;
	memcpy(&info, &m_stInfo, sizeof(monster_info_t));
	vir_SetMonsterInfo(info, in_pData);
	pMonster->Reset();
	if (!pMonster->vir_Born(info))
		return BUILD_ERRORCODE(0, emME_OBJ_CREATE);

	// 生产区域
	Arena* pArena = nullptr;
	int res = m_pAreaPool->Create(NULL, pArena);
	if (res != emME_OK)
		return res;

	// 怪物与区域关联
	pMonster->SetArena(pArena);
	pArena->SetMonster(pMonster);

	// 返回怪物ID
	out_nID = info.m_nID;
	return emME_OK;
}

// 创建怪物时，设置怪物信息
void MonsterPool::vir_SetMonsterInfo(monster_info_t& out_info, void* in_pData)
{
	create_info_t		*pinfo = (create_info_t *)in_pData;

	out_info.m_nID = vir_CreateID();
	out_info.m_nCrazyRate = pinfo->nCrazyRate;		// 怪物狂暴属性
	if (out_info.m_nCrazyRate > NORMAL_RATE)			
		out_info.m_nHPMax = 1;
	out_info.m_nHPCur = out_info.m_nHPMax;
}

int MonsterPool::vir_CreateID()
{
	int	nID = BUILD_MONSTERID(m_stInfo.m_emType, m_nIDs);
	m_nIDs++;

	if (m_nIDs >= g_c_nMaxMonsterID)
		m_nIDs = 1;

	return nID;
}

void MonsterPool::vir_Recyle(Monster* pMonster)
{
	Arena* pArena = pMonster->RemoveArena();
	if (nullptr == pArena)
		return;

	pArena->RemoveMonster();

	m_pAreaPool->Recycle(pArena->GetID());
}

void MonsterPool::SetArenaPool(ArenaPool* pAPool)
{
	m_pAreaPool = pAPool;
}

ArenaPool* MonsterPool::GetArenaPool(void) const
{
	return m_pAreaPool;
}