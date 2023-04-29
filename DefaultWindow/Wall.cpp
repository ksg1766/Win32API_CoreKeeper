#include "stdafx.h"
#include "Wall.h"
#include "Managers.h"
#include "TileGraphics.h"
#include "Collider.h"

CWall::CWall() : m_iDrawIDX(0), m_iDrawIDY(0), m_iOption(1)
{
}

CWall::~CWall()
{
}

void CWall::Initialize(void)
{
	m_eType = TYPE::WALL;
	m_vScale = Vector2(TILECX, TILECY);
	m_chWallAround = 0b00000000;

	m_pCollider = new CCollider;
	m_pGraphics = new CTileGraphics;

	m_pCollider->Initialize(this);
	m_pGraphics->Initialize(this);
}

int CWall::Update(void)
{
	return 0;
}

int CWall::LateUpdate(void)
{
	return 0;
}

void CWall::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(L"Wall0");
	m_pGraphics->Render(hDC, hMemDC);
}

void CWall::Release(void)
{
}

void CWall::OnUpdate(DIR _eDir, bool _isCreated)
{
	if (_isCreated)
		SetCreateAround(_eDir);
	else
		SetDestroyAround(_eDir);

	if (m_chWallAround & 1 << (UINT)DIR::RIGHT)
	{
		if (m_chWallAround & 1 << (UINT)DIR::UP)
		{
			if (m_chWallAround & 1 << (UINT)DIR::LEFT)
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawIDX = 15;
				}
				else
				{
					m_iDrawIDX = 16;
				}
			}
			else
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawIDX = 14;
				}
				else
				{
					m_iDrawIDX = 16;
				}
			}
		}
		else
		{
			if (m_chWallAround & 1 << (UINT)DIR::LEFT)
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawIDX = 15;
				}
				else
				{
					m_iDrawIDX = 16;
				}
			}
			else
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawIDX = 14;
				}
				else
				{
					m_iDrawIDX = 16;
				}
			}
		}
	}
	else
	{
		if (m_chWallAround & 1 << (UINT)DIR::UP)
		{
			if (m_chWallAround & 1 << (UINT)DIR::LEFT)
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawIDX = 12;
				}
				else
				{
					m_iDrawIDX = 16;
				}
			}
			else
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawIDX = 9;
				}
				else
				{
					m_iDrawIDX = 16;
				}
			}
		}
		else
		{
			if (m_chWallAround & 1 << (UINT)DIR::LEFT)
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawIDX = 12;
				}
				else
				{
					m_iDrawIDX = 16;
				}
			}
			else
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawIDX = 4;
				}
				else
				{
					m_iDrawIDX = 16;
				}
			}
		}
	}
}