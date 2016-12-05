#pragma once

#include "../../Arena/Arena.h"
#include "../../../Pool/Pool.h"
#include <list>
#include <map>

using namespace std;

class ArenaPool : public Pool<Arena>
{
public:
	ArenaPool();
	~ArenaPool();

protected:
	arena_info_t		m_stInfo;

public:
	void Release();

public:
	virtual bool vir_Initialize(const arena_info_t& info) = 0;
	virtual int vir_Create(Arena* pArena, void* in_pData, int& out_nID);
	virtual void vir_SetArenaInfo(arena_info_t& info, void* in_pData);
};