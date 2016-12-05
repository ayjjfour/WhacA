#include "Mole.h"

Mole::Mole()
{
	m_pHole = nullptr;
}

Mole::~Mole()
{
	m_pHole = nullptr;
}

bool Mole::SetHole(Hole* pHole)
{
	if (nullptr != m_pHole)
		return false;

	m_pHole = pHole;
	return true;
}

Hole* Mole::GetHole()
{
	return m_pHole;
}

Hole* Mole::RemoveHole()
{
	Hole* pHole = m_pHole;
	m_pHole = nullptr;

	return pHole;
}