#include "stdafx.h"
#include "EventManager.h"
#include "GameObject.h"

#include "Wall.h"
#include "Tile.h"
#include "Managers.h"

CEventManager::CEventManager()
{
}

CEventManager::~CEventManager()
{
}

void CEventManager::Update()
{
	// 타일과 벽에 대한 특수 상황 처리
	for (size_t i = 0; i < m_vecCreate.size(); ++i)
	{
		if (TYPE::TILE == m_vecCreate[i]->GetType())
		{
			int		_j = m_vecCreate[i]->GetPosition().x / TILECX;
			int		_i = m_vecCreate[i]->GetPosition().y / TILECY;

			int		iIndex = _i * TILEX + _j;

			CGameObject* pNewTileIndex = CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::TILE)[iIndex];

			CManagers::instance().Tile()->DestroyWall(pNewTileIndex->GetPosition());
			Safe_Delete(pNewTileIndex);
			CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::TILE)[iIndex] = m_vecCreate[i];
		}
	}
	m_vecCreate.clear();

	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		// 여기에서 삭제 해주고, GameScene에서는 벡터 원소만 날려 줌.
		if (TYPE::WALL == m_vecDead[i]->GetType())
		{
			CTile* pTile = new CTile;
			pTile->Initialize();
			pTile->SetPosition(m_vecDead[i]->GetPosition());
			pTile->SetTile(15, 0, 0, dynamic_cast<CWall*>(m_vecDead[i])->GetWallAround());
			m_vecCreate.push_back(pTile);
		}
		else if (TYPE::MONSTER == m_vecDead[i]->GetType())
		{
			CManagers::instance().Pool()->ReturnMonster(m_vecDead[i]);
		}
	}
	m_vecDead.clear();

	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventManager::CreateObject(CGameObject * _pObj, TYPE _eGroup)
{
	tagEvent evn = {};
	evn.eEvent = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	AddEvent(evn);
}

void CEventManager::DeleteObject(CGameObject * _pObj)
{
	tagEvent evn = {};
	evn.eEvent = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	AddEvent(evn);
}

void CEventManager::Execute(const tagEvent & _eve)
{
	switch (_eve.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		CGameObject* pNewObject = (CGameObject*)_eve.lParam;
		TYPE eType = (TYPE)_eve.wParam;

		if (eType == TYPE::MONSTER)
			CManagers::instance().Scene()->CurrentScene()->GetObjList(eType).push_back(pNewObject);
	}
		break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		CGameObject*	pDeadObject = (CGameObject*)_eve.lParam;
		pDeadObject->SetDead(true);
		m_vecDead.push_back(pDeadObject);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		//
		break;
	}
}
