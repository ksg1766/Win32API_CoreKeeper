#include "stdafx.h"
#include "Tile.h"
#include "Managers.h"
#include "TileGraphics.h"


CTile::CTile()
	: m_iDrawID(0), m_iOption(0), m_iBiom(0)
{
	m_pFrameKey = L"Desert_Ground";
	m_IsDead = false;
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_IsDead = false;
	m_eType = TYPE::TILE;
	m_vScale = Vector2(TILECX, TILECY);
	m_chWallAround = 0b00000000;

	m_pGraphics = new CTileGraphics;
	m_pGraphics->Initialize(this);

	m_eRender = RENDERID::BACKGROUND;
}

int CTile::Update(void)
{
	return 0;
}

int CTile::LateUpdate(void)
{
	return 0;
}

void CTile::Render(HDC hDC)
{	
	if (0 == m_iBiom)
		m_pFrameKey = L"Desert_Ground";
	else if (1 == m_iBiom)
		m_pFrameKey = L"Nature_Ground";
	else if (2 == m_iBiom)
		m_pFrameKey = L"LarvaHive_Ground";

	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);
	//if(m_iOption)
	//	hMemDC = CManagers::instance().Resource()->Find_Image(L"Desert_Wall");
	m_pGraphics->Render(hDC, hMemDC);
}

void CTile::OnUpdate(DIR _eDir, bool _isCreated)
{
	//if(_isCreated)
	//	m_chWallAround |= (1 << (UINT)_eDir);
	//else
	//	m_chWallAround &= ~(1 << (UINT)_eDir);

	////if (m_chWallAround & 1 << (UINT)DIR::RIGHT)
	////{
	////	if (m_chWallAround & 1 << (UINT)DIR::LEFT)
	////	{
	////		m_iDrawID = 13;
	////	}
	////	else
	////	{
	////		m_iDrawID = 8;
	////	}
	////}
	////else
	////{
	////	if (m_chWallAround & 1 << (UINT)DIR::LEFT)
	////	{
	////		m_iDrawID = 7;
	////	}
	////	else
	////	{
	////		m_iDrawID = 8;
	////	}
	////	//m_iDrawID = 4;
	////}
	////m_iOption = 1;

	////
	//if (m_chWallAround & 1 << (UINT)DIR::RIGHT)
	//{
	//	if (m_chWallAround & 1 << (UINT)DIR::LEFT)
	//	{
	//		if (m_chWallAround & 1 << (UINT)DIR::DOWN)
	//		{
	//			m_iDrawID = 13;
	//			m_eRender = RENDERID::GAMEOBJECT;
	//		}
	//	}
	//	else
	//	{
	//		if (m_chWallAround & 1 << (UINT)DIR::DOWN)
	//		{
	//			m_iDrawID = 8;
	//			m_eRender = RENDERID::GAMEOBJECT;
	//		}
	//	}
	//}
	//else
	//{
	//	if (m_chWallAround & 1 << (UINT)DIR::LEFT)
	//	{
	//		if (m_chWallAround & 1 << (UINT)DIR::DOWN)
	//		{
	//			m_iDrawID = 7;
	//			m_eRender = RENDERID::GAMEOBJECT;
	//		}
	//	}
	//	else
	//	{
	//		if (m_chWallAround & 1 << (UINT)DIR::DOWN)
	//		{
	//			m_iDrawID = 4;
	//			m_eRender = RENDERID::GAMEOBJECT;
	//		}
	//	}
	//}
	//m_iOption = 1;

	//if (!(m_chWallAround & (1 << (UINT)DIR::DOWN)))
	//{
	//	m_iOption = 0;
	//	m_iDrawID = 15;
	//	m_eRender = RENDERID::GAMEOBJECT;
	//}
}

void CTile::Release(void)
{
	Safe_Delete(m_pGraphics);
}