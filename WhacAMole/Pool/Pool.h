#pragma once

#include "../Error/MoleError.h"
#include <map>
#include <list>

using namespace std;

template<class T>
class Pool
{
protected:
	Pool();
	virtual ~Pool();

protected:
	int				m_nIDs;					// 构造对象ID的递增值
	int				m_nMax;
	list<T*>		m_list_free;
	map<int, T*>	m_map_used;

public:
	void Release(void);
	int Create(void* in_pData, T*& pObj);
	bool Recycle(int nID);
	bool IsPoolFull(void);

protected:
	bool	_IsPoolFull(void);
	bool	_AddToList(T* pObj);

protected:
	// 具体化实例对象，返回改对象的ID
	virtual int vir_Create(T* pObj, void* in_pData, int& out_nID) = 0;
	virtual void vir_Recyle(T* pObj);

	// 默认的创建ID函数，派生类可以根据自己的需要，改写ID的生成规则
	virtual int	vir_CreateID(void);
};

template<class T>
Pool<T>::Pool()
{
	Release();
}

template<class T>
Pool<T>::~Pool()
{
	Release();
}

template<class T>
void Pool<T>::Release(void)
{
	m_nIDs = 1;
	m_nMax = 0;
	m_list_free.clear();
	m_map_used.clear();
}

template<class T>
int Pool<T>::Create(void* in_pData, T*& pObj)
{
	pObj = nullptr;

	if (m_list_free.empty())
		return BUILD_ERRORCODE(0, emME_OBJ_USEDOUT);

	pObj = m_list_free.front();
	m_list_free.pop_front();
	if (nullptr == pObj)
		return BUILD_ERRORCODE(0, emME_OBJ_NULL);

	int nID;
	int res = vir_Create(pObj, in_pData, nID);
	if (emME_OK != res)
	{
		// 创建失败，回收之前分配的资源
		m_list_free.push_back(pObj);
		return res;
	}

	m_map_used.insert(make_pair(nID, pObj));

	return emME_OK;
}

template<class T>
void Pool<T>::vir_Recyle(T* pObj)
{
	return;
}

template<class T>
bool Pool<T>::Recycle(int nID)
{
	map<int, T*>::iterator		it;
	it = m_map_used.find(nID);
	if (it == m_map_used.end())
		return false;
	T* pObj = (*it).second;

	vir_Recyle(pObj);
	m_map_used.erase(it);
	if (nullptr == pObj)
		return false;

	m_list_free.push_back(pObj);

	return true;
}

template<class T>
bool Pool<T>::IsPoolFull(void)
{
	return _IsPoolFull();
}

template<class T>
bool Pool<T>::_IsPoolFull(void)
{
	return m_list_free.empty();
}

template<class T>
bool Pool<T>::_AddToList(T* pObj)
{
	m_list_free.push_back(pObj);

	return true;
}

template<class T>
int	Pool<T>::vir_CreateID(void)
{
	int		nID = m_nIDs;

	m_nIDs++;
	if (m_nIDs == 0x7FFFFFFF)
		m_nIDs = 1;

	return nID;
}