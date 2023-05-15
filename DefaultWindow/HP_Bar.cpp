#include "stdafx.h"
#include "HP_Bar.h"
#include "UIGraphics.h"
#include "Managers.h"
#include "Player.h"

CHP_Bar::CHP_Bar()
{
}

CHP_Bar::~CHP_Bar()
{
	Release();
}

void CHP_Bar::Initialize(void)
{
	m_eType = TYPE::UI;
	m_eRender = RENDERID::UI;
	m_iLayer = 0;

	m_IsDead = false;

	m_vPosition = Vector2(154.f, 58.f);
	m_vScale = Vector2(244.f, 16.f);

	m_pFrameKey = L"HealthBarWindow";
	m_dwTime = GetTickCount();

	m_pGraphics = new CGraphics;
	m_pGraphics->Initialize(this);

	m_pHPfront = new CUI;
	m_pHPfront->Initialize();
	m_pHPfront->SetLayer(0);
	m_pHPfront->SetPosition(m_vPosition);
	m_pHPfront->SetScale(m_vScale - 2.f * Vector2::One());

	CGraphics* pHPfrontGraphics = new CUIGraphics;
	pHPfrontGraphics->SetHost(m_pHPfront);
	m_pHPfront->SetGraphics(pHPfrontGraphics);
	m_pHPfront->SetFrameKey(L"HealthBarRed");
	
	m_pHost = CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).front();
}

int CHP_Bar::Update(void)
{
	m_pHPfront->SetScale(Vector2((m_vScale.x - 2.f) * (static_cast<CPlayer*>(m_pHost)->m_iHp / static_cast<float>(static_cast<CPlayer*>(m_pHost)->m_iMaxHp)), m_pHPfront->GetScale().y));
	m_pHPfront->SetPosition(Vector2(m_vPosition.x - (m_vScale.x - m_pHPfront->GetScale().x) / 2.f + 1, m_pHPfront->GetPosition().y));

	return 0;
}

int CHP_Bar::LateUpdate(void)
{
	return 0;
}

void CHP_Bar::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	static_cast<CGraphics*>(m_pGraphics)->Render(hDC, hMemDC);
	static_cast<CUI*>(m_pHPfront)->Render(hDC);
}

void CHP_Bar::Release(void)
{
	Safe_Delete(m_pGraphics);
	//Safe_Delete(m_pHPfront);
}
