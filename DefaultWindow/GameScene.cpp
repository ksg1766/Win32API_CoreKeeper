#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
#include "Managers.h"
#include "Tile.h"
#include "Wall.h"
#include "Ray.h"
#include "Collider.h"
#include "Glurch.h"
#include "HiveMother.h"
#include "MazeMerchant.h"
#include "PickAxe.h"
#include "UI.h"

#include "Core.h"
#include "Slime.h"
#include "Statue_Glurch.h"
#include "Statue_HiveMother.h"

#include "Trap.h"
//float g_fSound = 1.f;

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
	Release();
}

void CGameScene::Initialize(void)
{
	CManagers::instance().Collision()->Reset();

	CManagers::instance().Tile()->LoadTile();
	vector<CGameObject*>& vecTile = CManagers::instance().Tile()->GetTile();

	for (auto& iter : vecTile)
	{
		m_vecObjList[(UINT)TYPE::TILE].push_back(iter);
	}

	CGameObject* pPlayer = new CPlayer;
	pPlayer->Initialize();
	m_vecObjList[(UINT)TYPE::PLAYER].push_back(pPlayer);

	//CItem* _pPickAxe = new CPickAxe;
	//_pPickAxe->SetOwner(static_cast<CPlayer*>(pPlayer)); // Initialize보다 먼저해줘야함.
	//_pPickAxe->Initialize();
	CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).push_back(static_cast<CPlayer*>(pPlayer)->GetQuickSlot()[0]);
	//static_cast<CPlayer*>(pPlayer)->GetQuickSlot()[0] = _pPickAxe;
	//static_cast<CPlayer*>(pPlayer)->GetQuickSlotCount()[0] += 1;

	//TestMap1
	CGameObject* pGlurch = new CGlurch;
	pGlurch->Initialize();
	m_vecObjList[(UINT)TYPE::BOSS].push_back(pGlurch);

	for (int i = 0; i < 20; ++i)
		CManagers::instance().Pool()->CreateMonster();

	CGameObject* pMazeMerchant = new CMazeMerchant;
	pMazeMerchant->Initialize();
	m_vecObjList[(UINT)TYPE::PLAYER].push_back(pMazeMerchant);

	CGameObject* pMazeTrap = new CTrap;
	pMazeTrap->Initialize();
	pMazeTrap->SetPosition(Vector2(40.5f * TILECX, 44.5f * TILECY));
	m_vecObjList[(UINT)TYPE::ITEM].push_back(pMazeTrap);

	//TestMap2
	CGameObject* pHiveMother = new CHiveMother;
	pHiveMother->Initialize();
	m_vecObjList[(UINT)TYPE::BOSS].push_back(pHiveMother);

	m_IsHiveMotherDead = false;
	m_IsGlurchDead = false;
	//static_cast<CSlime*>(pMazeSlime)->Set();

	//MainMap
	CGameObject* pCore = new CCore;
	pCore->Initialize();
	CGameObject* pStatueGlurch = new CStatue_Glurch;
	pStatueGlurch->Initialize();
	CGameObject* pStatueHiveMother = new CStatue_HiveMother;
	pStatueHiveMother->Initialize();


	m_vecObjList[(UINT)TYPE::TILE].push_back(pCore);
	m_vecObjList[(UINT)TYPE::TILE].push_back(pStatueGlurch);
	m_vecObjList[(UINT)TYPE::TILE].push_back(pStatueHiveMother);


	CManagers::instance().UI()->InitializeSceneUI();

	CManagers::instance().Collision()->CheckGroup(TYPE::PLAYER, TYPE::MONSTER);
	CManagers::instance().Collision()->CheckGroup(TYPE::PLAYER, TYPE::BOSS);
	CManagers::instance().Collision()->CheckGroup(TYPE::PLAYER, TYPE::TILE);
	CManagers::instance().Collision()->CheckGroup(TYPE::PLAYER, TYPE::ITEM);
	CManagers::instance().Collision()->CheckGroup(TYPE::RAY, TYPE::TILE);
	CManagers::instance().Collision()->CheckGroup(TYPE::BOSS, TYPE::TILE);
	CManagers::instance().Collision()->CheckGroup(TYPE::BOSS, TYPE::ITEM);
	CManagers::instance().Collision()->CheckGroup(TYPE::MONSTER, TYPE::ITEM);
	CManagers::instance().Collision()->CheckGroup(TYPE::MONSTER, TYPE::TILE);
	CManagers::instance().Collision()->CheckGroup(TYPE::PLAYER, TYPE::PLAYER);

	CManagers::instance().Sound()->PlayBGM(L"Base_Theme_v4.wav", CManagers::instance().Sound()->GetVolume());
}

void CGameScene::FixedUpdate(void)
{
}

void CGameScene::Update(void)
{
	// 다른 오브젝트 삭제는 나중에 처리... // 여기도 함수로 옮길 것..
	srand((unsigned)time(NULL));
	for (int i = 0; i < (int)TYPE::TILE; ++i)
	{
		for (auto& iter = m_vecObjList[i].begin(); iter != m_vecObjList[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Update();
				++iter;
			}
			else if ((*iter)->IsDead())
			{
				iter = m_vecObjList[i].erase(iter);
			}
		}
	}

	/*if (!(m_pMazeMerchant)->IsDead())
	{
		m_pMazeMerchant->Update();
	}*/

	for (auto& iter = m_vecObjList[(UINT)TYPE::EFFECT].begin(); iter != m_vecObjList[(UINT)TYPE::EFFECT].end();)
	{
		if (!(*iter)->IsDead())
		{
		//	(*iter)->Update();
			++iter;
		}
		else
		{
			iter = m_vecObjList[(UINT)TYPE::EFFECT].erase(iter);
		}
	}

	for (auto& iter = m_vecObjList[(UINT)TYPE::UI].begin(); iter != m_vecObjList[(UINT)TYPE::UI].end();)
	{
		if (!(*iter)->IsDead())
		{
			(*iter)->Update();
			++iter;
		}
		else
		{
			iter = m_vecObjList[(UINT)TYPE::UI].erase(iter);
		}
	}
}

void CGameScene::LateUpdate(void)
{
	Vector2 vPlayerPosition = m_vecObjList[(UINT)TYPE::PLAYER].front()->GetPosition();

	/*m_pMazeMerchant->LateUpdate();
	RENDERID eMazeMerchID = m_pMazeMerchant->GetRenderID();
	m_RenderSort[(UINT)eMazeMerchID].push_back(m_pMazeMerchant);*/

	for (int i = 0; i < (UINT)TYPE::END; ++i)
	{
		if (i == (UINT)TYPE::TILE)
		{
			for (auto& iter : m_vecObjList[i])
			{

				if (abs(vPlayerPosition.x - iter->GetPosition().x) < 500
					&& abs(vPlayerPosition.y - iter->GetPosition().y) < 400)
				{
					iter->LateUpdate();
					RENDERID eID = iter->GetRenderID();
					m_RenderSort[(UINT)eID].push_back(iter);
				}
			}
		}

		else {
			for (auto& iter : m_vecObjList[i])
			{
				iter->LateUpdate();

				if (abs(vPlayerPosition.x - iter->GetPosition().x) < 500
					&& abs(vPlayerPosition.y - iter->GetPosition().y) < 400)
				{
					RENDERID eID = iter->GetRenderID();
					m_RenderSort[(UINT)eID].push_back(iter);
				}
			}
		}
	}

	for (auto& iter : m_vecObjList[(UINT)TYPE::EFFECT])
	{
		iter->LateUpdate();
		if (abs(vPlayerPosition.x - iter->GetPosition().x) < 500
			&& abs(vPlayerPosition.y - iter->GetPosition().y) < 400)
		{
			m_RenderSort[(UINT)RENDERID::EFFECT].push_back(iter);
		}
	}

	for (auto& iter : m_vecObjList[(UINT)TYPE::UI])
	{
		iter->LateUpdate();
		{
			m_RenderSort[(UINT)RENDERID::UI].push_back(iter);
		}
	}
	// 나중에 꼭 for문 하나로 합칠 것.... END가 중간에 껴 있어갖고......
	CManagers::instance().Collision()->LateUpdate();	// 나중에 얘네 MainGame으로 옮길 것
}

void CGameScene::Render(HDC m_DC)
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	CManagers::instance().Scroll()->ScrollShaking();

	for (size_t i = 0; i < (UINT)RENDERID::UI; ++i)
	{
		sort(m_RenderSort[i].begin(), m_RenderSort[i].end(), [&](CGameObject* pDest, CGameObject* pSrc)->bool
		{
			if (pDest->GetCollider())
			{
				if (pSrc->GetCollider())
					return (pDest->GetCollider()->GetPosition().y + pDest->GetCollider()->GetScale().y / 2.f) < (pSrc->GetCollider()->GetPosition().y + pSrc->GetCollider()->GetScale().y / 2.f);
				else
					return (pDest->GetCollider()->GetPosition().y + pDest->GetCollider()->GetScale().y / 2.f) < (pSrc->GetPosition().y + pSrc->GetScale().y / 2.f);
			}
			else
			{
				if (pSrc->GetCollider())
					return (pDest->GetPosition().y + pDest->GetScale().y / 2.f) < (pSrc->GetCollider()->GetPosition().y + pSrc->GetCollider()->GetScale().y / 2.f);
				else
					return (pDest->GetPosition().y + pDest->GetScale().y / 2.f) < (pSrc->GetPosition().y + pSrc->GetScale().y / 2.f);
			}
		});

		for (auto& iter : m_RenderSort[i])
		{
			if (!iter->IsDead())
				iter->Render(m_DC);
		}

		m_RenderSort[i].clear();
	}

	sort(m_RenderSort[(UINT)RENDERID::UI].begin(), m_RenderSort[(UINT)RENDERID::UI].end(), [&](CGameObject* pDest, CGameObject* pSrc)
	{
		return (static_cast<CUI*>(pDest)->GetLayer() < static_cast<CUI*>(pSrc)->GetLayer());
	});

	for (auto& iter : m_RenderSort[(UINT)RENDERID::UI])
		if (!iter->IsDead())
		{
			iter->Render(m_DC);
		}

	m_RenderSort[(UINT)RENDERID::UI].clear();

	//int	iCullX = abs((int)CManagers::instance().Scroll()->Get_ScrollX() / TILECX);
	//int	iCullY = abs((int)CManagers::instance().Scroll()->Get_ScrollY() / TILECY);
	//
	//int	iMaxX = iCullX + WINCX / TILECX + 2;
	//int	iMaxY = iCullY + WINCY / TILECY + 2;
	//
	//for (int i = iCullY; i < iMaxY; ++i)
	//{
	//	for (int j = iCullX; j < iMaxX; ++j)
	//	{
	//		int	iIndex = i * TILEX + j;
	//
	//		if (0 > iIndex || m_vecObjList[(UINT)TYPE::TILE].size() <= (size_t)iIndex)
	//			continue;
	//
	//		if (!m_vecObjList[(UINT)TYPE::TILE][iIndex]->IsDead())
	//		{
	//			m_vecObjList[(UINT)TYPE::TILE][iIndex]->Render(m_DC);
	//		}
	//		/*else
	//		{
	//			
	//		}*/
	//	}
	//}
	//
	//for (int i = 2; i < (int)TYPE::TILE; ++i)
	//{
	//	for (auto& iter : m_vecObjList[i])
	//		if (!iter->IsDead())
	//		{
	//			iter->Render(m_DC);
	//		}
	//}
	//
	//m_vecObjList[(UINT)TYPE::PLAYER].front()->Render(m_DC);
	//for (int i = 0; i < m_vecObjList[(UINT)TYPE::RAY].size(); ++i)
	//{
	//	m_vecObjList[(UINT)TYPE::RAY][i]->Render(m_DC);
	//}
}

void CGameScene::Release()
{
	__super::Release();
}