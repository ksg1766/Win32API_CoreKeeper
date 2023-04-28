#include "stdafx.h"
#include "StartScene.h"
#include "Managers.h"
#include "GameScene.h"

CStartScene::CStartScene()
{
}


CStartScene::~CStartScene()
{
}

void CStartScene::Initialize(void)
{

}

void CStartScene::FixedUpdate(void)
{
}

void CStartScene::Update(void)
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		CScene* pGameScene = new CGameScene;
		CManagers::instance().Scene()->Load_Scene(pGameScene);
	}
}

void CStartScene::LateUpdate(void)
{
}

void CStartScene::Render(HDC m_DC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(L"StartScene");
	GdiTransparentBlt(m_DC, 0, 0, 800, 600, hMemDC, 0, 0, 800, 600, RGB(255, 255, 255));
}
