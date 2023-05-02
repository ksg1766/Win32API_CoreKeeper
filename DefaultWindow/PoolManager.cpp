#include "stdafx.h"
#include "PoolManager.h"
#include "Managers.h"
#include "Struct.h"
#include "Slime.h"
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

void CPoolManager::ReturnMonster(CGameObject * _cMonster)
{
	//_cMonster->SetDead(true);
	m_cMonsterPool->GetMonsterPool()->push_back(_cMonster);
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
		CGameObject* pSlime = new CSlime;
		dynamic_cast<CSlime*>(pSlime)->Initialize();
		m_MonsterList.push_back(pSlime);
	}
}

void CPoolManager::MonsterPool::CreateMonster()
{
	auto& findByState = [&](CGameObject* _iter)
	{
		if (_iter->IsDead())
			return _iter;
	};

	auto& iterMonster = find_if(m_MonsterList.begin(), m_MonsterList.end(), findByState);

	// Do Something

	(*iterMonster)->SetDead(false);

	vector<CGameObject*>& vecTile = CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::TILE);
	UINT iTileSize = vecTile.size();
	while (true)
	{
		UINT iIndex = rand() % iTileSize;
		if (TYPE::TILE == vecTile[iIndex]->GetType())
		{
			(*iterMonster)->SetPosition(vecTile[iIndex]->GetPosition());
			break;
		}
	}

	CManagers::instance().Event()->CreateObject(*iterMonster, TYPE::MONSTER);
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