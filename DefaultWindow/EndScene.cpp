#include "stdafx.h"
#include "EndScene.h"
#include "Managers.h"

CEndScene::CEndScene()
{
}


CEndScene::~CEndScene()
{
}

void CEndScene::Initialize(void)
{
	m_dwTime = GetTickCount();

	m_pFrameKey[0] = L"BlackSolid";
	m_pFrameKey[1] = L"EndingScene";

	m_curFrameKey = m_pFrameKey[0];
	m_iCurIndex = 0;
}

void CEndScene::FixedUpdate(void)
{
}

void CEndScene::Update(void)
{
	if (CManagers::instance().Key()->Key_Down(VK_RETURN))
	{
		if (m_iCurIndex > 1)
		{

		}
		else
		{
			++m_iCurIndex;
			m_curFrameKey = m_pFrameKey[m_iCurIndex];
		}
	}
}

void CEndScene::LateUpdate(void)
{
}

void CEndScene::Render(HDC m_DC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_curFrameKey);
	GdiTransparentBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, WINCX, WINCY, RGB(255, 255, 255));
}
