#include "stdafx.h"
#include "TileGraphics.h"
#include "Vector2.h"
#include "Managers.h"
#include "GameObject.h"
#include "Tile.h"
#include "Wall.h"

CTileGraphics::CTileGraphics()
{
}


CTileGraphics::~CTileGraphics()
{
}

void CTileGraphics::Initialize(CGameObject * _pHost)
{
	m_pHost = _pHost;
	//SetHost(_pHost);
}

void CTileGraphics::Render(HDC hDC, HDC hMemDC)
{
	float	fScrollX = CManagers::instance().Scroll()->Get_ScrollX();
	float	fScrollY = CManagers::instance().Scroll()->Get_ScrollY();

	if (TYPE::TILE == m_pHost->GetType())
	{
		BitBlt(hDC,
			(int)(m_pHost->GetPosition().x - m_pHost->GetScale().x / 2.f + fScrollX),
			(int)(m_pHost->GetPosition().y - m_pHost->GetScale().y / 2.f + fScrollY),
			TILECX,
			TILECY,
			hMemDC,
			TILECX * dynamic_cast<CTile*>(m_pHost)->GetDrawID(),
			0,
			SRCCOPY);
	}
	else if(TYPE::WALL == m_pHost->GetType())
	{
		BitBlt(hDC,
			(int)(m_pHost->GetPosition().x - m_pHost->GetScale().x / 2.f + fScrollX),
			(int)(m_pHost->GetPosition().y - m_pHost->GetScale().y / 2.f + fScrollY),
			TILECX,
			TILECY,
			hMemDC,
			TILECX * dynamic_cast<CWall*>(m_pHost)->GetDrawID(),
			0,
			SRCCOPY);
	}
}
