#pragma once

#include "../../Arena/TSpider.h"
#include "ArenaPool.h"
#include <list>
#include <map>

using namespace std;

class TSpiderPool : public ArenaPool
{
public:
	TSpiderPool();
	~TSpiderPool();

public:
	virtual bool	vir_Initialize(const arena_info_t& info);
	void			Release();

protected:
	virtual bool	vir_Expend(int nCount);
};