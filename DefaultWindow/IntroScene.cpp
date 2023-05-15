#include "stdafx.h"
#include "IntroScene.h"
#include "GameScene.h"
#include "Managers.h"

CIntroScene::CIntroScene()
{
}


CIntroScene::~CIntroScene()
{
	Release();
}

void CIntroScene::Initialize(void)
{
	m_dwTime = GetTickCount();

	m_pFrameKey[0] = L"IntroSlide1";
	m_pFrameKey[1] = L"IntroSlide2";
	m_pFrameKey[2] = L"IntroSlide3";
	m_pFrameKey[3] = L"IntroSlide4";
	m_pFrameKey[4] = L"IntroSlide5";
	
	m_curFrameKey = m_pFrameKey[0];
	m_iCurIndex = 0;
}

void CIntroScene::FixedUpdate(void)
{
}

void CIntroScene::Update(void)
{
	if (CManagers::instance().Key()->Key_Down(VK_RETURN))
	{
		if (m_iCurIndex > 4)
		{
			CScene* pGameScene = new CGameScene;
			CManagers::instance().Scene()->LoadScene(pGameScene);
		}
		else
		{
			++m_iCurIndex;
			m_curFrameKey = m_pFrameKey[m_iCurIndex];
		}
	}
}

void CIntroScene::LateUpdate(void)
{
}

void CIntroScene::Render(HDC m_DC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_curFrameKey);
	GdiTransparentBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, WINCX, WINCY, RGB(255, 255, 255));
}

void CIntroScene::Release()
{

}
