#pragma once

#include "../../Arena/Hole.h"
#include "ArenaPool.h"
#include <list>
#include <map>

using namespace std;

class HolePool : public ArenaPool
{
public:
	HolePool();
	~HolePool();

protected:
	Hole*		m_pHoles;

public:
	virtual bool	vir_Initialize(const arena_info_t& info);
	void			Release();
};