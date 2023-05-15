#include "stdafx.h"
#include "HP_Bar_Boss.h"
#include "Graphics.h"
#include "Glurch.h"
#include "HiveMother.h"
#include "Managers.h"

CHP_Bar_Boss::CHP_Bar_Boss()
{
}


CHP_Bar_Boss::~CHP_Bar_Boss()
{
}

void CHP_Bar_Boss::Initialize(void)
{
	m_eType = TYPE::UI;
	m_eUIType = SCENEUI::BOSSHP;
	m_eRender = RENDERID::UI;
	m_iLayer = 0;

	m_IsDead = false;

	m_vScale = Vector2(194.f, 8.f);
	m_vPosition.x = m_pHost->GetPosition().x;
	m_vPosition.y = m_pHost->GetPosition().y - 0.5f * m_pHost->GetScale().y - 30.f * Vector2::Up().y;

	m_pFrameKey = L"UI_HealthBar_Boss";
	m_dwTime = GetTickCount();

	m_pGraphics = new CGraphics;
	m_pGraphics->Initialize(this);

	m_pHPfront = new CUI;
	m_pHPfront->Initialize();
	m_pHPfront->SetLayer(0);
	m_pHPfront->SetPosition(m_vPosition);
	m_pHPfront->SetScale(Vector2(m_vScale.x - 6.f, m_vScale.y - 2.f));
	m_pHPfront->SetUIType(SCENEUI::BOSSHP);

	CGraphics* pHPfrontGraphics = new CGraphics;
	pHPfrontGraphics->SetHost(m_pHPfront);
	m_pHPfront->SetGraphics(pHPfrontGraphics);
	m_pHPfront->SetFrameKey(L"UI_HealthBar_Red_Boss");

	FRAME tFrontFrame;
	tFrontFrame.iFrameStart = 0;
	tFrontFrame.iFrameEnd = 0;
	tFrontFrame.iFrameStartBf = m_tFrame.iFrameStart;
	tFrontFrame.dwTime = 0;
	tFrontFrame.iMotion = 0;
	tFrontFrame.dwSpeed = 0;

	m_pHPfront->SetFrame(tFrontFrame);

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameStartBf = m_tFrame.iFrameStart;
	m_tFrame.dwTime = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 0;
}

int CHP_Bar_Boss::Update(void)
{
	if (BOSS::GLURCH == m_pHost->GetBossType())
	{
		m_vPosition.x = m_pHost->GetPosition().x;
		m_vPosition.y = m_pHost->GetPosition().y - 0.5f * m_pHost->GetScale().y - 30.f * Vector2::Up().y;
		m_pHPfront->SetScale(Vector2((m_vScale.x - 6.f) * (static_cast<CGlurch*>(m_pHost)->GetHp() / static_cast<float>(static_cast<CGlurch*>(m_pHost)->GetMaxHp())), m_pHPfront->GetScale().y));
		m_pHPfront->SetPosition(Vector2(m_vPosition.x - (m_vScale.x - m_pHPfront->GetScale().x) / 2.f + 3, m_vPosition.y));
	}
	else if (BOSS::HIVEMOTHER == m_pHost->GetBossType())
	{
		m_pHPfront->SetScale(Vector2((m_vScale.x - 6.f) * (static_cast<CHiveMother*>(m_pHost)->GetHp() / static_cast<float>(static_cast<CHiveMother*>(m_pHost)->GetMaxHp())), m_pHPfront->GetScale().y));
		m_pHPfront->SetPosition(Vector2(m_vPosition.x - (m_vScale.x - m_pHPfront->GetScale().x) / 2.f + 3, m_pHPfront->GetPosition().y));
	}

	return 0;
}

int CHP_Bar_Boss::LateUpdate(void)
{
	return 0;
}

void CHP_Bar_Boss::Render(HDC hDC)
{
	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(m_pFrameKey);

	m_pGraphics->Render(hDC, hMemDC);
	static_cast<CUI*>(m_pHPfront)->Render(hDC);
}

void CHP_Bar_Boss::Release(void)
{
	Safe_Delete(m_pGraphics);
	Safe_Delete(m_pHPfront);
}
