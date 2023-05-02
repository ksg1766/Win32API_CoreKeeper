#include "stdafx.h"
#include "Tile.h"
#include "Managers.h"
#include "TileGraphics.h"


CTile::CTile()
	: m_iDrawIDX(14), m_iDrawIDY(0), m_iOption(0)
{
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
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(L"tileset0_ground_state0_BMP");
	if(m_iOption)
		hMemDC = CManagers::instance().Resource()->Find_Image(L"Wall0");
	m_pGraphics->Render(hDC, hMemDC);
}

void CTile::OnUpdate(DIR _eDir, bool _isCreated)
{
	if(_isCreated)
		m_chWallAround |= (1 << (UINT)_eDir);
	else
		m_chWallAround &= ~(1 << (UINT)_eDir);

	//if (m_chWallAround & 1 << (UINT)DIR::RIGHT)
	//{
	//	if (m_chWallAround & 1 << (UINT)DIR::LEFT)
	//	{
	//		m_iDrawIDX = 13;
	//	}
	//	else
	//	{
	//		m_iDrawIDX = 8;
	//	}
	//}
	//else
	//{
	//	if (m_chWallAround & 1 << (UINT)DIR::LEFT)
	//	{
	//		m_iDrawIDX = 7;
	//	}
	//	else
	//	{
	//		m_iDrawIDX = 8;
	//	}
	//	//m_iDrawIDX = 4;
	//}
	//m_iOption = 1;

	//
	if (m_chWallAround & 1 << (UINT)DIR::RIGHT)
	{
		if (m_chWallAround & 1 << (UINT)DIR::LEFT)
		{
			if (m_chWallAround & 1 << (UINT)DIR::DOWN)
			{
				m_iDrawIDX = 13;
				m_eRender = RENDERID::GAMEOBJECT;
			}
		}
		else
		{
			if (m_chWallAround & 1 << (UINT)DIR::DOWN)
			{
				m_iDrawIDX = 8;
				m_eRender = RENDERID::GAMEOBJECT;
			}
		}
	}
	else
	{
		if (m_chWallAround & 1 << (UINT)DIR::LEFT)
		{
			if (m_chWallAround & 1 << (UINT)DIR::DOWN)
			{
				m_iDrawIDX = 7;
				m_eRender = RENDERID::GAMEOBJECT;
			}
		}
		else
		{
			if (m_chWallAround & 1 << (UINT)DIR::DOWN)
			{
				m_iDrawIDX = 4;
				m_eRender = RENDERID::GAMEOBJECT;
			}
		}
	}
	m_iOption = 1;

	if (!(m_chWallAround & (1 << (UINT)DIR::DOWN)))
	{
		m_iOption = 0;
		m_iDrawIDX = 15;
	}
}

void CTile::Release(void)
{
	Safe_Delete(m_pGraphics);
}