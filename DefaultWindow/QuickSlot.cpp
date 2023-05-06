#include "stdafx.h"
#include "QuickSlot.h"
#include "UIGraphics.h"
#include "Managers.h"
#include "Player.h"

CQuickSlot::CQuickSlot()
{
	//ZeroMemory(m_arrObjects, 0, sizeof(m_arrObjects));
}

CQuickSlot::~CQuickSlot()
{
	Release();
}

void CQuickSlot::Initialize(void)
{
	m_eType = TYPE::UI;
	m_eRender = RENDERID::UI;
	m_iLayer = 0;
	m_pIcon = nullptr;

	m_IsDead = false;

	m_vPosition = Vector2(WINCX / 2.f, WINCY - 50.f);

	m_pFrameKey = L"QuickSlot";

	for (int i = 0; i < 10; ++i)
	{
		m_arrQuickSlot[i] = new CUI;
		m_arrQuickSlot[i]->Initialize();
		m_arrQuickSlot[i]->SetFrameKey(L"QuickSlot");
		dynamic_cast<CUI*>(m_arrQuickSlot[i])->SetLayer(0);

		m_arrIcons[i] = new CUI;
		dynamic_cast<CUI*>(m_arrIcons[i])->Initialize();
		dynamic_cast<CUI*>(m_arrIcons[i])->SetLayer(0);

		m_arrQuickSlot[i]->SetPosition(m_vPosition + Vector2::Right() * ((i-5) * (54.f + 5.f) + 27.f));
		m_arrIcons[i]->SetPosition(m_arrQuickSlot[i]->GetPosition());
		m_arrQuickSlot[i]->SetScale(Vector2(54.f, 54.f));
		//CGraphics* pIconGraphics = new CUIGraphics;
	}

	m_arrObjects = dynamic_cast<CPlayer*>(CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).front())->GetQuickSlot();
	//m_vecObjects = dynamic_cast<CPlayer*>(CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).front())->GetStorage();
	//m_arrObjects
	
	//m_vScale = Vector2(244.f, 16.f);

}

int CQuickSlot::Update(void)
{
	for (int i = 0; i < 10; ++i)
	{
		if (m_arrObjects[i])
		{
			m_arrIcons[i]->SetFrameKey(m_arrObjects[i]->GetFrameKey());
			m_arrIcons[i]->SetScale(m_arrObjects[i]->GetScale());
		}
		/*if (*m_vecObjects[i])
		{
			m_arrIcons[i]->SetFrameKey(m_arrObjects[i]->GetFrameKey());
			m_arrIcons[i]->SetScale(m_arrObjects[i]->GetScale());
		}*/
		else
		{
			m_arrIcons[i]->SetFrameKey(nullptr);
		}
	}

	return 0;
}

int CQuickSlot::LateUpdate(void)
{
	return 0;
}

void CQuickSlot::Render(HDC hDC)
{
//	HDC		hMemDC = CManagers::instance().Resource()->Find_Image(L"QuickSlot");
	for (int i = 0; i < 10; ++i)
	{
		if (m_arrQuickSlot[i])
			m_arrQuickSlot[i]->Render(hDC);

		if (m_arrObjects[i])
			dynamic_cast<CUI*>(m_arrIcons[i])->Render(hDC);
	}
}

void CQuickSlot::Release(void)
{
	for (int i = 0; i < 10; ++i)
	{
		Safe_Delete(m_arrQuickSlot[i]);
	}
}