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
	m_eUIType = SCENEUI::QUICKSLOT;
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
		static_cast<CUI*>(m_arrQuickSlot[i])->SetLayer(0);

		m_arrIcons[i] = new CUI;
		static_cast<CUI*>(m_arrIcons[i])->Initialize();
		static_cast<CUI*>(m_arrIcons[i])->SetLayer(0);

		m_arrQuickSlot[i]->SetPosition(m_vPosition + Vector2::Right() * ((i-5) * (54.f + 5.f) + 27.f));
		m_arrIcons[i]->SetPosition(m_arrQuickSlot[i]->GetPosition());
		m_arrQuickSlot[i]->SetScale(Vector2(54.f, 54.f));

		for (int j = 0; j < 3; ++j)
		{
			m_arrNumbers[i][j] = new CUI;
			static_cast<CUI*>(m_arrNumbers[i][j])->Initialize();
			static_cast<CUI*>(m_arrNumbers[i][j])->SetLayer(0);
			static_cast<CUI*>(m_arrNumbers[i][j])->SetFrameKey(nullptr);
			m_arrNumbers[i][j]->SetPosition(m_arrQuickSlot[i]->GetPosition() + Vector2(14.f, 14.f) - j * Vector2(11.f, 0.f));
			m_arrNumbers[i][j]->SetScale(Vector2(10.f, 30.f));
		}
	}

	m_arrObjects = static_cast<CPlayer*>(CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).front())->GetQuickSlot();
	m_iObjectsNum = static_cast<CPlayer*>(CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).front())->GetQuickSlotCount();
}

int CQuickSlot::Update(void)
{
	for (int i = 0; i < 10; ++i)
	{
		if (m_arrObjects[i])
		{
			m_arrIcons[i]->SetFrameKey(m_arrObjects[i]->GetFrameKey());
			m_arrIcons[i]->SetScale(m_arrObjects[i]->GetScale());

			if (m_iObjectsNum[i])
			{
				UINT temp = m_iObjectsNum[i];
				for (int j = 0; j < 3; ++j)
				{
					if (temp)
					{
						switch (temp % 10)
						{
						case 0: m_arrNumbers[i][j]->SetFrameKey(L"Font0"); break;
						case 1: m_arrNumbers[i][j]->SetFrameKey(L"Font1"); break;
						case 2: m_arrNumbers[i][j]->SetFrameKey(L"Font2"); break;
						case 3: m_arrNumbers[i][j]->SetFrameKey(L"Font3"); break;
						case 4: m_arrNumbers[i][j]->SetFrameKey(L"Font4"); break;
						case 5: m_arrNumbers[i][j]->SetFrameKey(L"Font5"); break;
						case 6: m_arrNumbers[i][j]->SetFrameKey(L"Font6"); break;
						case 7: m_arrNumbers[i][j]->SetFrameKey(L"Font7"); break;
						case 8: m_arrNumbers[i][j]->SetFrameKey(L"Font8"); break;
						case 9: m_arrNumbers[i][j]->SetFrameKey(L"Font9"); break;
						}
						temp /= 10;
					}
					else
					{
						m_arrNumbers[i][j]->SetFrameKey(L"Font0");
					}
				}
			}
			else
			{
				for (int j = 0; j < 3; ++j)
					m_arrNumbers[i][j]->SetFrameKey(L"Font0");
			}
		}
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
	for (int i = 0; i < 10; ++i)
	{
		if (m_arrQuickSlot[i])
			m_arrQuickSlot[i]->Render(hDC);

		if (m_arrObjects[i])
			static_cast<CUI*>(m_arrIcons[i])->Render(hDC);

		for (int j = 0; j < 3; ++j)
		{
			m_arrNumbers[i][j]->Render(hDC);
		}
	}
}

void CQuickSlot::Release(void)
{
	__super::Release();
	for (int i = 0; i < 10; ++i)
	{
		Safe_Delete(m_arrQuickSlot[i]);
		Safe_Delete(m_arrIcons[i]);
	}
}