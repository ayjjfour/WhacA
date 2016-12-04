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

public:
	virtual bool	vir_Initialize(const arena_info_t& info);
	void			Release();

protected:


protected:
	virtual bool	vir_Expend(int nCount);
	//virtual int		vir_CreateID(void);
};