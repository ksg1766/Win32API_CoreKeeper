#include "stdafx.h"
#include "UIManager.h"
#include "Managers.h"
#include "HP_Bar.h"
#include "QuickSlot.h"
#include "Player.h"

CUIManager::CUIManager()
{
}

CUIManager::~CUIManager()
{
}

void CUIManager::InitializeSceneUI()
{
	CGameObject* pHP_Bar = new CHP_Bar;
	CGameObject* pHunger_Bar = new CHP_Bar;
	CGameObject* pQuickSlot = new CQuickSlot;

	pHP_Bar->Initialize();
	pQuickSlot->Initialize();
	pHunger_Bar->Initialize();

	dynamic_cast<CHP_Bar*>(pHunger_Bar)->SetFrameKey(L"HungerBarWindow");
	dynamic_cast<CHP_Bar*>(pHunger_Bar)->GetFrontBar()->SetFrameKey(L"HungerBarOrange");

	pHunger_Bar->SetPosition(pHP_Bar->GetPosition() + 15.f * Vector2::Down());
	pHunger_Bar->SetScale(Vector2(244.f, 9.f));
	dynamic_cast<CHP_Bar*>(pHunger_Bar)->GetFrontBar()->SetPosition(pHunger_Bar->GetPosition());
	dynamic_cast<CHP_Bar*>(pHunger_Bar)->GetFrontBar()->SetScale(pHunger_Bar->GetScale() - 2.f * Vector2::One());

	AddSceneUI(pHP_Bar);
	AddSceneUI(pHunger_Bar);
	AddSceneUI(pQuickSlot);
}

void CUIManager::InitializePopUpUI()
{
}

void CUIManager::AddSceneUI(CGameObject* _pUI)
{
	CManagers::instance().Event()->CreateObject(_pUI, TYPE::UI);
	vecGroupSceneUI.push_back(_pUI);
}

void CUIManager::SubSceneUI(CGameObject * _pUI)
{
	CManagers::instance().Event()->DeleteObject(_pUI);
}

void CUIManager::PickingIcon(POINT _pt, bool _isPressing)
{
	CGameObject** ppQuickSlotObj = dynamic_cast<CQuickSlot*>(vecGroupSceneUI[(UINT)SCENEUI::QUICKSLOT])->GetQuickSlotObjects();
	CGameObject** ppQuickSlotRect = dynamic_cast<CQuickSlot*>(vecGroupSceneUI[(UINT)SCENEUI::QUICKSLOT])->GetQuickSlotUI();
	CGameObject** ppQuickSlotIcon = dynamic_cast<CQuickSlot*>(vecGroupSceneUI[(UINT)SCENEUI::QUICKSLOT])->GetQuickSlotIcon();
	
	CGameObject** ppQuickSlot = dynamic_cast<CPlayer*>(CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::PLAYER).front())->GetQuickSlot();


	for (int i = 0; i < 10; ++i)
	{
		if (_isPressing)
		{
			if (ppQuickSlotIcon[i])
				if ((_pt.x <= ppQuickSlotIcon[i]->GetPosition().x + ppQuickSlotIcon[i]->GetScale().x / 2)
					&& (_pt.x >= ppQuickSlotIcon[i]->GetPosition().x - ppQuickSlotIcon[i]->GetScale().x / 2)
					&& (_pt.y <= ppQuickSlotIcon[i]->GetPosition().y + ppQuickSlotIcon[i]->GetScale().y / 2)
					&& (_pt.y >= ppQuickSlotIcon[i]->GetPosition().y - ppQuickSlotIcon[i]->GetScale().y / 2))
					ppQuickSlotIcon[i]->SetPosition(Vector2(_pt.x, _pt.y));
		}
		else
		{
			if (ppQuickSlotIcon[i])
			{
				if ((_pt.x <= ppQuickSlotIcon[i]->GetPosition().x + ppQuickSlotIcon[i]->GetScale().x / 2)
					&& (_pt.x >= ppQuickSlotIcon[i]->GetPosition().x - ppQuickSlotIcon[i]->GetScale().x / 2)
					&& (_pt.y <= ppQuickSlotIcon[i]->GetPosition().y + ppQuickSlotIcon[i]->GetScale().y / 2)
					&& (_pt.y >= ppQuickSlotIcon[i]->GetPosition().y - ppQuickSlotIcon[i]->GetScale().y / 2))
				{
					bool isFixed = false;
					for (int j = 0; j < 10; ++j)
					{
						if ((ppQuickSlotIcon[i]->GetPosition().x <= ppQuickSlotRect[j]->GetPosition().x + ppQuickSlotRect[j]->GetScale().x / 2.f)
							&& (ppQuickSlotIcon[i]->GetPosition().x >= ppQuickSlotRect[j]->GetPosition().x - ppQuickSlotRect[j]->GetScale().x / 2.f)
							&& (ppQuickSlotIcon[i]->GetPosition().y <= ppQuickSlotRect[j]->GetPosition().y + ppQuickSlotRect[j]->GetScale().y / 2.f)
							&& (ppQuickSlotIcon[i]->GetPosition().y >= ppQuickSlotRect[j]->GetPosition().y - ppQuickSlotRect[j]->GetScale().y / 2.f))
						{
							swap(ppQuickSlot[j], ppQuickSlot[i]);
							ppQuickSlotIcon[i]->SetPosition(ppQuickSlotRect[i]->GetPosition());
							ppQuickSlotIcon[j]->SetPosition(ppQuickSlotRect[j]->GetPosition());
							//ppQuickSlotObj[j] = ppQuickSlotObj[i];
							//ppQuickSlotObj[i] = nullptr;

							isFixed = true;
							break;
						}
					}
					if (!isFixed)
					{
						ppQuickSlotIcon[i]->SetPosition(ppQuickSlotRect[i]->GetPosition());
					}
				}
			}
		}
	}
}

void CUIManager::OpenPopUpUI(CGameObject * _pUI)
{
	CManagers::instance().Scene()->CurrentScene()->GetObjList(TYPE::UI).push_back(_pUI);
	vecGroupSceneUI.push_back(_pUI);
}

void CUIManager::ClosePopUpUI(CGameObject * _pUI)
{
}

void CUIManager::Initialize()
{

}
