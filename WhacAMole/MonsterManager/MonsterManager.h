#pragma once

#include "Pool/HeadPool.h"
#include "CreateInfo.h"

#include <map>
#include <vector>
#include <list>

using namespace std;

// ���������
class MonsterManager
{
public:
	MonsterManager();
	~MonsterManager();

private:
	map<int, int>			m_mapType;				// ����ID���������͵�ӳ�� ID -> type

	// �������
	vector<int>				m_MoleSeq;
	HolePool				m_HolePool;				// ����Ѩ��
	MolePool				m_MolePersizPool;		// ��˹�����
	MolePool				m_MoleNursePool;		// ��ʿ�����
	MolePool				m_MoleFlyingPool;		// ���е����
	MolePool				m_MoleAdorablePool;		// ���ȵ����
	MolePool				m_MoleMinerPool;		// �󹤵����
	MolePool				m_MoleKingPool;			// ������
	
	// �����������
	vector<int>				m_OtherSeq;
	TSpiderPool				m_TSpiderPool;			// ֩��켣��
	TFlyingPool				m_TFlyingPool;			// ��Ӭ�켣��
	MTracerPool				m_SpiderPool;			// ֩���
	MTracerPool				m_FlyingPool;			// ��Ӭ��

	// ����������
private:
	unsigned int m_seed;	// �����������


//////////////////////////////////////////////////////////////////////////
// ��ʼ��
//////////////////////////////////////////////////////////////////////////
public:
	bool Initialize(void);
	void Release(void);

protected:
	// �ڲ��ӿ�
	bool _Initialize_MonsterSeq(void);
	bool _Initialize_ArenaPool(void);
	bool _initialize_MonsterPool(void);

	bool _initialize_ArenaPool(const arena_info_t& info, ArenaPool* pArenaPool);
	bool _initialize_MonsterPool(const monster_info_t& info, MonsterPool* pMonsterPool, ArenaPool* pArenaPool);
	bool _FetchMonsterInfo(MonsterType emType, monster_info_t& out_info);

//////////////////////////////////////////////////////////////////////////
// ��������
//////////////////////////////////////////////////////////////////////////
public:
	void CreateMonster(create_info_t& in_info, list<Monster*>& out_lMonster);

protected:
	// ����һ�ι���������ÿ����������һֻ��
	void _CreateOnce(create_info_t& in_info, list<Monster*>& out_lMonster);

	// ��һ������У��������һֻ����
	// �����б�
	//	in_info				[in] ��������ʱ����Ϣ�����Ƿ���ڼ��
	//	out_lMonster		[out] �������������б�
	//	seq					[in] �������У�������������������һ����
	void _CreateFromGroup(create_info_t& in_info, list<Monster*>& out_lMonster, vector<int>& seq);
	int _GetRandomMonsterType(const vector<int>& seq) const;
	int _CreateFromPool(int nType, create_info_t& in_info, Monster*& out_pMonster);

//////////////////////////////////////////////////////////////////////////
// ���չ������
//////////////////////////////////////////////////////////////////////////
public:
	void RecycleMonster(int nID);
	void RecycleMonster(vector<int>& vec_type);
	void RecycleMonster(list<int>& list_type);

protected:
	// ���չ���
	void _RecycleMonster(int nID);

//////////////////////////////////////////////////////////////////////////
// ��ȡ�������
//////////////////////////////////////////////////////////////////////////
public:
	Monster* FetchMonster(int nID);

protected:
	Monster* _FetchMonster(int nType, int nID);
};