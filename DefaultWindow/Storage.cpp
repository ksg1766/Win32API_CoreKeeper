#include "stdafx.h"
#include "Storage.h"


CStorage::CStorage()
{
}


CStorage::~CStorage()
{
}

void CStorage::Initialize(CGameObject * _pHost)
{
	m_pHost = _pHost;
}

void CStorage::AddObject(CGameObject * _pObject)
{
	m_vecStorage.push_back(_pObject);
}

void CStorage::SubObject(UINT _iIndex)
{
	/*vector<CGameObject*>::iterator iter = 
	m_vecStorage.erase(m_vecStorage[_iIndex]);*/
}
