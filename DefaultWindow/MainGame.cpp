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
	CManagers::instance().Scene()->Load_Scene(cStartScene);
}

void CMainGame::Update(void)
{
	CManagers::instance().Scene()->Get_Current_Scene()->Update();
}

void CMainGame::LateUpdate(void)
{
	CManagers::instance().Scene()->Get_Current_Scene()->LateUpdate();
}

void CMainGame::Render()
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(L"FullBackBuffer");
	BitBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CManagers::instance().Scene()->Get_Current_Scene()->Render(hMemDC);

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}

void CMainGame::Release(void)
{
	CManagers::instance().Release();
	ReleaseDC(g_hWnd, m_DC);
}
