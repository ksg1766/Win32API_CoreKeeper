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
	//Rectangle(m_DC, 0, 0, WINCX, WINCY);
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(L"BackBuffer");
	BitBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CManagers::instance().Scene()->Get_Current_Scene()->Render(hMemDC);
}

void CMainGame::Release(void)
{
	//Safe_Delete<CGameObject*>(m_pPlayer);
	ReleaseDC(g_hWnd, m_DC);
}
