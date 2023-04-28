#include "stdafx.h"
#include "PoolManager.h"
#include "Managers.h"
#include "Struct.h"
#include "Monster.h"
#include "Enum.h"


CPoolManager::CPoolManager()
{
}

void CPoolManager::Initialize()
{
	m_cMonsterPool = new MonsterPool;
	m_cMonsterPool->Initialize();
}

CPoolManager::~CPoolManager()
{
	Release();
}

void CPoolManager::Return_Monster(CGameObject * _cMonster)
{
	_cMonster->SetDead(true);
	m_cMonsterPool->Get_MonsterPool()->push_back(_cMonster);
}

void CPoolManager::Release()
{
	m_cMonsterPool->Release();
	Safe_Delete(m_cMonsterPool);
}

CPoolManager::MonsterPool::~MonsterPool()
{
	Release();
}

void CPoolManager::MonsterPool::Initialize()
{
	for (int i = 0; i < iMaxMonsterPool; ++i)
	{
		CGameObject* _cMonster = new CMonster;
		dynamic_cast<CMonster*>(_cMonster)->Initialize();
		m_MonsterList.push_back(_cMonster);
	}
}

void CPoolManager::MonsterPool::Create_Monster(CGameObject* _pPlayer)
{
	auto& findByState = [&](CGameObject* _iter)
	{
		if (_iter->IsDead())
			return _iter;
	};

	auto& iterMonster = find_if(m_MonsterList.begin(), m_MonsterList.end(), findByState);

	// Do Something

	(*iterMonster)->SetDead(false);

	CManagers::instance().Scene()->Get_Current_Scene()->GetObjList(TYPE::MONSTER).push_back(*iterMonster);
	m_MonsterList.erase(iterMonster);
}

void CPoolManager::MonsterPool::Release()
{
	if (!(m_MonsterList.empty()))
		for (auto& iter : m_MonsterList)
		{
			Safe_Delete(iter);
		}

	m_MonsterList.clear();
}