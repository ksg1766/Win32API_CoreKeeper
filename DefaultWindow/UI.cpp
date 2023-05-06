#include "stdafx.h"
#include "UI.h"
#include "UIGraphics.h"
#include "Managers.h"

CUI::CUI() : m_iLayer(0)
{
}

CUI::~CUI()
{
}

void CUI::Initialize(void)
{
	m_IsDead = false;
	m_eType = TYPE::UI;
	m_eRender = RENDERID::UI;
	m_iLayer = 0;
	m_pGraphics = new CUIGraphics;
	m_pGraphics->Initialize(this);
	m_pFrameKey = nullptr;
}

int CUI::Update(void)
{
	return 0;
}

int CUI::LateUpdate(void)
{
	return 0;
}

void CUI::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	dynamic_cast<CUIGraphics*>(m_pGraphics)->Render(hDC, hMemDC);
}

void CUI::Release(void)
{
}
