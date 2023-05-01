#include "stdafx.h"
#include "MainGame.h"
#include "Managers.h"
#include "StartScene.h"

CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	CManagers::instance().Initialize();

	CScene* cStartScene = new CStartScene;
	CManagers::instance().Scene()->LoadScene(cStartScene);
}

void CMainGame::Update(void)
{
	CManagers::instance().Scene()->CurrentScene()->Update();
}

void CMainGame::LateUpdate(void)
{
	CManagers::instance().Scene()->CurrentScene()->LateUpdate();
}

void CMainGame::Render()
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(L"FullBackBuffer");
	BitBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CManagers::instance().Scene()->CurrentScene()->Render(hMemDC);

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	CManagers::instance().Event()->Update();
}

void CMainGame::Release(void)
{
	CManagers::instance().Release();
	ReleaseDC(g_hWnd, m_DC);
}
