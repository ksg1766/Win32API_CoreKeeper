#include "stdafx.h"
#include "EditScene.h"
#include "Managers.h"

CEditScene::CEditScene():m_iDrawID(0), m_iOption(0), m_iBiom(0)
{
}

CEditScene::~CEditScene()
{
	Release();
	CManagers::instance().Tile()->Release();
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
	srand((unsigned)time(NULL));


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
			m_iOption = 0;
	}

	if (CManagers::instance().Key()->Key_Down('1'))	{ m_iBiom = 0; m_iDrawID = 0; }
	if (CManagers::instance().Key()->Key_Down('2'))	{ m_iBiom = 1; m_iDrawID = 0; }
	if (CManagers::instance().Key()->Key_Down('3'))	{ m_iBiom = 2; m_iDrawID = 0; }
	if (CManagers::instance().Key()->Key_Down(VK_SPACE))
	{
		if (0 == m_iBiom || 1 == m_iBiom)
		{
			++m_iDrawID;
			if (6 < m_iDrawID)
				m_iDrawID = 0;
		}
	}

	if (CManagers::instance().Key()->Key_Pressing(VK_LBUTTON))
	{
		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (long)CManagers::instance().Scroll()->Get_ScrollX();
		pt.y -= (long)CManagers::instance().Scroll()->Get_ScrollY();

		CManagers::instance().Tile()->PickingTile(pt, m_iBiom, m_iDrawID, m_iOption);
	}

	if (CManagers::instance().Key()->Key_Pressing(VK_CONTROL) && CManagers::instance().Key()->Key_Down('S'))
		CManagers::instance().Tile()->SaveTile();

	if (CManagers::instance().Key()->Key_Pressing(VK_CONTROL) && CManagers::instance().Key()->Key_Down('O'))
		CManagers::instance().Tile()->LoadTile();

	if (CManagers::instance().Key()->Key_Pressing(VK_CONTROL) && CManagers::instance().Key()->Key_Down('Q'))
		CManagers::instance().Scene()->TerminateScene();
}

void CEditScene::LateUpdate(void)
{
	CManagers::instance().Tile()->LateUpdate();
}

void CEditScene::Render(HDC m_DC)
{
	//HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);
	CManagers::instance().Tile()->Render(m_DC);
}