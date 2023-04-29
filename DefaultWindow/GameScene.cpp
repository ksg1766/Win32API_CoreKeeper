#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
#include "Managers.h"

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
		if (TYPE::TILE == iter->GetType())
			m_vecObjList[(UINT)TYPE::TILE].push_back(iter);
		if (TYPE::WALL == iter->GetType())
			m_vecObjList[(UINT)TYPE::WALL].push_back(iter);
	}
}

void CGameScene::FixedUpdate(void)
{
}

void CGameScene::Update(void)
{
	for (int i = 0; i < (int)TYPE::END; ++i)
	{
		for (auto& iter : m_vecObjList[i])
			iter->Update();
	}
}

void CGameScene::LateUpdate(void)
{
	for (int i = 0; i < (int)TYPE::END; ++i)
	{
		for (auto& iter : m_vecObjList[i])
			iter->LateUpdate();
	}
}

void CGameScene::Render(HDC m_DC)
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	for (int i = 1; i < (int)TYPE::END; ++i)
	{
		for (auto& iter : m_vecObjList[i])
			iter->Render(m_DC);
	}
	m_vecObjList[(UINT)TYPE::PLAYER].front()->Render(m_DC);
}

void CGameScene::Release()
{
	__super::Release();
}
