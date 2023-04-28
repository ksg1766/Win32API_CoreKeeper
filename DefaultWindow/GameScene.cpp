#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
}

void CGameScene::Initialize(void)
{
	CGameObject* pPlayer = new CPlayer;
	pPlayer->Initialize();
	m_cObjList[(int)TYPE::PLAYER].push_back(pPlayer);
}

void CGameScene::FixedUpdate(void)
{
}

void CGameScene::Update(void)
{
	for (int i = 0; i < (int)TYPE::END; ++i)
	{
		for (auto& iter : m_cObjList[i])
			iter->Update();
	}
}

void CGameScene::LateUpdate(void)
{
	for (int i = 0; i < (int)TYPE::END; ++i)
	{
		for (auto& iter : m_cObjList[i])
			iter->LateUpdate();
	}
}

void CGameScene::Render(HDC m_DC)
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	for (int i = 0; i < (int)TYPE::END; ++i)
	{
		for (auto& iter : m_cObjList[i])
			iter->Render(m_DC);
	}
}
