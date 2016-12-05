#include "Manager/MonsterManager.h"
#include <stdio.h>
#include <list>

using namespace std;

int main(int argc, char*argv[])
{
	MonsterManager		man;

	man.Initialize();

	create_info_t		info;
	list<Monster*>		lMonster;
	monster_info_t		stinfo;

	info.nCount = 30;
	info.bIsCrazy = true;

	for (int i = 0; i < 2; i++)
	{
		info.nCount = 30 - i * 15;
		info.bIsCrazy = true;
		man.CreateMonster(info, lMonster);
		man.CreateMonster(info, lMonster);
		man.CreateMonster(info, lMonster);

		int		index = 0;
		list<Monster*>::iterator		it;
		for (it = lMonster.begin(); it != lMonster.end(); it++)
		{
			(*it)->GetInfo(stinfo);
			printf("[%02d]type = %d, id = 0x%X, name = %s\n", ++index, stinfo.m_nType, stinfo.m_nMonsterID, stinfo.m_Name);
			man.RecycleMonster(stinfo.m_nMonsterID);
		}

		lMonster.clear();
		printf("\n\n");
	}

	system("pause");

	return 0;
}