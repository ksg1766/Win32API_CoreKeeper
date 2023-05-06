#pragma once
#include "UI.h"
class CQuickSlot :
	public CUI
{
public:
	CQuickSlot();
	virtual ~CQuickSlot();

	virtual void Initialize(void)	override;
	virtual int Update(void)		override;
	virtual int LateUpdate(void)	override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;

	CGameObject**	GetQuickSlotObjects() { return m_arrObjects; }
	CGameObject**	GetQuickSlotUI() { return m_arrQuickSlot; }
	CGameObject**	GetQuickSlotIcon() { return m_arrIcons; }
	//vector<CGameObject*>&	GetQuickSLots() { return m_vecSlots; }

private:
	CGameObject**	m_arrObjects;
	//vector<CGameObject*>* m_vecObjects;

	CGameObject*	m_arrQuickSlot[10];

	CGameObject*	m_arrIcons[10];
	//vector<CGameObject*> m_vecIcons;

	// 아.. 코드 왜 이따구로 짰지 어제의 나는..
};

