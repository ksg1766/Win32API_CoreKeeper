#include "stdafx.h"
#include "Wall.h"
#include "Managers.h"
#include "TileGraphics.h"
#include "Collider.h"

CWall::CWall() : m_iDrawID(0), m_iOption(1), m_iBiom(0)
{
	m_pFrameKey = L"Desert_Wall";
	m_IsDead = false;
}

CWall::~CWall()
{
	Release();
}

void CWall::Initialize(void)
{
	m_IsDead = false;
	m_eType = TYPE::WALL;
	m_vScale = Vector2(TILECX, TILECY);
	m_chWallAround = 0b00000000;

	m_pCollider = new CCollider;
	m_pGraphics = new CTileGraphics;

	m_pCollider->Initialize(this);
	m_pGraphics->Initialize(this);

	m_eRender = RENDERID::GAMEOBJECT;
}

int CWall::Update(void)
{
	return 0;
}

int CWall::LateUpdate(void)
{
	m_pCollider->LateUpdate();
	return 0;
}

void CWall::Render(HDC hDC)
{
	if (0 == m_iBiom)
		m_pFrameKey = L"Desert_Wall";
	else if (1 == m_iBiom)
		m_pFrameKey = L"Nature_Wall";
	else if (2 == m_iBiom)
		m_pFrameKey = L"LarvaHive_Wall";

	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
	m_pCollider->Render(hDC);
}

void CWall::Release(void)
{
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
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
					m_iDrawID = 15;
				}
				else
				{
					m_iDrawID = 16;
				}
			}
			else
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawID = 14;
				}
				else
				{
					m_iDrawID = 16;
				}
			}
		}
		else
		{
			if (m_chWallAround & 1 << (UINT)DIR::LEFT)
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawID = 13;
				}
				else
				{
					m_iDrawID = 16;
				}
			}
			else
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawID = 8;
				}
				else
				{
					m_iDrawID = 16;
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
					m_iDrawID = 12;
				}
				else
				{
					m_iDrawID = 16;
				}
			}
			else
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawID = 9;
				}
				else
				{
					m_iDrawID = 16;
				}
			}
		}
		else
		{
			if (m_chWallAround & 1 << (UINT)DIR::LEFT)
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawID = 7;
				}
				else
				{
					m_iDrawID = 16;
				}
			}
			else
			{
				if (m_chWallAround & 1 << (UINT)DIR::DOWN)
				{
					m_iDrawID = 4;
				}
				else
				{
					m_iDrawID = 16;
				}
			}
		}
	}
}

void CWall::OnCollisionEnter(CCollider * _pOther)
{
	CGameObject* pOtherObj = _pOther->GetHost();
	if (TYPE::PLAYER == pOtherObj->GetType() || TYPE::MONSTER == pOtherObj->GetType())
	{
		Vector2 vOtherPos = _pOther->GetPosition();
		Vector2 vOtherScale = _pOther->GetScale();

		Vector2 vThisPos = GetCollider()->GetPosition();
		Vector2 vThisScale = GetCollider()->GetScale();

		float fWidth = fabs(vOtherPos.x - vThisPos.x);
		float fHeight = fabs(vOtherPos.y - vThisPos.y);
		float fRadiusX = (vOtherScale.x / 2.f + vThisScale.x / 2.f) - fWidth;
		float fRadiusY = (vOtherScale.y / 2.f + vThisScale.y / 2.f) - fHeight;

		if (fRadiusX < fRadiusY)
		{
			if (vOtherPos.x < vThisPos.x)
			{
				vOtherPos = pOtherObj->GetPosition();
				vOtherPos.x -= fRadiusX;
			}
			else
			{
				vOtherPos = pOtherObj->GetPosition();
				vOtherPos.x += fRadiusX;
			}
		}
		else
		{
			if (vOtherPos.y < vThisPos.y)
			{
				vOtherPos = pOtherObj->GetPosition();
				vOtherPos.y -= fRadiusY;
			}
			else
			{
				vOtherPos = pOtherObj->GetPosition();
				vOtherPos.y += fRadiusY;
			}
		}
		pOtherObj->SetPosition(vOtherPos);
	}
}

void CWall::OnCollisionStay(CCollider * _pOther)
{
	CGameObject* pOtherObj = _pOther->GetHost();
	if (TYPE::PLAYER == pOtherObj->GetType() || TYPE::MONSTER == pOtherObj->GetType())
	{
		Vector2 vOtherPos = _pOther->GetPosition();
		Vector2 vOtherScale = _pOther->GetScale();

		Vector2 vThisPos = GetCollider()->GetPosition();
		Vector2 vThisScale = GetCollider()->GetScale();

		float fWidth = fabs(vOtherPos.x - vThisPos.x);
		float fHeight = fabs(vOtherPos.y - vThisPos.y);
		float fRadiusX = (vOtherScale.x / 2.f + vThisScale.x / 2.f) - fWidth;
		float fRadiusY = (vOtherScale.y / 2.f + vThisScale.y / 2.f) - fHeight;

		if (fRadiusX < fRadiusY)
		{
			if (vOtherPos.x < vThisPos.x)
			{
				vOtherPos = pOtherObj->GetPosition();
				vOtherPos.x -= fRadiusX;
			}
			else
			{
				vOtherPos = pOtherObj->GetPosition();
				vOtherPos.x += fRadiusX;
			}
		}
		else
		{
			if (vOtherPos.y < vThisPos.y)
			{
				vOtherPos = pOtherObj->GetPosition();
				vOtherPos.y -= fRadiusY;
			}
			else
			{
				vOtherPos = pOtherObj->GetPosition();
				vOtherPos.y += fRadiusY;
			}
		}
		pOtherObj->SetPosition(vOtherPos);
	}
}

void CWall::OnCollisionExit(CCollider * _pOther)
{
}
