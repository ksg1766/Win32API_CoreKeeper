#include "stdafx.h"
#include "UIGraphics.h"
#include "GameObject.h"

CUIGraphics::CUIGraphics()
{
}


CUIGraphics::~CUIGraphics()
{
}

void CUIGraphics::Initialize(CGameObject * _pHost)
{
	m_pHost = _pHost;
}

void CUIGraphics::Render(HDC hDC, HDC hMemDC)
{
	/*BitBlt(hDC,
		(int)(m_pHost->GetPosition().x - m_pHost->GetScale().x / 2.f),
		(int)(m_pHost->GetPosition().y - m_pHost->GetScale().y / 2.f),
		m_pHost->GetScale().x,
		m_pHost->GetScale().y,
		hMemDC,
		0,
		0,
		SRCCOPY);*/

	GdiTransparentBlt(hDC,
		(int)(m_pHost->GetPosition().x - m_pHost->GetScale().x / 2.f), // 복사받을 x위치의 좌표
		(int)(m_pHost->GetPosition().y - m_pHost->GetScale().y / 2.f ), // 복사 받을 y위치의 좌표
		(int)m_pHost->GetScale().x, // 복사 받을 가로 길이
		(int)m_pHost->GetScale().y, // 복사 받을 세로 길이
		hMemDC,	// 복사할 비트맵 이미지 dc
		0,		// 비트맵을 출력할 시작 x좌표
		0,		// 비트맵을 출력할 시작 y좌표
		(int)m_pHost->GetScale().x, // 복사할 비트맵의 가로 사이즈
		(int)m_pHost->GetScale().y,// 복사할 비트맵의 세로 사이즈
		RGB(255, 255, 255)); //제거하고자 하는 색상
}
