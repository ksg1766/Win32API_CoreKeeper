#include "stdafx.h"
#include "StartScene.h"
#include "Managers.h"
#include "IntroScene.h"
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
		CScene* pIntroScene = new CIntroScene;
		pIntroScene->Initialize();
		CManagers::instance().Scene()->LoadScene(pIntroScene);
	}
	else if (CManagers::instance().Key()->Key_Pressing(VK_CONTROL) && CManagers::instance().Key()->Key_Down('E'))
	{
		CScene* pEditScene = new CEditScene;
		CManagers::instance().Scene()->LoadScene(pEditScene);
	}
}

void CStartScene::LateUpdate(void)
{
}

void CStartScene::Render(HDC m_DC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(L"StartScene");
	GdiTransparentBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, WINCX, WINCY, RGB(255, 255, 255));
}
