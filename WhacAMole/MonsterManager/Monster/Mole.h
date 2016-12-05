#pragma once

#include "Monster.h"
#include "../Arena/Hole.h"

// ������
class Mole : public Monster
{
public:
	Mole();
	~Mole();

private:
	Hole*			m_pHole;

public:
	bool	SetHole(Hole* pHole);
	Hole*	GetHole(void);
	Hole*	RemoveHole(void);
};