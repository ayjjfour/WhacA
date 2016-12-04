#pragma once

#include "../../Arena/TFlying.h"
#include "ArenaPool.h"
#include <list>
#include <map>

using namespace std;

class TFlyingPool : public ArenaPool
{
public:
	TFlyingPool();
	~TFlyingPool();

protected:
	TFlying*		m_pTFlyings;

public:
	virtual bool	vir_Initialize(const arena_info_t& info);
	void			Release();
};