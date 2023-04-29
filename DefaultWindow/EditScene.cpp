#include "stdafx.h"
#include "EditScene.h"
#include "Managers.h"

CEditScene::CEditScene():m_iDrawIDX(0), m_iDrawIDY(0), m_iOption(0)
{
}

CEditScene::~CEditScene()
{
	Release();
}

void CEditScene::Initialize(void)
{
	CManagers::instance().Tile()->Initialize();
}

void CEditScene::FixedUpdate(void)
{

}

void CEditScene::Update(void)
{
	CManagers::instance().Tile()->Update();

	if (CManagers::instance().Key()->Key_Pressing(VK_LEFT))
		CManagers::instance().Scroll()->Set_ScrollX(5.f);

	if (CManagers::instance().Key()->Key_Pressing(VK_RIGHT))
		CManagers::instance().Scroll()->Set_ScrollX(-5.f);

	if (CManagers::instance().Key()->Key_Pressing(VK_UP))
		CManagers::instance().Scroll()->Set_ScrollY(5.f);

	if (CManagers::instance().Key()->Key_Pressing(VK_DOWN))
		CManagers::instance().Scroll()->Set_ScrollY(-5.f);

	if (CManagers::instance().Key()->Key_Down(VK_TAB))
	{
		++m_iOption;
		if (m_iOption > 1)
			m_iOption -= 2;
	}

	if (CManagers::instance().Key()->Key_Down('1'))
	{
		++m_iDrawIDX;
		if (m_iDrawIDX > 15)
			m_iDrawIDX -= 16;
	}

	if (CManagers::instance().Key()->Key_Down(VK_CONTROL) && CManagers::instance().Key()->Key_Down('1'))
	{
		++m_iDrawIDY;
		if (m_iDrawIDY > 19)
			m_iDrawIDY -= 20;
	}

	if (CManagers::instance().Key()->Key_Pressing(VK_LBUTTON))
	{
		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (long)CManagers::instance().Scroll()->Get_ScrollX();
		pt.y -= (long)CManagers::instance().Scroll()->Get_ScrollY();

		CManagers::instance().Tile()->PickingTile(pt, m_iDrawIDX, m_iDrawIDY, m_iOption);
	}

	if (CManagers::instance().Key()->Key_Pressing(VK_CONTROL) && CManagers::instance().Key()->Key_Down('S'))
		CManagers::instance().Tile()->SaveTile();

	if (CManagers::instance().Key()->Key_Pressing(VK_CONTROL) && CManagers::instance().Key()->Key_Down('O'))
		CManagers::instance().Tile()->LoadTile();

	if (CManagers::instance().Key()->Key_Pressing(VK_CONTROL) && CManagers::instance().Key()->Key_Down('Q'))
		CManagers::instance().Scene()->Terminate_Scene();
}

void CEditScene::LateUpdate(void)
{
	CManagers::instance().Tile()->LateUpdate();
}

void CEditScene::Render(HDC m_DC)
{
	CManagers::instance().Tile()->Render(m_DC);
}
