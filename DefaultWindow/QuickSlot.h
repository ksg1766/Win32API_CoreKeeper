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
	UINT**			GetObjectsNum() { return &m_iObjectsNum; }

private:
	CGameObject**	m_arrObjects;
	UINT*			m_iObjectsNum;
	//vector<CGameObject*>* m_vecObjects;
	//map<CGameObject*, UINT>* m_mapQuickSlot;
	CGameObject*	m_arrQuickSlot[10];

	CGameObject*	m_arrIcons[10];
	CGameObject*	m_arrNumbers[10][3];
	//vector<CGameObject*> m_vecIcons;

	// 뭔 코드지 대체..
};

