#include "stdafx.h"
#include "Graphics.h"
#include "UI.h"
#include "Managers.h"
#include "GameObject.h"

void CGraphics::Initialize(CGameObject * _pHost)
{
	m_pHost = _pHost;
}

void CGraphics::Render(HDC hDC, HDC hMemDC)
{
	float	fScrollX;
	float	fScrollY;

	if (TYPE::UI == m_pHost->GetType() && SCENEUI::BOSSHP != static_cast<CUI*>(m_pHost)->GetUIType())
	{
		fScrollX = 0.f;
		fScrollY = 0.f;

		GdiTransparentBlt(hDC,
		(int)(m_pHost->GetPosition().x - m_pHost->GetScale().x / 2.f), // 복사받을 x위치의 좌표
			(int)(m_pHost->GetPosition().y - m_pHost->GetScale().y / 2.f), // 복사 받을 y위치의 좌표
			(int)m_pHost->GetScale().x, // 복사 받을 가로 길이
			(int)m_pHost->GetScale().y, // 복사 받을 세로 길이
			hMemDC,	// 복사할 비트맵 이미지 dc
			0,		// 비트맵을 출력할 시작 x좌표
			0,		// 비트맵을 출력할 시작 y좌표
			(int)m_pHost->GetScale().x, // 복사할 비트맵의 가로 사이즈
			(int)m_pHost->GetScale().y,// 복사할 비트맵의 세로 사이즈
			RGB(255, 255, 255)); //제거하고자 하는 색상
	}

	else
	{
		fScrollX = CManagers::instance().Scroll()->Get_ScrollX();
		fScrollY = CManagers::instance().Scroll()->Get_ScrollY();

		GdiTransparentBlt(hDC,
			(int)(m_pHost->GetPosition().x - m_pHost->GetScale().x / 2.f + fScrollX), // 복사받을 x위치의 좌표
			(int)(m_pHost->GetPosition().y - m_pHost->GetScale().y / 2.f + fScrollY), // 복사 받을 y위치의 좌표
			(int)m_pHost->GetScale().x, // 복사 받을 가로 길이
			(int)m_pHost->GetScale().y, // 복사 받을 세로 길이
			hMemDC,	// 복사할 비트맵 이미지 dc
			m_pHost->GetFrame().iFrameStart * (int)m_pHost->GetScale().x,		// 비트맵을 출력할 시작 x좌표
			m_pHost->GetFrame().iMotion * (int)m_pHost->GetScale().y,		// 비트맵을 출력할 시작 y좌표
			(int)m_pHost->GetScale().x, // 복사할 비트맵의 가로 사이즈
			(int)m_pHost->GetScale().y,// 복사할 비트맵의 세로 사이즈
			RGB(255, 255, 255)); //제거하고자 하는 색상
	}
}

CGraphics::~CGraphics()
{
}