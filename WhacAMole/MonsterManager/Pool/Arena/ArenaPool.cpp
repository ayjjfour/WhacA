#include "ArenaPool.h"
#include "GameData/GameConfig.h"
#include "MonsterManager/CreateInfo.h"

ArenaPool::ArenaPool()
{
}

ArenaPool::~ArenaPool()
{
}

void ArenaPool::Release()
{
	memset(&m_stInfo, 0, sizeof(arena_info_t));
	Pool<Arena>::Release();
}

int ArenaPool::vir_Create(Arena* pArena, void* in_pData, int& out_nID)
{
	arena_info_t		info;
	vir_SetArenaInfo(info, in_pData);

	// 创建区域，设置区域数据
	if (!pArena->vir_Build(info))
		return BUILD_ERRORCODE(0, emME_ARENA_CREATE);

	out_nID = pArena->GetID();

	return emME_OK;
}

void ArenaPool::vir_SetArenaInfo(arena_info_t& info, void* in_pData)
{
	return;
}