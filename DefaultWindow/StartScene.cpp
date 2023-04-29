#include "stdafx.h"
#include "StartScene.h"
#include "Managers.h"
#include "EditScene.h"
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
	if (CManagers::instance().Key()->Key_Down(VK_RETURN))
	{
		CScene* pGameScene = new CGameScene;
		CManagers::instance().Scene()->Load_Scene(pGameScene);
	}
	else if (CManagers::instance().Key()->Key_Down('E'))
	{
		CScene* pEditScene = new CEditScene;
		CManagers::instance().Scene()->Load_Scene(pEditScene);
	}
}

void CStartScene::LateUpdate(void)
{
}

void CStartScene::Render(HDC m_DC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(L"FullStartScene");
	GdiTransparentBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, WINCX, WINCY, RGB(255, 255, 255));
}
