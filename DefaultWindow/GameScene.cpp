#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
#include "Managers.h"
#include "Tile.h"
#include "Wall.h"
#include "Ray.h"
#include "Collider.h"

#include "Item.h"

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
	Release();
}

void CGameScene::Initialize(void)
{
	CGameObject* pPlayer = new CPlayer;
	pPlayer->Initialize();

	m_vecObjList[(int)TYPE::PLAYER].push_back(pPlayer);

	CManagers::instance().Tile()->LoadTile();
	vector<CGameObject*>& vecTile = CManagers::instance().Tile()->GetTile();

	for (auto& iter : vecTile)
	{
		m_vecObjList[(UINT)TYPE::TILE].push_back(iter);
	}

	CManagers::instance().Collision()->CheckGroup(TYPE::PLAYER, TYPE::MONSTER);
	CManagers::instance().Collision()->CheckGroup(TYPE::PLAYER, TYPE::BOSS);
	CManagers::instance().Collision()->CheckGroup(TYPE::PLAYER, TYPE::TILE);
	CManagers::instance().Collision()->CheckGroup(TYPE::RAY, TYPE::TILE);
	CManagers::instance().Collision()->CheckGroup(TYPE::MONSTER, TYPE::BOSS);
	CManagers::instance().Collision()->CheckGroup(TYPE::ITEM, TYPE::MONSTER);
	CManagers::instance().Collision()->CheckGroup(TYPE::ITEM, TYPE::BOSS);
	CManagers::instance().Collision()->CheckGroup(TYPE::ITEM, TYPE::TILE);
}

void CGameScene::FixedUpdate(void)
{
}

void CGameScene::Update(void)
{
	//for (auto& iter = m_vecObjList[(UINT)TYPE::TILE].begin(); iter != m_vecObjList[(UINT)TYPE::TILE].end();)
	//{
	//	if ((*iter)->IsDead())
	//	{
	//		CWall* pIter = dynamic_cast<CWall*>(*iter);
	//		CTile* pTile = new CTile;
	//		pTile->Initialize();
	//		pTile->SetPosition(pIter->GetPosition());
	//		
	//		CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_vecObjList[(UINT)TYPE::PLAYER].front());
	//
	//		if (pIter->GetCollider() == pPlayer->GetWallTarget())
	//		{
	//			//pIter->GetCollider()->OnCollisionExit(pPlayer->GetCollider());
	//			//pPlayer->GetCollider()->OnCollisionExit(pIter->GetCollider());
	//			pPlayer->GetRay()->GetCollider()->OnCollisionExit(pIter->GetCollider());
	//		}
	//		
	//		CManagers::instance().Tile()->DestroyWall(pIter->GetPosition());
	//
	//		pTile->SetTile(15, 0, 0, pIter->GetWallAround());
	//		Safe_Delete(pIter);
	//		*iter = pTile;
	//		++iter;
	//	}
	//	else
	//		++iter;
	//}
	// 다른 오브젝트 삭제는 나중에 처리... // 여기도 함수로 옮길 것..

	for (int i = 0; i < (int)TYPE::END; ++i)
	{
		for (auto& iter : m_vecObjList[i])
		{
			if (!iter->IsDead())
			{
				iter->Update();
			}
		}
	}
}

void CGameScene::LateUpdate(void)
{
	for (int i = 0; i < (int)TYPE::END; ++i)
	{
		for (auto& iter : m_vecObjList[i])
		{
			iter->LateUpdate();
		}
	}
	CManagers::instance().Collision()->LateUpdate();	// 나중에 얘네 MainGame으로 옮길 것

}

void CGameScene::Render(HDC m_DC)
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);

	int	iCullX = abs((int)CManagers::instance().Scroll()->Get_ScrollX() / TILECX);
	int	iCullY = abs((int)CManagers::instance().Scroll()->Get_ScrollY() / TILECY);

	int	iMaxX = iCullX + WINCX / TILECX + 2;
	int	iMaxY = iCullY + WINCY / TILECY + 2;

	for (int i = iCullY; i < iMaxY; ++i)
	{
		for (int j = iCullX; j < iMaxX; ++j)
		{
			int	iIndex = i * TILEX + j;

			if (0 > iIndex || m_vecObjList[(UINT)TYPE::TILE].size() <= (size_t)iIndex)
				continue;

			if (!m_vecObjList[(UINT)TYPE::TILE][iIndex]->IsDead())
			{
				m_vecObjList[(UINT)TYPE::TILE][iIndex]->Render(m_DC);
			}
			else
			{
				
			}
		}
	}

	for (int i = 2; i < (int)TYPE::TILE; ++i)
	{
		for (auto& iter : m_vecObjList[i])
			if (!iter->IsDead())
			{
				iter->Render(m_DC);
			}
	}


	m_vecObjList[(UINT)TYPE::PLAYER].front()->Render(m_DC);
	for (int i = 0; i < m_vecObjList[(UINT)TYPE::RAY].size(); ++i)
	{
		m_vecObjList[(UINT)TYPE::RAY][i]->Render(m_DC);
	}
}

void CGameScene::Release()
{
	__super::Release();
}