#include "stdafx.h"
#include "Graphics.h"
#include "Managers.h"
#include "GameObject.h"

void CGraphics::Initialize(CGameObject * _pHost)
{
	m_pHost = _pHost;
}

void CGraphics::Render(HDC hDC, HDC hMemDC)
{
	float	fScrollX = CManagers::instance().Scroll()->Get_ScrollX();
	float	fScrollY = CManagers::instance().Scroll()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		(int)(m_pHost->GetPosition().x - m_pHost->GetScale().x / 2.f + fScrollX), // ������� x��ġ�� ��ǥ
		(int)(m_pHost->GetPosition().y - m_pHost->GetScale().y / 2.f + fScrollY), // ���� ���� y��ġ�� ��ǥ
		(int)m_pHost->GetScale().x, // ���� ���� ���� ����
		(int)m_pHost->GetScale().y, // ���� ���� ���� ����
		hMemDC,	// ������ ��Ʈ�� �̹��� dc
		m_pHost->GetFrame().iFrameStart * (int)m_pHost->GetScale().x,		// ��Ʈ���� ����� ���� x��ǥ
		m_pHost->GetFrame().iMotion * (int)m_pHost->GetScale().y,		// ��Ʈ���� ����� ���� y��ǥ
		(int)m_pHost->GetScale().x, // ������ ��Ʈ���� ���� ������
		(int)m_pHost->GetScale().y,// ������ ��Ʈ���� ���� ������
		RGB(255, 255, 255)); //�����ϰ��� �ϴ� ����

	//GdiTransparentBlt(hDC,
	//	(int)(m_pHost->GetPosition().x - m_pHost->GetScale().x / 2.f + fScrollX), // ������� x��ġ�� ��ǥ
	//	(int)(m_pHost->GetPosition().y - m_pHost->GetScale().y / 2.f),					// ���� ���� y��ġ�� ��ǥ)
	//	(int)(m_pHost->GetPosition().x + m_pHost->GetScale().x / 2.f),					 // ���� ���� ���� ����
	//	(int)(m_pHost->GetPosition().y + m_pHost->GetScale().y / 2.f),					 // ���� ���� ���� ����
	//	hMemDC,	// ������ ��Ʈ�� �̹��� dc
	//	0,		// ��Ʈ���� ����� ���� x��ǥ
	//	0,		// ��Ʈ���� ����� ���� y��ǥ
	//	(int)m_pHost->GetScale().x, // ������ ��Ʈ���� ���� ������
	//	(int)m_pHost->GetScale().y,// ������ ��Ʈ���� ���� ������
	//	RGB(255, 255, 255)); //�����ϰ��� �ϴ� ����
}

CGraphics::~CGraphics()
{
}