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

protected:
	TSpider*		m_pTSpiders;

public:
	virtual bool	vir_Initialize(const arena_info_t& info);
	void			Release();
};