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
		(int)(m_pHost->GetPosition().x - m_pHost->GetScale().x / 2.f), // ������� x��ġ�� ��ǥ
		(int)(m_pHost->GetPosition().y - m_pHost->GetScale().y / 2.f ), // ���� ���� y��ġ�� ��ǥ
		(int)m_pHost->GetScale().x, // ���� ���� ���� ����
		(int)m_pHost->GetScale().y, // ���� ���� ���� ����
		hMemDC,	// ������ ��Ʈ�� �̹��� dc
		0,		// ��Ʈ���� ����� ���� x��ǥ
		0,		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_pHost->GetScale().x, // ������ ��Ʈ���� ���� ������
		(int)m_pHost->GetScale().y,// ������ ��Ʈ���� ���� ������
		RGB(255, 255, 255)); //�����ϰ��� �ϴ� ����
}
